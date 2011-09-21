#include "pathpicker.h"


// init common icons
#include "core.h"


#include <QHBoxLayout>
#include <QFileDialog>


namespace QSint
{


PathPicker::PathPicker(QWidget *parent) :
    QWidget(parent),
    m_editorEnabled(true),
    m_pickMode(PF_EXISTING_FILE),
    m_dialogMode(DF_DEFAULT)
{
    QHBoxLayout *hbl = new QHBoxLayout();
    hbl->setSpacing(0);
    hbl->setMargin(0);
    setLayout(hbl);

    m_editor = new QLineEdit(this);

    m_button = new QToolButton(this);
    m_button->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_button->setIcon(QIcon(":/icons/Open"));

    hbl->addWidget(m_editor);
    hbl->addWidget(m_button);

    connect(m_button, SIGNAL(clicked()), this, SLOT(showPickDialog()));
}


void PathPicker::setEditorEnabled(bool set)
{
    if (m_editorEnabled != set) {
        m_editorEnabled = set;
        m_editor->setEnabled(set);
    }
}


void PathPicker::showPickDialog()
{
    emit beforePicked();

    QString result;
    QString caption(m_caption);

    // default caption if empty
    if (caption.isEmpty()){
        switch (m_pickMode){
        case PF_EXISTING_FILE:
            caption = tr("Choose a file to open");
            break;

        case PF_EXISTING_FILES:
            caption = tr("Choose files to open");
            break;

        case PF_EXISTING_DIR:
            caption = tr("Choose a directory");
            break;

        case PF_SAVE_FILE:
            caption = tr("Choose a file to save");
            break;
        }
    }

    // default icon if empty
    if (m_button->icon().isNull() && m_button->text().isEmpty()){
        m_button->setIcon(QIcon(":/icons/Open"));
    }

    bool isSystem = (m_dialogMode == DF_SYSTEM);

    // use native dialogs?
    bool asked = false;
    if (isSystem) {
        switch (m_pickMode){
        case PF_EXISTING_DIR:
            asked = true;

            result = QFileDialog::getExistingDirectory(NULL,
                        caption,
                        m_dir);
            break;

        case PF_EXISTING_FILE:
            asked = true;

            result = QFileDialog::getOpenFileName(NULL,
                        caption,
                        m_dir,
                        m_filter);
            break;

        case PF_SAVE_FILE:
            asked = true;

            result = QFileDialog::getSaveFileName(NULL,
                        caption,
                        m_dir,
                        m_filter);
            break;

        case PF_EXISTING_FILES:
            {
            asked = true;

            QStringList list = QFileDialog::getOpenFileNames(NULL,
                        caption,
                        m_dir,
                        m_filter);

            if (!list.isEmpty())
                result = list.join(";");

            break;
            }
        }
    }

    // use Qt dialogs instead
    if (!asked) {
        QFileDialog dialog(NULL, caption, m_dir, m_filter);

        switch (m_pickMode){
            case PF_EXISTING_FILE:
                dialog.setAcceptMode(QFileDialog::AcceptOpen);
                dialog.setFileMode(QFileDialog::ExistingFile);
                break;

            case PF_EXISTING_FILES:
                dialog.setAcceptMode(QFileDialog::AcceptOpen);
                dialog.setFileMode(QFileDialog::ExistingFiles);
                break;

            case PF_EXISTING_DIR:
                dialog.setAcceptMode(QFileDialog::AcceptOpen);
                dialog.setFileMode(QFileDialog::Directory);
                dialog.setOption(QFileDialog::ShowDirsOnly);
                break;

            case PF_SAVE_FILE:
                dialog.setAcceptMode(QFileDialog::AcceptOpen);
                dialog.setFileMode(QFileDialog::AnyFile);
                break;
        }

        if (dialog.exec()) {
            QStringList list = dialog.selectedFiles();
            if (!list.isEmpty())
                result = list.join(";");
        }
    }

    if (result.isEmpty())
        return;

    m_editor->setText(result);

    emit picked(result);
}


}

