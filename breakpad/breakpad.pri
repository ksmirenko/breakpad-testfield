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

SOURCES +=

HEADERS +=\
	$$PWD/client/windows/common/auto_critical_section.h \
	$$PWD/client/windows/common/ipc_protocol.h \
	$$PWD/client/windows/crash_generation/client_info.h \
	$$PWD/client/windows/crash_generation/crash_generation_client.h \
	$$PWD/client/windows/crash_generation/crash_generation_server.h \
	$$PWD/client/windows/crash_generation/minidump_generator.h \
	$$PWD/client/windows/handler/exception_handler.h \
	$$PWD/client/windows/sender/crash_report_sender.h \
	$$PWD/client/minidump_file_writer-inl.h \
	$$PWD/client/minidump_file_writer.h \
	$$PWD/common/windows/dia_util.h \
	$$PWD/common/windows/guid_string.h \
	$$PWD/common/windows/http_upload.h \
	$$PWD/common/windows/omap.h \
	$$PWD/common/windows/omap_internal.h \
	$$PWD/common/windows/pdb_source_line_writer.h \
	$$PWD/common/windows/string_utils-inl.h \
	$$PWD/common/basictypes.h \
	$$PWD/common/byte_cursor.h \
	$$PWD/common/convert_UTF.h \
	$$PWD/common/dwarf_cfi_to_module.h \
	$$PWD/common/dwarf_cu_to_module.h \
	$$PWD/common/dwarf_line_to_module.h \
	$$PWD/common/language.h \
	$$PWD/common/md5.h \
	$$PWD/common/memory.h \
	$$PWD/common/memory_range.h \
	$$PWD/common/minidump_type_helper.h \
	$$PWD/common/module.h \
	$$PWD/common/scoped_ptr.h \
	$$PWD/common/simple_string_dictionary.h \
	$$PWD/common/stabs_reader.h \
	$$PWD/common/stabs_to_module.h \
	$$PWD/common/stdio.h \
	$$PWD/common/string_conversion.h \
	$$PWD/common/symbol_data.h \
	$$PWD/common/test_assembler.h \
	$$PWD/common/unordered.h \
	$$PWD/common/using_std_string.h \
	$$PWD/google_breakpad/common/breakpad_types.h \
	$$PWD/google_breakpad/common/minidump_cpu_amd64.h \
	$$PWD/google_breakpad/common/minidump_cpu_arm.h \
	$$PWD/google_breakpad/common/minidump_cpu_arm64.h \
	$$PWD/google_breakpad/common/minidump_cpu_mips.h \
	$$PWD/google_breakpad/common/minidump_cpu_ppc.h \
	$$PWD/google_breakpad/common/minidump_cpu_ppc64.h \
	$$PWD/google_breakpad/common/minidump_cpu_sparc.h \
	$$PWD/google_breakpad/common/minidump_cpu_x86.h \
	$$PWD/google_breakpad/common/minidump_exception_linux.h \
	$$PWD/google_breakpad/common/minidump_exception_mac.h \
	$$PWD/google_breakpad/common/minidump_exception_ps3.h \
	$$PWD/google_breakpad/common/minidump_exception_solaris.h \
	$$PWD/google_breakpad/common/minidump_exception_win32.h \
	$$PWD/google_breakpad/common/minidump_format.h \
	$$PWD/google_breakpad/common/minidump_size.h \
	$$PWD/google_breakpad/processor/basic_source_line_resolver.h \
	$$PWD/google_breakpad/processor/call_stack.h \
	$$PWD/google_breakpad/processor/code_module.h \
	$$PWD/google_breakpad/processor/code_modules.h \
	$$PWD/google_breakpad/processor/dump_context.h \
	$$PWD/google_breakpad/processor/dump_object.h \
	$$PWD/google_breakpad/processor/exploitability.h \
	$$PWD/google_breakpad/processor/fast_source_line_resolver.h \
	$$PWD/google_breakpad/processor/memory_region.h \
	$$PWD/google_breakpad/processor/microdump.h \
	$$PWD/google_breakpad/processor/microdump_processor.h \
	$$PWD/google_breakpad/processor/minidump.h \
	$$PWD/google_breakpad/processor/minidump_processor.h \
	$$PWD/google_breakpad/processor/proc_maps_linux.h \
	$$PWD/google_breakpad/processor/process_result.h \
	$$PWD/google_breakpad/processor/process_state.h \
	$$PWD/google_breakpad/processor/source_line_resolver_base.h \
	$$PWD/google_breakpad/processor/source_line_resolver_interface.h \
	$$PWD/google_breakpad/processor/stack_frame.h \
	$$PWD/google_breakpad/processor/stack_frame_cpu.h \
	$$PWD/google_breakpad/processor/stack_frame_symbolizer.h \
	$$PWD/google_breakpad/processor/stackwalker.h \
	$$PWD/google_breakpad/processor/symbol_supplier.h \
	$$PWD/google_breakpad/processor/system_info.h

LIBS += -L"$$_PRO_FILE_PWD/libs/common.lib"
LIBS += -L"$$_PRO_FILE_PWD/libs/crash_generation_client.lib"
LIBS += -L"$$_PRO_FILE_PWD/libs/crash_report_sender.lib"
LIBS += -L"$$_PRO_FILE_PWD/libs/exception_handler.lib"


unix {
	target.path = /usr/lib
	INSTALLS += target
}

DISTFILES += \
	breakpad.pri
