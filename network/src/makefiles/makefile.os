# ------------------------------------------------------------------------------
#
# makefile.os
#
# libnetwork library version 7.0.0 release 1
#
# copyright 2001-2016 Code Construct Systems (CCS) ( CONFIDENTIAL/PROPRIETARY )
#
# ------------------------------------------------------------------------------

# Open systems OS/OE port

#
# network library name.
#
TARGET = libnetwork.a

#
# Include flags.
#
INCLUDE = -I.

#
# C compiler definitions and flags.
#
CC = c99
CDEBUG = -g
COPTIMIZE = -O3
CDEFS = -D_POSIX_ENVIRONMENT -D_POSIX_SOURCE
CFLAGS = -c $(CDEBUG) $(COPTIMIZE) -ansi -pedantic -std=c99 $(CDEFS)

#
# C compiler warning flags.
#
CWARNS = -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-declarations -Wmissing-include-dirs -Wno-unused-parameter -Wuninitialized -Wold-style-definition -Wstrict-prototypes -Wmissing-prototypes

#
# Archiver and flags.
#
AR = ar
ARFLAGS = crvs

#
# Library path.
#
LIB = ../lib

#
# List of include files.
#
INCLUDES = \
 	network.h

#
# List of object files.
#
OBJECTS = \
	http.o \
	httputil.o \
	net.o \
	netlogs.o \
	debug.o \
	utils.o \
	version.o

all: $(TARGET)

#
# Rule for creating the network library file.
#
$(TARGET): $(OBJECTS)
	@$(AR) $(ARFLAGS) $@ $(OBJECTS)
	mv $(TARGET) $(LIB)
	cp $(INCLUDES) ../inc

#
# Rule for building HTTP networking functions object.
#
http.o: http.c 
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building HTTP networking utility functions object.
#
httputil.o: httputil.c 
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building TCP/IP network interface functions object.
#
net.o: net.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building library logging functions object.
#
netlogs.o: netlogs.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building debug functions object.
#
debug.o: debug.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building utility functions object.
#
utils.o: utils.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for building library version information object.
#
version.o: version.c
	@echo "building $@"
	@$(CC) $(CFLAGS) $(INCLUDE) $(CWARNS) -o $@ $<

#
# Rule for cleaning out generated files.
#
clean:
	rm -f *.o

# ------------------------------------------------------------------------------
