#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ui->MultiPageWidget->addPage(new QLabel("Page 1"), "Page 1", QSint::MultiPageWidget::PP_TOP);
    ui->MultiPageWidget->addPage(new QLabel("Page 2"), "Page 2", QSint::MultiPageWidget::PP_BOTTOM);
    ui->MultiPageWidget->addPage(new QLabel("Page 3"), "Page 3", QSint::MultiPageWidget::PP_LEFT);
    ui->MultiPageWidget->addPage(new QLabel("Page 4"), "Page 4", QSint::MultiPageWidget::PP_RIGHT);
    ui->MultiPageWidget->addPage(new QLabel("Page 5"), "Long Text Page 5", QSint::MultiPageWidget::PP_TOP);
    ui->MultiPageWidget->addPage(new QLabel("Page 6"), "Long Text Page 6", QSint::MultiPageWidget::PP_BOTTOM);
    ui->MultiPageWidget->addPage(new QLabel("Page 7"), "Long Text Page 7", QSint::MultiPageWidget::PP_LEFT);
    ui->MultiPageWidget->addPage(new QLabel("Page 8"), "Long Text Page 8", QSint::MultiPageWidget::PP_RIGHT);
    ui->MultiPageWidget->addPage(new QLabel("Page 9"), "Very Long Text Page 9", QSint::MultiPageWidget::PP_TOP);
    ui->MultiPageWidget->addPage(new QLabel("Page 10"), "Very Long Text Page 10", QSint::MultiPageWidget::PP_BOTTOM);
    ui->MultiPageWidget->addPage(new QLabel("Page 11"), "Very Long Text Page 11", QSint::MultiPageWidget::PP_LEFT);
    ui->MultiPageWidget->addPage(new QLabel("Page 12"), "Very Long Text Page 12", QSint::MultiPageWidget::PP_RIGHT);

    ui->MultiPageWidget->insertPage(new QLabel("Page 1 Layer 1"), "Page 1 L1", QSint::MultiPageWidget::PP_TOP, 0, 1);
    ui->MultiPageWidget->insertPage(new QLabel("Page 2 Layer 1"), "Page 2 L1", QSint::MultiPageWidget::PP_BOTTOM, 0, 1);
    ui->MultiPageWidget->insertPage(new QLabel("Page 3 Layer 1"), "Page 3 L1", QSint::MultiPageWidget::PP_LEFT, 0, 1);
    ui->MultiPageWidget->insertPage(new QLabel("Page 4 Layer 1"), "Page 4 L1", QSint::MultiPageWidget::PP_RIGHT, 0, 1);
    ui->MultiPageWidget->insertPage(new QLabel("Page 5 Layer 1"), "Long Text Page 5 L1", QSint::MultiPageWidget::PP_TOP, 0, 1);
    ui->MultiPageWidget->insertPage(new QLabel("Page 6 Layer 1"), "Long Text Page 6 L1", QSint::MultiPageWidget::PP_BOTTOM, 0, 1);
    ui->MultiPageWidget->insertPage(new QLabel("Page 7 Layer 1"), "Long Text Page 7 L1", QSint::MultiPageWidget::PP_LEFT, 0, 1);
    ui->MultiPageWidget->insertPage(new QLabel("Page 8 Layer 1"), "Long Text Page 8 L1", QSint::MultiPageWidget::PP_RIGHT, 0, 1);

    // Top by default
    ui->AreaSelector->setCurrentIndex(0);
    on_AreaSelector_currentIndexChanged(0);
}


MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_AreaSelector_currentIndexChanged(int index)
{
    QSint::MultiPageWidget::PagePosition area = (QSint::MultiPageWidget::PagePosition)index;
    Qt::Alignment alignment = ui->MultiPageWidget->alignment(area);

    ui->AlignLeft->setChecked(alignment & Qt::AlignLeft);
    ui->AlignRight->setChecked(alignment & Qt::AlignRight);
    ui->AlignJustify->setChecked(alignment & Qt::AlignJustify);
    ui->AlignHCenter->setChecked(alignment & Qt::AlignHCenter);
    ui->AlignVCenter->setChecked(alignment & Qt::AlignVCenter);
    ui->AlignTop->setChecked(alignment & Qt::AlignTop);
    ui->AlignBottom->setChecked(alignment & Qt::AlignBottom);
}


void MainWidget::on_AlignLeft_clicked(bool)
{
    setAlignment();
}


void MainWidget::on_AlignRight_clicked(bool)
{
    setAlignment();
}


void MainWidget::on_AlignHCenter_clicked(bool)
{
    setAlignment();
}


void MainWidget::on_AlignJustify_clicked(bool)
{
    setAlignment();
}


void MainWidget::on_AlignTop_clicked(bool)
{
    setAlignment();
}


void MainWidget::on_AlignBottom_clicked(bool)
{
    setAlignment();
}


void MainWidget::on_AlignVCenter_clicked(bool)
{
    setAlignment();
}


void MainWidget::setAlignment()
{
    int index = ui->AreaSelector->currentIndex();
    QSint::MultiPageWidget::PagePosition area = (QSint::MultiPageWidget::PagePosition)index;

    Qt::Alignment align;

    if (ui->AlignBottom->isChecked())
        align |= Qt::AlignBottom;
    if (ui->AlignTop->isChecked())
        align |= Qt::AlignTop;
    if (ui->AlignLeft->isChecked())
        align |= Qt::AlignLeft;
    if (ui->AlignRight->isChecked())
        align |= Qt::AlignRight;
    if (ui->AlignJustify->isChecked())
        align |= Qt::AlignJustify;
    if (ui->AlignHCenter->isChecked())
        align |= Qt::AlignHCenter;
    if (ui->AlignVCenter->isChecked())
        align |= Qt::AlignVCenter;

    ui->MultiPageWidget->setAlignment(align, area);
}
