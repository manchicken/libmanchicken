# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c99 -ggdb3 -I../src
AM_LDFLAGS = -lc -L../src -lmanchicken
LDADD = -L../src -lmanchicken

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
noinst_PROGRAMS = t_mutable_string t_findbin t_swansong t_dynamic_list t_single_linked_list
t_mutable_string_SOURCES = t_mutable_string.c
t_mutable_string_LDADD = ../src/libmanchicken.a

t_findbin_SOURCES = t_findbin.c
t_findbin_LDADD = ../src/libmanchicken.a

t_swansong_SOURCES = t_swansong.c
t_swansong_LDADD = ../src/libmanchicken.a

t_dynamic_list_SOURCES = t_dynamic_list.c
t_dynamic_list_LDADD = ../src/libmanchicken.a

t_single_linked_list_SOURCES = t_single_linked_list.c
t_single_linked_list_LDADD = ../src/libmanchicken.a