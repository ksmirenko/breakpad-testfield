TEMPLATE = subdirs

CONFIG += c++11

SUBDIRS += \
	breakpad \
	gui

gui.depends = breakpad
