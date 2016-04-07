#include "crashHandler.h"

#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QCoreApplication>
#include <QString>

// for now Breakpad will work on Windows only
#include "client/windows/handler/exception_handler.h"

namespace Breakpad {
	class CrashHandlerPrivate
	{
	public:
		CrashHandlerPrivate()
		{
			pHandler = NULL;
		}

		~CrashHandlerPrivate()
		{
			delete pHandler;
		}

		void InitCrashHandler(const QString& dumpPath);
		static google_breakpad::ExceptionHandler* pHandler;
		static bool bReportCrashesToSystem;
	};

	google_breakpad::ExceptionHandler* CrashHandlerPrivate::pHandler = NULL;
	bool CrashHandlerPrivate::bReportCrashesToSystem = false;

	bool DumpCallback(
		const wchar_t* _dump_dir
		, const wchar_t* _minidump_id
		, void* context
		, EXCEPTION_POINTERS* exinfo
		, MDRawAssertionInfo* assertion
		, bool success
	)
	{
		Q_UNUSED(context);
		Q_UNUSED(_dump_dir);
		Q_UNUSED(_minidump_id);
		Q_UNUSED(assertion);
		Q_UNUSED(exinfo);

		/*
		NO STACK USE, NO HEAP USE THERE !!!
		Creating QString's, using qDebug, etc. - everything is crash-unfriendly.
		*/
		return CrashHandlerPrivate::bReportCrashesToSystem ? success : true;
	}

	void CrashHandlerPrivate::InitCrashHandler(const QString& dumpPath)
	{
		if (pHandler != NULL)
			return;

		std::wstring pathAsStr = (const wchar_t*)dumpPath.utf16();
		pHandler = new google_breakpad::ExceptionHandler(
			pathAsStr
			, /*FilterCallback*/ 0
			, DumpCallback
			, /*context*/ 0
			, true
		);
	}

	/************************************************************************/
	/* CrashHandler														 */
	/************************************************************************/
	CrashHandler* CrashHandler::instance()
	{
		static CrashHandler globalHandler;
		return &globalHandler;
	}

	CrashHandler::CrashHandler()
	{
		d = new CrashHandlerPrivate();
	}

	CrashHandler::~CrashHandler()
	{
		delete d;
	}

	void CrashHandler::setReportCrashesToSystem(bool report)
	{
		d->bReportCrashesToSystem = report;
	}

	bool CrashHandler::writeMinidump()
	{
		bool res = d->pHandler->WriteMinidump();
		if (res) {
			qDebug("BreakpadQt: writeMinidump() success.");
		} else {
			//qWarning("BreakpadQt: writeMinidump() failed.");
			qDebug("BreakpadQt: writeMinidump() failed.");
		}
		return res;
	}

	void CrashHandler::Init(const QString& reportPath)
	{
		d->InitCrashHandler(reportPath);
		qDebug("Breakpad initialized!");
	}
}
