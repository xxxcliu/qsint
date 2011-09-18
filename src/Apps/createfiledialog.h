#ifndef CREATEFILEDIALOG_H
#define CREATEFILEDIALOG_H


#include <QDialog>

#include "createdialogbase.h"


namespace Ui {
    class CreateFileDialog;
}


namespace QSint
{


class CreateFileDialog : public QDialog, public CreateDialogBase
{
    Q_OBJECT

public:
    explicit CreateFileDialog(QWidget *parent = 0);
    ~CreateFileDialog();

    // reimplemented methods
    virtual const DocTypeInfo* createFile(const QList<const DocTypeInfo*>& docTypes);

protected:
    void changeEvent(QEvent *e);

protected slots:
    void on_twDocTypes_itemSelectionChanged();

private:
    Ui::CreateFileDialog *ui;
};


}


#endif // CREATEFILEDIALOG_H
