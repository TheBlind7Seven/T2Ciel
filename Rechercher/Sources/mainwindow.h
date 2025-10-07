#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qglobal.h>
#if QT_VERSION >= 0x050100
#include <QtWidgets>
#endif

class FindDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void about();
    void newFile();
    void openFile(const QString &path = QString());

    void rechercher();
    void onActionRechercher();

    void rechercherSuivant(const QString &texte, Qt::CaseSensitivity cs, bool wholeWords);
    void rechercherPrecedent(const QString &texte, Qt::CaseSensitivity cs, bool wholeWords);

private:
    void setupFind();
    void setupEditor();
    void setupFileMenu();
    void setupHelpMenu();
    void setupEditMenu();
    void setupToolBar();

    QTextEdit *editor;
    FindDialog *findDialog;
    QTextCursor cursor;
};

#endif // MAINWINDOW_H
