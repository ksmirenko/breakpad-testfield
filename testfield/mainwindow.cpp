#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <csignal>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->breakButton, SIGNAL(clicked()), this, SLOT(doBreak()));
	ui->breakButton->setFocus();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void kaboom()
{
	raise(SIGSEGV);
}

void MainWindow::doBreak()
{
//	QMessageBox msgBox;
//	msgBox.setText("The app will crash now.");
//	msgBox.exec();

	// EXCEPTION_INT_DIVIDE_BY_ZERO
//	int foo = 0;
//	int bar = 42 / foo;
//	Q_UNUSED(bar)

	// EXCEPTION_ACCESS_VIOLATION_WRITE
//	int* p0 = nullptr;
//	*p0 = 42;

	// EXCEPTION_ACCESS_VIOLATION_READ
//	int arr[10];
//	arr[10] = 4;
//	Q_UNUSED(arr)

	// just do it
//	kaboom();

	// std_terminate
//	throw QString("Oh, hello there!");

	// std_terminate
	QObject *obj = new QObject();
	delete obj;
	delete obj;
}
