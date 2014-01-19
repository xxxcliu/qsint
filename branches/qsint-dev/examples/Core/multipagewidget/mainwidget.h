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
    void on_AreaSelector_currentIndexChanged(int index);
    void on_AlignLeft_clicked(bool);
    void on_AlignRight_clicked(bool);
    void on_AlignHCenter_clicked(bool);
    void on_AlignJustify_clicked(bool);
    void on_AlignTop_clicked(bool);
    void on_AlignBottom_clicked(bool);
    void on_AlignVCenter_clicked(bool);

private:
    void setAlignment();

    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
