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

#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QCoreApplication>
#include <QString>

// for now Breakpad will work on Windows only
#include "client/windows/handler/exception_handler.h"
#include "client/windows/sender/crash_report_sender.h"

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

		void InitCrashHandler(const QString &dumpPath);
		static google_breakpad::ExceptionHandler *pHandler;
		static bool bReportCrashesToSystem;
	};

	const int MAX_REPORTS_PER_DAY = 5;
	const std::wstring &REPORT_URL = L"http://caliper-ksmirenko.rhcloud.com/crash_upload";
	
	google_breakpad::ExceptionHandler *CrashHandlerPrivate::pHandler = NULL;
	bool CrashHandlerPrivate::bReportCrashesToSystem = true;

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
		const std::map<std::wstring, std::wstring> params;
		std::map<std::wstring, std::wstring> files;
		// Reconstructing exact name of generated minidump file
		//std::wstring key = std::wstring(minidumpId);
		std::wstring filename = dumpPath;
		filename += L"\\";
		filename += minidumpId;
		filename += L".dmp";
		files.insert(std::pair<std::wstring, std::wstring>(L"", filename));
		// Sending the report
		const google_breakpad::ReportResult res = sender.SendCrashReport(REPORT_URL, params, files, 0);
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

		return CrashHandlerPrivate::bReportCrashesToSystem ? success : true;
	}

	void CrashHandlerPrivate::InitCrashHandler(const QString &dumpPath)
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

	void CrashHandler::Init(const QString& dumpPath)
	{
		d->InitCrashHandler(dumpPath);
		qDebug("Breakpad initialized!");
	}
}
