# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c99 -ggdb3 -I../src
AM_LDFLAGS = -lc -L../src -lmanchicken
# LDADD = ../lib/libmanchicken.a

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
noinst_PROGRAMS = t_mutable_string t_findbin
t_mutable_string_SOURCES = t_mutable_string.c
t_findbin_SOURCES = t_findbin.c
