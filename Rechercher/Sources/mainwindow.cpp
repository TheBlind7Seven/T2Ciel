#include "mainwindow.h"
#include "finddialog.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>

//! [0]
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupEditor();
    setCentralWidget(editor);

    setupFileMenu();
    setupEditMenu();
    setupHelpMenu();
    setupFind();
    setupToolBar();

    setWindowTitle(QString::fromUtf8("Éditeur"));
}

//! [0]

void MainWindow::about()
{
    QMessageBox::about(this, QString::fromUtf8("À propos d'Éditeur"),
                       QString::fromUtf8("<p><b>Éditeur</b><br/>Un petit éditeur de texte avec fonction rechercher.</p>"));
}

void MainWindow::setupToolBar()
{
    QToolBar *toolBar = addToolBar(tr("Outils"));

    toolBar->addAction(tr("Nouveau"), this, &MainWindow::newFile);
    toolBar->addAction(tr("Ouvrir"), this, [this]() { openFile(); });
    toolBar->addSeparator();

    toolBar->addAction(tr("Couper"), editor, &QTextEdit::cut);
    toolBar->addAction(tr("Copier"), editor, &QTextEdit::copy);
    toolBar->addAction(tr("Coller"), editor, &QTextEdit::paste);
    toolBar->addSeparator();

    toolBar->addAction(tr("Rechercher"), this, &MainWindow::rechercher);
}

void MainWindow::newFile()
{
    editor->clear();
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier"), "", tr("Fichiers C++ (*.cpp *.h);;Tous les fichiers (*.*)"));

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            editor->setPlainText(file.readAll());
    }
}


void MainWindow::setupFind()
{
    findDialog = new FindDialog(this);

    connect(findDialog, &FindDialog::rechercherSuivant,
            this, &MainWindow::rechercherSuivant);
    connect(findDialog, &FindDialog::rechercherPrecedent,
            this, &MainWindow::rechercherPrecedent);

}

//! [1]
void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor = new QTextEdit;
    editor->setFont(font);


    QFile file("traceroute.txt");
    if (file.open(QFile::ReadOnly | QFile::Text))
        editor->setPlainText(file.readAll());
}
//! [1]

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&Fichier"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&Nouveau"), this, SLOT(newFile()),
                        QKeySequence::New);

    fileMenu->addAction(tr("&Ouvrir..."), this, SLOT(openFile()),
                        QKeySequence::Open);

    fileMenu->addAction(tr("&Quitter"), qApp, SLOT(quit()),
                        QKeySequence::Quit);
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Aide"), this);
    menuBar()->addMenu(helpMenu);

    helpMenu->addAction(QString::fromUtf8("À propos d'Éditeur"), this, SLOT(about()));
    helpMenu->addAction(QString::fromUtf8("À propos de Qt"), qApp, SLOT(aboutQt()));
}

void MainWindow::setupEditMenu()
{
    QMenu *editMenu = new QMenu(tr("&Édition"), this);
    menuBar()->addMenu(editMenu);


    QAction *actionCouper = editMenu->addAction(tr("Couper"), editor, &QTextEdit::cut);
    actionCouper->setShortcut(QKeySequence::Cut);

    QAction *actionCopier = editMenu->addAction(tr("Copier"), editor, &QTextEdit::copy);
    actionCopier->setShortcut(QKeySequence::Copy);

    QAction *actionColler = editMenu->addAction(tr("Coller"), editor, &QTextEdit::paste);
    actionColler->setShortcut(QKeySequence::Paste);

    editMenu->addSeparator();

    QAction *actionRechercher = new QAction(tr("Rechercher"), this);
    actionRechercher->setShortcut(QKeySequence::Find);
    connect(actionRechercher, &QAction::triggered, this, &MainWindow::rechercher);

    editMenu->addAction(actionRechercher);
}



void MainWindow::rechercher()
{
    if (findDialog) {
        findDialog->show();
        findDialog->raise();
        findDialog->activateWindow();
    }
}
void MainWindow::onActionRechercher()
{
    QMessageBox::information(this, "Rechercher", "Tu as cliqué sur Rechercher !");
}

void MainWindow::rechercherSuivant(const QString &texte, Qt::CaseSensitivity cs, bool wholeWords)
{
    QTextDocument::FindFlags options = QTextDocument::FindFlags();

    if (cs == Qt::CaseSensitive)
        options |= QTextDocument::FindCaseSensitively;
    if (wholeWords)
        options |= QTextDocument::FindWholeWords;

    cursor = editor->document()->find(texte, cursor, options);

    if (!cursor.isNull()) {
        editor->setTextCursor(cursor);
        editor->ensureCursorVisible();
    } else {
        QMessageBox::information(this, tr("Information"), tr("Recherche terminée !"));
    }
}



void MainWindow::rechercherPrecedent(const QString &texte, Qt::CaseSensitivity cs, bool wholeWords)
{
    if (texte.isEmpty())
        return;

    QTextDocument::FindFlags options = QTextDocument::FindBackward;

    if (cs == Qt::CaseSensitive)
        options |= QTextDocument::FindCaseSensitively;
    if (wholeWords)
        options |= QTextDocument::FindWholeWords;

    cursor = editor->document()->find(texte, cursor, options);

    if (!cursor.isNull()) {
        editor->setTextCursor(cursor);
        editor->ensureCursorVisible();
    } else {
        QMessageBox::information(this, tr("Information"),
                                 tr("Recherche terminée !"));
        cursor = QTextCursor(editor->document());
        cursor.movePosition(QTextCursor::End);
    }
}








