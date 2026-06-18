#===========================================================================
#
#Makefile --
#
#
#Wolfram Schenck <wolfram.schenck@fh-bielefeld.de>
#     Copyright (C) 2015
#     Engineering Informatics
#     Department of Engineering Sciences and Mathematics
#     University of Applied Sciences Bielefeld
#
#1.2 / 13. Oct 15 (ws)
#
#
#===========================================================================

BIN      = main.exe

CC       = gcc
CFLAGS   = -D_GNU_SOURCE -Wall -g
CPP      = g++
CPPFLAGS = -D_GNU_SOURCE -Wall -g
LNFLAGS  = -Wall

# Шукаємо всі файли у папці
CFILES   := $(wildcard *.c)
OBJS1    := $(CFILES:.c=.o)

CPPFILES := $(wildcard *.C)
OBJS2    := $(CPPFILES:.C=.o)

HEADERFILES := $(wildcard *.H)

# Правило для .c файлів
%.o: %.c $(HEADERFILES)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $<

# Правило для .C (C++) файлів
%.o: %.C $(HEADERFILES)
	@echo "Compiling $<..."
	$(CPP) $(CPPFLAGS) -c $<

all: $(BIN)

# Лінкування
$(BIN): $(OBJS2) $(OBJS1)
	@echo "Linking $@..."
	$(CPP) $(LNFLAGS) -o $@ $(OBJS2) $(OBJS1)

# Очищення проєкту
clean:
	@echo "Cleaning files..."
	rm -f *.o *~ $(BIN)

#
# Bedeutung Makefile Makros:
#
# $< the name of the related file that caused the action.
# $* the prefix shared by target and dependent files.
# $@ is the name of the file to be made.
# $? is the names of the changed dependents.
