#include "mainwindow.h"

#include <string>
#include <QApplication>
#include <QString>
#include <QStandardPaths>

#include <crashHandler.h>

//const QString& DUMP_PATH = QString("dumps\\");
const QString& DUMP_PATH = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow w;
	w.show();

	qDebug("Minidump path: " + DUMP_PATH.toLatin1());
	// initializing Breakpad
	Breakpad::CrashHandler* pHandler = Breakpad::CrashHandler::instance();
	pHandler->Init(DUMP_PATH);

	int res = app.exec();

	return res;
}
