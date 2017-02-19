#ifndef tctdximptsource_h

#define tctdximptsource_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtNetwork/QHttp>

#include "tcimptsource.h"

/*! \brief tcTdxImportSource
    \author lgh (zhlgh603@qq.com)
    \version 0.01
    \date 2017.02.17
 	
    从通达信导入股票每日数据。
*/
class tcTdxImportSource : public tcImportSource
{
	Q_OBJECT

public:
    tcTdxImportSource();

	virtual QString GetDescription();

	virtual bool HaveSettingDialog();

	virtual void ShowSettingDialog(QWidget *pParent);

protected:
	virtual bool ImportProcess();

	virtual void CancelImportProcess();

	void GetImportUrlList(QStringList &pUrlList);

	void SetImportUrlList(const QStringList &pUrlList);

	bool ProcessForOnePage(const QString &pPageUrl);

	void ProcessForOneStock(const QString &pText);

protected slots:
	void DoHttpDone(bool pError);

private:
	QHttp *mHttp;

	bool mIsReceiving;

	bool mIsCanceling;

	QString mReceivedData;

};

#endif //tctdximptsource_h
