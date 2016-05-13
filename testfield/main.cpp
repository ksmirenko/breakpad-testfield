#include "mainwindow.h"

#include <string>
#include <QApplication>
#include <QString>
#include <QStandardPaths>

#if defined(Q_OS_WIN32)
#include <crashHandler.h>
#endif

//const QString& DUMP_PATH = QString("dumps\\");
const QString& DUMP_PATH = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow w;
	w.show();

	qDebug("Minidump path: " + DUMP_PATH.toLatin1());
#if defined(Q_OS_WIN32)
	// initializing Breakpad - for now only on Windows
	Breakpad::CrashHandler* pHandler = Breakpad::CrashHandler::instance();
	pHandler->Init(DUMP_PATH);
#endif

	int res = app.exec();

	return res;
}
