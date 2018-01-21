# SQLiteToolBox
#
# Copyright (C) 2014  Frank Sommer
#
# Makefile for  
# sqliteDBinfo and sqlite2csv
# 

CC=gcc
CFLAGS=-Wall -std=c99

SRCDIR = ./source
EXECDIR = ./DEB/bin
MANDIR = ./DEB/usr/share/man/man1
OBJ = *.o
BAK = *~

all:  deb exec man

deb: sqliteDBinfo sqlite2csv
	strip $(EXECDIR)/sqlite2csv
	strip $(EXECDIR)/sqliteDBinfo
	dpkg -b ./DEB sqlitetoolbox.deb

exec: sqliteDBinfo sqlite2csv 
	mkdir -p $(EXECDIR)

sqliteDBinfo: $(SRCDIR)/sqliteDBinfo.c
	$(CC) -Wall -std=c99 $(SRCDIR)/sqliteDBinfo.c -o $(EXECDIR)/sqliteDBinfo -lsqlite3

sqlite2csv: $(SRCDIR)/sqlite2csv.c
	$(CC) -Wall -std=c99 $(SRCDIR)/sqlite2csv.c -o $(EXECDIR)/sqlite2csv -lsqlite3

man: sqliteDBinfo.man sqlite2csv.man
	mkdir -p $(MANDIR)

sqliteDBinfo.man: $(SRCDIR)/man/sqliteDBinfo.1
	gzip -c $(SRCDIR)/man/sqliteDBinfo.1 > $(MANDIR)/sqliteDBinfo.1.gz

sqlite2csv.man: $(SRCDIR)/man/sqlite2csv.1
	gzip -c $(SRCDIR)/man/sqlite2csv.1 > $(MANDIR)/sqlite2csv.1.gz
	
clean:
	rm -rf $(OBJ) $(BAK)
