/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include  "mainwindow.h"
#include "finddialog.h"

//! [0]
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupFileMenu();
    setupEditMenu(); // définition à compléter
    setupHelpMenu();
    setupFind(); // définition à compléter
    setupEditor();

    setCentralWidget(editor);
    setWindowTitle(QString::fromUtf8("Éditeur"));
}
//! [0]

void MainWindow::about()
{
    QMessageBox::about(this, QString::fromUtf8("À propos d'Éditeur"), QString::fromUtf8("<p><b>Éditeur</b><br/>...</p>"));
}

void MainWindow::newFile()
{
    editor->clear();
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier"), "", tr("Fichiers C++ (*.cpp *.h)"));

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
    connect(findDialog, &FindDialog::findRequested, this, &MainWindow::find);
}


void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor = new QTextEdit;
    editor->setFont(font);

    //editor->ensureCursorVisible();

    // chargement d'un fichier par défaut
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

    QAction *findAct = new QAction(tr("&Rechercher..."), this);
    findAct->setShortcut(QKeySequence::Find); // Ctrl+F
    connect(findAct, &QAction::triggered, this, &MainWindow::rechercher);

    editMenu->addAction(findAct);

    // tu peux ajouter ici Copier/Couper/Coller si tu veux
}


void MainWindow::rechercher()
{
    // Si la boîte FindDialog n'existe pas encore, on l'instancie
    if (!findDialog)
        setupFind();

    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}


void MainWindow::find(const QString &text, bool caseSensitive, bool backward)
{
    if (text.isEmpty()) {
        QMessageBox::information(this, tr("Rechercher"), tr("Veuillez saisir un texte à rechercher."));
        return;
    }

    QTextDocument::FindFlags flags;
    if (backward)
        flags |= QTextDocument::FindBackward;
    if (caseSensitive)
        flags |= QTextDocument::FindCaseSensitively;

    bool found = editor->find(text, flags);
    if (!found) {
        QMessageBox::information(this, tr("Rechercher"), tr("Texte trouvé."));
        // repositionner le curseur pour que la recherche puisse repartir si besoin
        QTextCursor cur = editor->textCursor();
        if (backward)
            cur.movePosition(QTextCursor::End);
        else
            cur.movePosition(QTextCursor::Start);
        editor->setTextCursor(cur);
    }
}

