#include "finddialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel(tr("Recherche :"));
    texteRecherche = new QLineEdit;

    respecterCasse = new QCheckBox(tr("Respecter la casse"));
    rechercheArriere = new QCheckBox(tr("Chercher en arrière"));
    regexBox = new QCheckBox(tr("Utiliser des expressions régulières"));
    wholeWords = new QCheckBox(tr("Mot entier seulement"));

    boutonRechercher = new QPushButton(tr("Rechercher"));
    boutonRechercher->setDefault(true);
    boutonRechercher->setEnabled(false);
    boutonFermer = new QPushButton(tr("Fermer"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label, 0, 0);
    layout->addWidget(texteRecherche, 0, 1, 1, 2);
    layout->addWidget(respecterCasse, 1, 0);
    layout->addWidget(rechercheArriere, 2, 0);
    layout->addWidget(regexBox, 3, 0);
    layout->addWidget(wholeWords, 4, 0);
    layout->addWidget(boutonRechercher, 1, 2);
    layout->addWidget(boutonFermer, 2, 2);

    setLayout(layout);
    setWindowTitle(tr("Rechercher..."));

    connect(texteRecherche, SIGNAL(textChanged(const QString &)), this, SLOT(validerBouton()));
    connect(boutonRechercher, SIGNAL(clicked()), this, SLOT(clicRechercher()));
    connect(boutonFermer, SIGNAL(clicked()), this, SLOT(close()));
}

FindDialog::~FindDialog()
{
}

void FindDialog::validerBouton()
{
    boutonRechercher->setEnabled(!texteRecherche->text().isEmpty());
}

void FindDialog::clicRechercher()
{
    QString texte = texteRecherche->text();
    Qt::CaseSensitivity cs = respecterCasse->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    bool whole = wholeWords->isChecked();

    if (rechercheArriere->isChecked())
        emit rechercherPrecedent(texte, cs, whole);
    else
        emit rechercherSuivant(texte, cs, whole);
}
