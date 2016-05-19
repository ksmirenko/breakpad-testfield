/* Copyright 2016 Kirill Smirenko
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "crashHandler.h"

#include <map>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QCoreApplication>
#include <QString>

#include <QDebug>

// for now Breakpad will work on Windows only
#include "client/windows/handler/exception_handler.h"
#include "client/windows/sender/crash_report_sender.h"

namespace Breakpad {
	class CrashHandlerPrivate
	{
	public:
		CrashHandlerPrivate()
		{
			exceptionHandler = NULL;
			dumpPath = NULL;
		}

		~CrashHandlerPrivate()
		{
			delete exceptionHandler;
			delete dumpPath;
		}

		void InitCrashHandler(std::wstring dumpPath);
		static google_breakpad::ExceptionHandler *exceptionHandler;
		static bool shouldReportCrashes;
		static std::wstring	*dumpPath;
	};

	const int MAX_REPORTS_PER_DAY = 5;
	// TODO: this should be moved to some configuration file
//	const std::wstring &REPORT_URL = L"http://caliper-ksmirenko.rhcloud.com/crash_upload";
	const std::wstring &REPORT_URL = L"http://127.0.0.1:3000/crash_upload";

	std::wstring productName = L"";
	std::wstring productVersion = L"";

	google_breakpad::ExceptionHandler *CrashHandlerPrivate::exceptionHandler = NULL;
	bool CrashHandlerPrivate::shouldReportCrashes = true;
	std::wstring *CrashHandlerPrivate::dumpPath = NULL;

	bool FilterCallback(
		void* context
		, EXCEPTION_POINTERS *exinfo
		, MDRawAssertionInfo *assertion
	) {
		Q_UNUSED(context)
		Q_UNUSED(exinfo)
		Q_UNUSED(assertion)
		qDebug() << "FilterCallback called";
		return true;
	}

	/// Callback that is called after minidumps have been written
	bool DumpCallback(
		const wchar_t *dumpPath
		, const wchar_t *minidumpId
		, void* context
		, EXCEPTION_POINTERS *exinfo
		, MDRawAssertionInfo *assertion
		, bool success
	)
	{
		Q_UNUSED(context);
#if defined(Q_OS_WIN32)
		Q_UNUSED(assertion);
		Q_UNUSED(exinfo);
#endif

		google_breakpad::CrashReportSender sender(dumpPath);
		sender.set_max_reports_per_day(MAX_REPORTS_PER_DAY);
		// Adding parameters
		std::map<std::wstring, std::wstring> params;
		params[L"prod"] = productName;
		params[L"ver"] = productVersion;
		// Reconstructing exact name of generated minidump file
		std::wstring filename = minidumpId;
		filename += L".dmp";
		std::wstring filenameFull = dumpPath;
		filenameFull += L"/";
		filenameFull += filename;
		// Sending the report
		const google_breakpad::ReportResult res = sender.SendCrashReport(REPORT_URL, params, filenameFull, 0);
		// Notifying user about report sending result
		wchar_t *msg;
		switch (res)
		{
			case google_breakpad::RESULT_SUCCEEDED:
				msg = L"Crash report was SENT and accepted by the server.";
			break;
			case google_breakpad::RESULT_REJECTED:
				msg = L"Crash report was sent, but the server REJECTED it.";
			break;
			case google_breakpad::RESULT_THROTTLED:
				msg = L"Crash report was not sent due to exceeding day LIMIT.";
			break;
			default:
				msg = L"Failed to communicate with the server.";
			break;
		}
		MessageBox(0, msg, L"Crash report", MB_OK|MB_ICONINFORMATION);

		return CrashHandlerPrivate::shouldReportCrashes ? success : true;
	}

	void terminateHandler()
	{
		google_breakpad::ExceptionHandler::WriteMinidump(
			*CrashHandlerPrivate::dumpPath
			, DumpCallback
			, NULL
		);
	}

	void CrashHandlerPrivate::InitCrashHandler(std::wstring dumpPath) {
		if (exceptionHandler != NULL)
			return;

//		std::wstring pathAsStr = (const wchar_t*)dumpPath.utf16();
		exceptionHandler = new google_breakpad::ExceptionHandler(
			dumpPath
			, FilterCallback
			, DumpCallback
			, /*context*/ 0
			, google_breakpad::ExceptionHandler::HANDLER_ALL
		);

		CrashHandlerPrivate::dumpPath = new std::wstring(dumpPath);
		std::set_terminate(terminateHandler);
	}


	/************************************************************************/
	/* CrashHandler                                                         */
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
		d->shouldReportCrashes = report;
	}

	bool CrashHandler::writeMinidump()
	{
		bool res = d->exceptionHandler->WriteMinidump();
		return res;
	}

	void CrashHandler::Init(std::wstring dumpPath, std::wstring name, std::wstring version)
	{
		productName = name;
		productVersion = version;
		d->InitCrashHandler(dumpPath);
		qDebug() << "Breakpad initialized!";
	}
}
