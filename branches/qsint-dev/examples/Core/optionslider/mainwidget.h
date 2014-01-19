#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private Q_SLOTS:
    void on_OptionSlider_valueChanged(int index);

private:

    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
