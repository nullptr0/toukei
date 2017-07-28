#include <QFileDialog>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->deckList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(selectDeck(QListWidgetItem*,QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open FIle"), "/home");
    if (fileName.isEmpty())
        return;
    db = std::unique_ptr<Ankidb>(new Ankidb(fileName.toStdString()));

    decks = db->getDecks();

    for(int i = 0; i < decks.size(); i++){
        Deck &d = decks[i];
        QString name = QString::fromStdString(d.get_name());
        QListWidgetItem *item = new QListWidgetItem(name, ui->deckList);
        item->setData(Qt::UserRole, QVariant(i));
        //ui->deckList->addItem(item);
    }
}

void MainWindow::selectDeck(QListWidgetItem *cur, QListWidgetItem *prev){
    int idx = cur->data(Qt::UserRole).toInt();

    Deck &d = decks[idx];
    ui->deckLabel->setText(QString::fromStdString(d.get_name()));
}
