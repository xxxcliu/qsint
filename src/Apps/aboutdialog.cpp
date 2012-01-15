#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include "mainwindow.h"


namespace QSint
{


AboutDialog::AboutDialog(ParentClass* parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->treeComponentsInfo->header()->setResizeMode(QHeaderView::ResizeToContents);
    ui->treeComponentsInfo->header()->setMovable(false);

    Q_ASSERT(parent != NULL);

    // application
    ui->labelName->setText(parent->getInfo(QSint::ApplicationTitle).toString());

    ui->labelVersion->setText(QCoreApplication::applicationVersion());

    ui->labelProvider->setText(parent->getInfo(QSint::ApplicationCopyright).toString());

    QString url(QString("<a href='%1'>%1</a>").arg(parent->getInfo(QSint::ApplicationURL).toString()));
    if (url.isEmpty())
        ui->labelURL->hide();
    else
        ui->labelURL->setText(url);

    QString info(parent->getInfo(QSint::ApplicationDescription).toString());
    if (info.isEmpty())
        ui->labelDescription->hide();
    else {
        info = "<hr>" + info;
        ui->labelDescription->setText(info);
    }

    QPixmap logo = qvariant_cast<QPixmap>(parent->getInfo(QSint::ApplicationLogo));
    if (logo.isNull())
        ui->labelLogo->hide();
    else
        ui->labelLogo->setPixmap(logo);

    setWindowTitle(tr("About %1").arg(parent->getInfo(QSint::ApplicationTitle).toString()));

    // components
    const QList<VersionInfo>& compInfo = parent->componentsInfo();
    if (compInfo.isEmpty()) {
        ui->treeComponentsInfo->hide();
    } else {
        ui->treeComponentsInfo->clear();

        foreach(const VersionInfo& info, compInfo)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeComponentsInfo);
            item->setText(0, info.name);
            item->setText(1, info.textVersion);
            item->setText(2, info.description);
        }
    }
}


AboutDialog::~AboutDialog()
{
    delete ui;
}


void AboutDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


}
