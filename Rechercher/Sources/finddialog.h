#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <qglobal.h>
#include <QtWidgets>

class FindDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *label;
    QLineEdit *texteRecherche;
    QCheckBox *respecterCasse;
    QCheckBox *rechercheArriere;
    QCheckBox *regexBox;
    QCheckBox *wholeWords;
    QPushButton *boutonRechercher;
    QPushButton *boutonFermer;

public:
    FindDialog(QWidget *parent = nullptr);
    ~FindDialog();

signals:
    void rechercherSuivant(const QString &texte, Qt::CaseSensitivity cs, bool wholeWords);
    void rechercherPrecedent(const QString &texte, Qt::CaseSensitivity cs, bool wholeWords);

private slots:
    void validerBouton();
    void clicRechercher();
};

#endif // FINDDIALOG_H
