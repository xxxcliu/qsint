#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    on_OptionSlider_valueChanged(0);
}


MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_OptionSlider_valueChanged(int index)
{
    ui->CurrentItemLabel->setText(ui->OptionSlider->optionsList().at(index));
}
