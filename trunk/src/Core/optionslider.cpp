#include "optionslider.h"


namespace QSint
{


OptionSlider::OptionSlider(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);

    m_slider = new QSlider(this);
    mainLayout->addWidget(m_slider);

    m_labelBox = new QHBoxLayout();
    mainLayout->addLayout(m_labelBox);

    m_slider->setTickPosition(QSlider::TicksBelow);
    m_slider->setTickInterval(1);
    m_slider->setMinimum(0);
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setPageStep(1);
    m_slider->setSingleStep(1);

    connect(m_slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
    connect(m_slider, SIGNAL(sliderMoved(int)), this, SIGNAL(sliderMoved(int)));
}


void OptionSlider::setOptionsList(const QStringList& options)
{
    qDeleteAll(m_labels);

    m_options = options;

    m_slider->setMaximum(m_options.size()-1);

    for (int i = 0; i < m_options.size(); i++)
    {
        QLabel *label = new QLabel(m_options.at(i), this);
        m_labels.push_back(label);

        m_labelBox->addWidget(label);

        if (i == 0){
            label->setAlignment(Qt::AlignLeft);
            m_labelBox->setStretchFactor(label, 1);
        } else if (i == m_options.size()-1){
            label->setAlignment(Qt::AlignRight);
            m_labelBox->setStretchFactor(label, 1);
        } else {
            label->setAlignment(Qt::AlignHCenter);
            m_labelBox->setStretchFactor(label, 2);
        }

        label->setWordWrap(true);
    }

    emit valueChanged(m_slider->value());
}


void OptionSlider::setCurrentIndex(int index)
{
    m_slider->setValue(index);
}


int OptionSlider::currentIndex()
{
    return m_slider->value();
}


} // namespace
