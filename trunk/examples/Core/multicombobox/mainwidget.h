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
    void on_MultiComboBox_currentIndexChanged(int index);
    void on_EnabledCB_toggled(bool);
    void on_EnableAll_clicked();

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
