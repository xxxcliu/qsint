#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ui->Slider1->enableTicks();
    ui->Slider2->enableTicks();

    ui->Slider1->expandVertically();
    ui->Slider2->expandVertically();
    ui->Slider3->expandVertically();

    ui->Slider1->setEditorWidth(80);
    ui->Slider1->setUnitLabelWidth(30);
    ui->Slider2->setEditorWidth(80);
    ui->Slider2->setUnitLabelWidth(30);
    ui->Slider3->setEditorWidth(80);
    ui->Slider3->setUnitLabelWidth(30);
}


MainWidget::~MainWidget()
{
    delete ui;
}



