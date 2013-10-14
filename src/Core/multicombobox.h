#ifndef MULTICOMBOBOX_H
#define MULTICOMBOBOX_H

#include <QComboBox>
#include <QStandardItemModel>


namespace QSint
{


class MultiComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit MultiComboBox(QWidget *parent = 0);

    void setOptionEnabled(int index, bool enabled = true);
    bool isOptionEnabled(int index) const;

    void setOptionCheckable(int index, bool checkable = true, bool tristate = false);
    bool isOptionCheckable(int index) const;
    bool isOptionTristate(int index) const;

    void setOptionChecked(int index, int checkState = Qt::Checked);
    int isOptionChecked(int index) const;

signals:
    
public slots:
    
protected:
    QStandardItemModel m_model;
};


} // namespace

#endif // MULTICOMBOBOX_H
