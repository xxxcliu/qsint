#include "multicombobox.h"


namespace QSint
{


MultiComboBox::MultiComboBox(QWidget *parent) :
    QComboBox(parent)
{
    setModel(&m_model);
}


void MultiComboBox::setOptionEnabled(int index, bool enabled)
{
    if (index < 0 || index >= count())
        return;

    m_model.item(index, modelColumn())->setEnabled(enabled);
}


bool MultiComboBox::isOptionEnabled(int index) const
{
    if (index < 0 || index >= count())
        return false;

    return m_model.item(index, modelColumn())->isEnabled();
}


void MultiComboBox::setOptionCheckable(int index, bool checkable, bool tristate)
{
    if (index < 0 || index >= count())
        return;

    m_model.item(index, modelColumn())->setCheckable(checkable);
    m_model.item(index, modelColumn())->setTristate(tristate);
}


bool MultiComboBox::isOptionCheckable(int index) const
{
    if (index < 0 || index >= count())
        return false;

    return m_model.item(index, modelColumn())->isCheckable();
}


bool MultiComboBox::isOptionTristate(int index) const
{
    if (index < 0 || index >= count())
        return false;

    return m_model.item(index, modelColumn())->isTristate();
}


void MultiComboBox::setOptionChecked(int index, int checkState)
{
}


int MultiComboBox::isOptionChecked(int index) const
{
    if (index < 0 || index >= count())
        return -1;

    return m_model.item(index, modelColumn())->checkState();
}


} // namespace

