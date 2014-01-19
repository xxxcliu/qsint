#include "createfiledialog.h"
#include "ui_createfiledialog.h"
#include "documentfactory.h"


namespace QSint
{


CreateFileDialog::CreateFileDialog(QWidget *parent) :
    QDialog(parent),
    CreateDialogBase(),
    ui(new Ui::CreateFileDialog)
{
    ui->setupUi(this);
}


CreateFileDialog::~CreateFileDialog()
{
    delete ui;
}


void CreateFileDialog::changeEvent(QEvent *e)
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


void CreateFileDialog::on_twDocTypes_itemSelectionChanged()
{
    ui->pbCreate->setEnabled(!ui->twDocTypes->selectedItems().isEmpty());
}


// reimplemented methods

const DocTypeInfo* CreateFileDialog::createFile(const QList<const DocTypeInfo*>& docTypes)
{
    ui->twDocTypes->clear();
    foreach (const DocTypeInfo* info, docTypes) {
        Q_ASSERT(info != NULL);
        Q_ASSERT(info->isValid());

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->twDocTypes);

        item->setText(0, info->description);
        item->setIcon(0, info->icon);
        item->setData(0, 1000, (quintptr)info);
    }

    // just to update button state before actual execution
    on_twDocTypes_itemSelectionChanged();

    if (exec() == QDialog::Rejected)
        return NULL;

    if (ui->twDocTypes->selectedItems().isEmpty())
        return NULL;

    QTreeWidgetItem* item = ui->twDocTypes->selectedItems().first();
    return (const DocTypeInfo*)qvariant_cast<quintptr>(item->data(0, 1000));
}


}

