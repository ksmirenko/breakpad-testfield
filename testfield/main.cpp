#include "mainwindow.h"

#include <exception>
#include <string>
#include <QApplication>
#include <QString>
#include <QStandardPaths>
#include <QDebug>

#if defined(Q_OS_WIN32)
#include <crashHandler.h>
#endif

// TODO: this should be moved to some configuration file
const std::wstring DUMP_PATH = L"";
//const QString &DUMP_PATH =
//	QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
const std::wstring PRODUCT_NAME = L"BreakpadTestfield";

void onTerminate() {
	qDebug() << "Terminate intercepted";
//	QApplication::exit(-1);
	std::exit(-1);
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setApplicationVersion(APP_VERSION);
	MainWindow w;
	w.show();

#if defined(Q_OS_WIN32)
	// initializing Breakpad - for now only on Windows
	Breakpad::CrashHandler* crashHandler = Breakpad::CrashHandler::instance();
	crashHandler->Init(
		DUMP_PATH
		, PRODUCT_NAME
		, app.applicationVersion().toStdWString()
	);
#endif

	int res = app.exec();

	return res;
}
