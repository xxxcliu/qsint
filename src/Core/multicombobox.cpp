#include "multicombobox.h"


namespace QSint
{


MultiComboBox::MultiComboBox(QWidget *parent) :
    QComboBox(parent)
{
}


void MultiComboBox::setOptionEnabled(int index, bool enabled)
{
    if (index < 0 || index >= count())
        return;

    setItemData(index, enabled, EnabledRole);
}


bool MultiComboBox::isOptionEnabled(int index) const
{
    if (index < 0 || index >= count())
        return false;

    return itemData(index, EnabledRole).toBool();
}


} // namespace

