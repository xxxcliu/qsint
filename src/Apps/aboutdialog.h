#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H


#include <QDialog>


namespace Ui {
    class AboutDialog;
}


namespace QSint
{


class MainWindow;


class AboutDialog : public QDialog
{
    Q_OBJECT

    typedef MainWindow ParentClass;

public:
    explicit AboutDialog(ParentClass* parent);
    ~AboutDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AboutDialog *ui;
};


}


#endif // ABOUTDIALOG_H
