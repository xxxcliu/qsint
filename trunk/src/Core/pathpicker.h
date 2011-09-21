#ifndef PATHPICKER_H
#define PATHPICKER_H

#include <QLineEdit>
#include <QToolButton>


namespace QSint
{


class PathPicker : public QWidget
{
    Q_OBJECT

public:
    /// \brief Defines file system objects to pick.
    enum PickFlags {
        /// single existing file can be picked (default)
        PF_EXISTING_FILE,
        /// one or more existing files can be picked
        PF_EXISTING_FILES,
        /// single existing directory can be picked
        PF_EXISTING_DIR,
        /// a file to save can be picked (non-existing as well)
        PF_SAVE_FILE
    };

    /// \brief Defines pick dialog type
    enum DialogFlags {
        /// use system dialog
        DF_SYSTEM = 0,
        /// use default Qt dialog
        DF_DEFAULT
    };

    /** Constructor.
      */
    explicit PathPicker(QWidget *parent = 0);

    /** Enables (default) or disables manual path editor according to \a set parameter.
      */
    void setEditorEnabled(bool set);

    /** Returns \a true if manual path editor is enabled, \a false otherwise.
      */
    inline bool isEditorEnabled() const { return m_editorEnabled; }

    /** Defines objects being picked as \a PickFlags.
      */
    void setObjectsToPick(int flags) { m_pickMode = flags; }

    /** Returns \a PickFlags defining objects to pick.
      */
    inline int objectsToPick() const { return m_pickMode; }

    /** Defines pick dialog type as \a DialogFlags.
      */
    void setDialogType(int flags) { m_dialogMode = flags; }

    /** Returns \a DialogFlags defining dialog type.
      */
    inline int dialogType() const { return m_dialogMode; }

    void setDefaultDirectory(const QString& dirName) { m_dir = dirName; }

    inline const QString& defaultDirectory() const { return m_dir; }

    void setFilters(const QString& filters) { m_filter = filters; }

    inline const QString& filters() const { return m_filter; }

    void setCaption(const QString& text) { m_caption = text; }

    inline const QString& caption() const { return m_caption; }

    QToolButton* button() { return m_button; }

    QLineEdit* editor() { return m_editor; }

signals:
    /** Emitted when user is about to pick an object from the dialog or editor.
      */
    void beforePicked();

    /** Emitted when user picks an object from the dialog or editor.
        \a path
      */
    void picked(const QString& path);

protected Q_SLOTS:
    /** Invokes file object pick dialog. When a valid object(s) has been picked
        from the filesystem, the implementation should set the content of the editor
        and emit \a picked() signal.
      */
    virtual void showPickDialog();

protected:
    QLineEdit *m_editor;
    bool m_editorEnabled;

    QToolButton *m_button;

    int m_pickMode;
    int m_dialogMode;

    QString m_filter;
    QString m_dir;
    QString m_caption;
};


}


#endif // PATHPICKER_H
