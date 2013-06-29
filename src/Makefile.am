# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c99 -O2 -D_XOPEN_SOURCE -D_XOPEN_SOURCE_EXTENDED
AM_LDFLAGS = -lc

lib_LIBRARIES = libmanchicken.a
include_HEADERS = mutable_string.h findbin.h manchicken.h swansong.h dynamic_list.h dynamic_csv.h
libmanchicken_a_SOURCES = mutable_string.c findbin.c swansong.c dynamic_list.c dynamic_csv.c