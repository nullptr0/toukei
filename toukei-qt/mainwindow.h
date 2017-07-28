#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <memory>
#include "ankidb.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Ankidb> db;
    std::vector<Deck> decks;


public slots:
    void openFile();
    void selectDeck(QListWidgetItem *cur, QListWidgetItem *prev);
};

#endif // MAINWINDOW_H
