# Copyright 2016 Kirill Smirenko
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

QT -= gui

TARGET = breakpad
TEMPLATE = lib

DEFINES += BREAKPAD_LIBRARY

INCLUDEPATH +=\
	$$PWD \
	$$PWD/src

SOURCES += crashHandler.cpp
HEADERS += crashHandler.h

# Windows
SOURCES +=\
	$$PWD/client/windows/crash_generation/crash_generation_client.cc \
	$$PWD/client/windows/handler/exception_handler.cc \
	$$PWD/client/windows/sender/crash_report_sender.cc \
	$$PWD/common/windows/guid_string.cc \
	$$PWD/common/windows/http_upload.cc \
	$$PWD/common/windows/string_utils.cc

HEADERS +=\
	$$PWD/client/windows/common/ipc_protocol.h \
	$$PWD/client/windows/crash_generation/crash_generation_client.h \
	$$PWD/client/windows/handler/exception_handler.h \
	$$PWD/client/windows/sender/crash_report_sender.h \
	$$PWD/common/scoped_ptr.h \
	$$PWD/common/windows/guid_string.h \
	$$PWD/common/windows/http_upload.h \
	$$PWD/common/windows/string_utils-inl.h \
	$$PWD/google_breakpad/common/breakpad_types.h \
	$$PWD/google_breakpad/common/minidump_format.h

win32 {
	LIBS += -lwininet
}


DISTFILES += \
	breakpad.pri

CONFIG+=warn_off
