#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QSintApp>


class MainWidget : public QSint::MainWindow
{
    Q_OBJECT

    typedef QSint::MainWindow BaseClass;

public:
    explicit MainWidget(QWidget *parent = 0);

protected:
    virtual void init();

private:
    class TestMenuController* m_testMenuCntr;
};

#endif // MAINWIDGET_H
