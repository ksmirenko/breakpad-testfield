#include "mainwindow.h"

#include <string>
#include <QApplication>

#include <client/windows/handler/exception_handler.h>

const std::wstring DUMP_PATH = L"dumps\\";

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow w;
	w.show();

	// Creates a new ExceptionHandler instance to handle writing minidumps.
	// Before writing a minidump, the optional filter callback will be called.
	// Its return value determines whether or not Breakpad should write a
	// minidump.  Minidump files will be written to dump_path, and the optional
	// callback is called after writing the dump file, as described above.
	// handler_types specifies the types of handlers that should be installed.

	google_breakpad::ExceptionHandler *excHandler;
	excHandler = new google_breakpad::ExceptionHandler(
		DUMP_PATH
		, 0
		, 0
		, 0
		, google_breakpad::ExceptionHandler::HANDLER_ALL
	);

//	google_breakpad::ExceptionHandler *excHandler = new google_breakpad::ExceptionHandler(
//		L"dumps\\"
//		, /* FilterCallback */ 0
//		, /* MinidumpCallback */ 0
//		, /* context */ 0
//		, google_breakpad::ExceptionHandler::HANDLER_ALL
//		, MiniDumpNormal
//		, L""
//		, 0
//	);

	int res = app.exec();

	delete excHandler;

	return res;
}
