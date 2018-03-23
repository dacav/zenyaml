check_PROGRAMS = happypath
TESTS = $(check_PROGRAMS)

happypath_CPPFLAGS = -I$(top_srcdir)/zenyaml/include/
happypath_SOURCES = happypath.cc
happypath_LDADD = ../zenyaml/libzenyaml.la -lyaml
happypath_LDFLAGS = -no-install
