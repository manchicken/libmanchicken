#
# libmanchicken - Copyright (C) 2013 Michael D. Stemle, Jr.
#
# This file is part of libmanchicken.
#
# libmanchicken is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libmanchicken is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with libmanchicken. If not, see <http://www.gnu.org/licenses/>.

SRCDIR = ./src
INCDIR = ./include
OBJDIR = ./obj
LIBDIR = ./lib
TESTDIR = ./t
TESTOBJDIR = ./t/obj

CC = gcc
AR = ar -cr
RANLIB = ranlib
RM = rm -f

CFLAGS = -fPIC -ggdb3 -I$(INCDIR) -Wall

# Sources
LIBMANCHICKEN_SRCS = \
	$(OBJDIR)/mutable_string.c \

TESTS_SRCS = \
	$(TESTDIR)/t_mutable_string.c \

# Objects
LIBMANCHICKEN_OBJS = \
	$(OBJDIR)/mutable_string.o \

TESTS_OBJS = \
	$(TESTOBJDIR)/t_mutable_string.o \

# Libraries
LIBS = \
	$(LIBDIR)/libmanchicken.a \

# Binaries
TESTS = \
	$(TESTDIR)/t_mutable_string.test

# Flags
TESTS_LDFLAGS = -L$(LIBDIR) -lc -lcunit -lmanchicken

.PHONY: all
all: $(LIBS) $(TESTS)
	ctags -R -f .tags

.PHONY: rebuild
rebuild: clean all

# Tests
$(TESTDIR)/%.test: $(TESTOBJDIR)/%.o $(LIBDIR)/libmanchicken.a
	$(CC) -o $@ $(TESTS_LDFLAGS) $<

# Libs
$(LIBDIR)/libmanchicken.a: $(LIBMANCHICKEN_OBJS)
	$(AR) $@ $<
	$(RANLIB) $@

# Other stuff (generic)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

$(TESTOBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

.PHONY: clean
clean:
	$(RM) $(OBJDIR)/*.o $(LIBDIR)/*.a $(TESTS) $(TESTOBJDIR)/*.o

.PHONY: tags
tags:
	ctags -R -f .tags
