#ifndef MULTICOMBOBOX_H
#define MULTICOMBOBOX_H

#include <QComboBox>


namespace QSint
{


class MultiComboBox : public QComboBox
{
    Q_OBJECT
public:
    enum ItemRoles{
        EnabledRole = Qt::UserRole-1
    };


    explicit MultiComboBox(QWidget *parent = 0);

    void setOptionEnabled(int index, bool enabled = true);
    bool isOptionEnabled(int index) const;
    
signals:
    
public slots:
    
};


} // namespace

#endif // MULTICOMBOBOX_H
