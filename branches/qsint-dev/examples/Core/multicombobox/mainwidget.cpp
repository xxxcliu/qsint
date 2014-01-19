#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ui->MultiComboBox->setOptionCheckable(0);
    ui->MultiComboBox->setOptionCheckable(1, true, true);

    on_MultiComboBox_currentIndexChanged(0);
}


MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_MultiComboBox_currentIndexChanged(int index)
{
    ui->EnabledCB->blockSignals(true);
    ui->EnabledCB->setChecked(ui->MultiComboBox->isOptionEnabled(index));
    ui->EnabledCB->blockSignals(false);

    ui->CheckedCB->blockSignals(true);
    ui->CheckedCB->setCheckState((Qt::CheckState)ui->MultiComboBox->isOptionChecked(index));
    ui->CheckedCB->blockSignals(false);
}


void MainWidget::on_EnabledCB_toggled(bool on)
{
    int index = ui->MultiComboBox->currentIndex();
    ui->MultiComboBox->setOptionEnabled(index, on);
}


void MainWidget::on_EnableAll_clicked()
{
    for (int i = 0; i < ui->MultiComboBox->count(); i++)
        ui->MultiComboBox->setOptionEnabled(i);
}


