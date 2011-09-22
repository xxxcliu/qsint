#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(ui->PathPicker, SIGNAL(beforePick()), this, SLOT(beforePicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_PathPicker_beforePicked()
{
    int flags = 0;

    if (ui->rbFile->isChecked())
        flags = QSint::PathPicker::PF_EXISTING_FILE;

    if (ui->rbFileToSave->isChecked())
        flags = QSint::PathPicker::PF_SAVE_FILE;

    if (ui->rbFiles->isChecked())
        flags = QSint::PathPicker::PF_EXISTING_FILES;

    if (ui->rbDir->isChecked())
        flags = QSint::PathPicker::PF_EXISTING_DIR;


    int dialogFlags = QSint::PathPicker::DF_DEFAULT;

    if (ui->rbSystemDialog->isChecked())
        dialogFlags = QSint::PathPicker::DF_SYSTEM;


    ui->PathPicker->setObjectsToPick(flags);
    ui->PathPicker->setDialogType(dialogFlags);
}
