TEMPLATE = subdirs

CONFIG += c++11

SUBDIRS += \
	breakpad \
	testfield

testfield.depends = breakpad

QMAKE_LFLAGS_RELEASE += -MAP
QMAKE_CFLAGS_RELEASE += -Zi
QMAKE_LFLAGS_RELEASE += -debug -opt:ref
