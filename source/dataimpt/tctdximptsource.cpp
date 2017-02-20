#include "tctdximptsource.h"

#include <QtGui/QApplication>
#include <QtCore/QUrl>

#include "../service/tcsvcpack.h"
#include "../stockinfo/tcstockinfopack.h"
#include "tctdximptsourcedlg.h"

#include "tdx.cpp"

tcTdxImportSource::tcTdxImportSource()
{
	mHttp = NULL;
}

QString tcTdxImportSource::GetDescription()
{
    return tr("tdx stock (import from data folder)");
}

bool tcTdxImportSource::HaveSettingDialog()
{
	return true;
}

void tcTdxImportSource::ShowSettingDialog(QWidget *pParent)
{
	QStringList urllist;
	GetImportUrlList(urllist);

    tcTdxImportSourceDialog dlg(pParent);
	if (! dlg.SetSettings(urllist)) {
		tcLogService::CreateLog(this, "Error when set dialog settings.");
		return;
	}
	if (dlg.exec() != QDialog::Accepted) {
		return;
	}
	if (! dlg.GetSettings(urllist)) {
		tcLogService::CreateLog(this, "Error when get dialog settings.");
		return;
	}
	SetImportUrlList(urllist);
}

bool tcTdxImportSource::ImportProcess()
{
	mIsCanceling = false;

    mPath = "E:/new_gxzq_v6.56";
    QStringList stockList = getStockList(mPath);

	int i;
    for (i=0; i<stockList.count(); i++) {
        ProcessForOneStock(stockList[i]);
		if (mIsCanceling) {
			emit OnAppendMessage(tr("Import procedure canceled by user."), false);
			break;
		}
        emit OnUpdateProgress(i*100 / stockList.count());
	}
	emit OnUpdateProgress(100);

	OnAppendMessage(tr("All done."), true);
	return true;
}

void tcTdxImportSource::CancelImportProcess()
{
	mIsCanceling = true;
}

void tcTdxImportSource::GetImportUrlList(QStringList &pUrlList)
{
	pUrlList.clear();
	int urlcount = tcCfgService::GetAttribute(this, "UrlCount", "0").toInt();
	int i;
	QString urlkey = "Url_%1";
	for (i=0; i<urlcount; i++) {
		QString url = tcCfgService::GetAttribute(this, urlkey.arg(i), "");
		pUrlList.append(url);
	};
}

void tcTdxImportSource::SetImportUrlList(const QStringList &pUrlList)
{
	QString urlcount = "%1";
	tcCfgService::SetAttribute(this, "UrlCount", urlcount.arg(pUrlList.count()));
	int i;
	QString urlkey = "Url_%1";
	for (i=0; i<pUrlList.count(); i++) {
		tcCfgService::SetAttribute(this, urlkey.arg(i), pUrlList[i]);
	}
}

bool tcTdxImportSource::ProcessForOnePage(const QString &pPageUrl)
{
	emit OnAppendMessage(tr("Begin import from page: %1.").arg(pPageUrl), true);

	QUrl url(pPageUrl);
	mHttp->setHost(url.host(), url.port() != -1 ? url.port() : 80);
	if (! url.userName().isEmpty()) {
		mHttp->setUser(url.userName(), url.password());
	}
	
	mIsReceiving = true;
	mHttp->get(pPageUrl);

	while (mIsReceiving) {
		qApp->processEvents();
		if (mIsCanceling) {
			return false;
		}
	}
	if (mReceivedData.isEmpty()) {
		return false;
	}

	QRegExp rx("<tr bgcolor=(?:\\S+) align=center><a name=(\\S+)></a>(.+)(?=</tr>)");
	rx.setMinimal(true);
	int pos = 0;
	while ((pos = rx.indexIn(mReceivedData, pos)) != -1) {
		ProcessForOneStock(rx.cap(2));
		pos += rx.matchedLength();
	}
	return true;
}

void tcTdxImportSource::ProcessForOneStock(const QString &pText)
{
    QStringList nameList = pText.split(",");
    if (3!=nameList.count()) {
        emit OnAppendMessage(tr("Error when extract data of stock."), false);
        return;
    }
    QString stockcode = nameList.at(0);
//    QString stockname = nameList.at(1);
//    QString shortname = nameList.at(2);

    //get the stock object
    tcStockInfo stockinfo(stockcode);
    if (! stockinfo.IsAvailable()) {
        emit OnAppendMessage(tr("The stock not exists."), false);
        return;
    }

    emit OnAppendMessage(tr("Processing stock %1 ...").arg(stockcode), true);

    QString fileName = mPath + "/vipdoc/sh/lday/sh" + stockcode + ".day";

    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly))
    {
        return;
    }
    int len = sizeof(tdx_lday);
    tdx_lday lday;
    char *p = (char *)&lday;
    memset(p, 0, len);
    while(len==f.read(p, len))
    {
        tcStockDailyData dailydata;
        //set the data of today
        QDate date = QDate::fromString(QString::number(lday.date), "yyyyMMdd");
//        if (! stockinfo->ReadData(date, &dailydata)) {
//            emit OnAppendMessage(tr("Error when get daily data of stock."), false);
//            return;
//        }
        dailydata.OpenPrice = long(lday.open);
        dailydata.ClosePrice = long(lday.close);
        dailydata.MaxPrice = long(lday.high);
        dailydata.MinPrice = long(lday.low);
        dailydata.TotalPrice = lday.amount;
        dailydata.Quantity = lday.vol;
        if (! stockinfo->WriteData(date, &dailydata)) {
            emit OnAppendMessage(tr("Error when set daily data of stock."), false);
            return;
        }

        memset(p, 0, len);
        qApp->processEvents();
    }
}

void tcTdxImportSource::DoHttpDone(bool pError)
{
	if (pError) {
		tcLogService::CreateLog(this, "Done Error: " + mHttp->errorString());
		emit OnAppendMessage(tr("Error: %1").arg(mHttp->errorString()), false);
	}
	else {
		Q_ASSERT(mHttp);
		mReceivedData = mHttp->readAll();
		emit OnAppendMessage(tr("Received successful."), true);
	}
	mIsReceiving = false;
}

//#include "moc_tctdximptsource.cpp"
