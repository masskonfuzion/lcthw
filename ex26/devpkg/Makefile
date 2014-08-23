# Set prefix
PREFIX?=/usr/local

# Set compiler flags
CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1 -I${PREFIX}/apr/include/apr-util-1

# Linker flags
LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

# "all" target depends on devpkg
all: devpkg

# "devpkg" target depends on bstrlib.o, db.o, shell.o, and commands.o
devpkg: bstrlib.o db.o shell.o commands.o

install: all
	install -d $(DESTDIR)/$(PREFIX)/bin/
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

clean:
	rm -f *.o
	rm -f devpkg
	rm -rf *.dSYM

