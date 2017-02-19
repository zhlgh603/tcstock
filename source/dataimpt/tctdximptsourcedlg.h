#ifndef tctdximptsourcedlg_h

#define tctdximptsourcedlg_h

#include <QtCore/QVariant>
#include <QtGui/QDialog>
#include <QtGui/QTableWidgetItem>

/*! \brief tcTdxImportSourceDialog
    \author lgh (zhlgh603@qq.com)
    \version 0.01
    \date 2017.02.17
*/
class tcTdxImportSourceDialog : public QDialog
{
	Q_OBJECT

public:
    tcTdxImportSourceDialog(QWidget *pParent);

    ~tcTdxImportSourceDialog();

	bool SetSettings(const QStringList &pUrlList);

	bool GetSettings(QStringList &pUrlList);

protected slots:
	void UrlListChanged(QTableWidgetItem *pItem);

};

#endif //tctdximptsourcedlg_h

