#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->breakButton, SIGNAL(clicked()), this, SLOT(handleBreakButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleBreakButton()
{
    QMessageBox msgBox;
    msgBox.setText("The app will crash now.");
    msgBox.exec();
    int foo = 0;
    int bar = 42 / foo; // KABOOM
    (void)bar;
}
