#include "tctdximptsourcedlg.h"

#include <QtGui/QHeaderView>

tcTdxImportSourceDialog::tcTdxImportSourceDialog(QWidget *pParent)
	: QDialog(pParent)
{
//	setupUi(this);
//	tbl1->setColumnCount(1);
//	tbl1->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
//	tbl1->verticalHeader()->hide();
//	tbl1->horizontalHeader()->hide();
//	tbl1->setSelectionMode(QAbstractItemView::SingleSelection);
//	tbl1->setSelectionBehavior(QAbstractItemView::SelectRows);

//	connect(tbl1, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(UrlListChanged(QTableWidgetItem *)));
}

tcTdxImportSourceDialog::~tcTdxImportSourceDialog()
{
}

bool tcTdxImportSourceDialog::SetSettings(const QStringList &pUrlList)
{
//	foreach (QString url, pUrlList) {
//		int row = tbl1->rowCount();
//		tbl1->insertRow(row);
//		tbl1->setItem(row, 0, new QTableWidgetItem(url));
//	}
//	//append an empty line
//	int row = tbl1->rowCount();
//	tbl1->insertRow(row);
//	tbl1->setItem(row, 0, new QTableWidgetItem(""));
	return true;
}

bool tcTdxImportSourceDialog::GetSettings(QStringList &pUrlList)
{
//	pUrlList.clear();
//	int i;
//	for (i=0; i<tbl1->rowCount()-1; i++) {
//		QTableWidgetItem *item = tbl1->item(i, 0);
//		pUrlList.append(item->text());
//	}
	return true;
}

void tcTdxImportSourceDialog::UrlListChanged(QTableWidgetItem *pItem)
{
//	int i;
//	for (i=tbl1->rowCount()-2; i>=0; i--) {
//		QTableWidgetItem *item = tbl1->item(i, 0);
//		if (item->text().isEmpty()) {
//			tbl1->removeRow(i);
//		}
//	}
//	//check if last line is empty
//	int row = tbl1->rowCount();
//	if (row > 0) {
//		QTableWidgetItem *item = tbl1->item(row-1, 0);
//		if (! item->text().isEmpty()) {
//			tbl1->insertRow(row);
//			tbl1->setItem(row, 0, new QTableWidgetItem(""));
//		}
//	}
}

//#include "moc_tctdximptsourcedlg.cpp"
