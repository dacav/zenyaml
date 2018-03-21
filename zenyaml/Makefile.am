lib_LTLIBRARIES = libzenyaml.la
include_HEADERS = \
	include/zenyaml/datatypes.h \
	include/zenyaml/parser.h

libzenyaml_la_CPPFLAGS = -I./include/
libzenyaml_la_SOURCES = \
	datatypes.cc $(include_HEADERS)/datatypes.h \
	parser.cc $(include_HEADERS)/parser.h
