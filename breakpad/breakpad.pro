#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T15:20:21
#
#-------------------------------------------------

QT       -= core gui

TARGET = breakpad
TEMPLATE = lib

DEFINES += BREAKPAD_LIBRARY

SOURCES += breakpad.cpp

HEADERS += breakpad.h\
        breakpad_global.h \
    src/client/windows/common/auto_critical_section.h \
    src/client/windows/common/ipc_protocol.h \
    src/client/windows/crash_generation/client_info.h \
    src/client/windows/crash_generation/crash_generation_client.h \
    src/client/windows/crash_generation/crash_generation_server.h \
    src/client/windows/crash_generation/minidump_generator.h \
    src/client/windows/handler/exception_handler.h \
    src/client/windows/sender/crash_report_sender.h \
    src/client/minidump_file_writer-inl.h \
    src/client/minidump_file_writer.h \
    src/common/windows/dia_util.h \
    src/common/windows/guid_string.h \
    src/common/windows/http_upload.h \
    src/common/windows/omap.h \
    src/common/windows/omap_internal.h \
    src/common/windows/pdb_source_line_writer.h \
    src/common/windows/string_utils-inl.h \
    src/common/basictypes.h \
    src/common/byte_cursor.h \
    src/common/convert_UTF.h \
    src/common/dwarf_cfi_to_module.h \
    src/common/dwarf_cu_to_module.h \
    src/common/dwarf_line_to_module.h \
    src/common/language.h \
    src/common/md5.h \
    src/common/memory.h \
    src/common/memory_range.h \
    src/common/minidump_type_helper.h \
    src/common/module.h \
    src/common/scoped_ptr.h \
    src/common/simple_string_dictionary.h \
    src/common/stabs_reader.h \
    src/common/stabs_to_module.h \
    src/common/stdio.h \
    src/common/string_conversion.h \
    src/common/symbol_data.h \
    src/common/test_assembler.h \
    src/common/unordered.h \
    src/common/using_std_string.h \
    src/google_breakpad/common/breakpad_types.h \
    src/google_breakpad/common/minidump_cpu_amd64.h \
    src/google_breakpad/common/minidump_cpu_arm.h \
    src/google_breakpad/common/minidump_cpu_arm64.h \
    src/google_breakpad/common/minidump_cpu_mips.h \
    src/google_breakpad/common/minidump_cpu_ppc.h \
    src/google_breakpad/common/minidump_cpu_ppc64.h \
    src/google_breakpad/common/minidump_cpu_sparc.h \
    src/google_breakpad/common/minidump_cpu_x86.h \
    src/google_breakpad/common/minidump_exception_linux.h \
    src/google_breakpad/common/minidump_exception_mac.h \
    src/google_breakpad/common/minidump_exception_ps3.h \
    src/google_breakpad/common/minidump_exception_solaris.h \
    src/google_breakpad/common/minidump_exception_win32.h \
    src/google_breakpad/common/minidump_format.h \
    src/google_breakpad/common/minidump_size.h \
    src/google_breakpad/processor/basic_source_line_resolver.h \
    src/google_breakpad/processor/call_stack.h \
    src/google_breakpad/processor/code_module.h \
    src/google_breakpad/processor/code_modules.h \
    src/google_breakpad/processor/dump_context.h \
    src/google_breakpad/processor/dump_object.h \
    src/google_breakpad/processor/exploitability.h \
    src/google_breakpad/processor/fast_source_line_resolver.h \
    src/google_breakpad/processor/memory_region.h \
    src/google_breakpad/processor/microdump.h \
    src/google_breakpad/processor/microdump_processor.h \
    src/google_breakpad/processor/minidump.h \
    src/google_breakpad/processor/minidump_processor.h \
    src/google_breakpad/processor/proc_maps_linux.h \
    src/google_breakpad/processor/process_result.h \
    src/google_breakpad/processor/process_state.h \
    src/google_breakpad/processor/source_line_resolver_base.h \
    src/google_breakpad/processor/source_line_resolver_interface.h \
    src/google_breakpad/processor/stack_frame.h \
    src/google_breakpad/processor/stack_frame_cpu.h \
    src/google_breakpad/processor/stack_frame_symbolizer.h \
    src/google_breakpad/processor/stackwalker.h \
    src/google_breakpad/processor/symbol_supplier.h \
    src/google_breakpad/processor/system_info.h \
    src/exception_handler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
