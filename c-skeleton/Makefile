# ===== The Header Stuff =====
# Set CFLAGS (compiler flags)
# Note:  -Isrc tells the compiler to look in the src folder for files
# Note $(OPTFLAGS) -- the user may add his/her own OPTFLAGS as optionsin addition to the CFLAGS; but he/she should leave CFLAGS alone
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)

#Options used when linking a library -- the user may specify OBTLIBS
LIBS=-ldl $(OPTLIBS)

# The ?= notation checks to see if PREFIX is set. If not set, then the Makefile sets it
PREFIX?=/usr/local


# SOURCES: This line dynamically creates the SOURCES variable using a wildcard.  
# 1st parameter picks up .c files in subfolders of src/
# 2nd parameter picks up .c files in the src folder (the main folder)
SOURCES=$(wildcard src/**/*.c src/*.c)

# Create the OBJECTS variable by looking at the SOURCES variable, changing the %.c extensions to %.o, then assigning that list to OBJECTS 
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

# Use the wildcard again to find all test source files
TEST_SRC=$(wildcard test/*_tests.c)

# Use the patsubst trick to get all the TEST targets.  This time, we strip the .c extension (instead of making .o files)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

# We specify that the build target is "libYOUR_LIBRARY.a" (where you specify what YOUR_LIBRARY is)
TARGET=build/libYOUR_LIBRARY.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# ===== The Target Build =====

# By default, make builds the first target if no targets are specified on the command line.
# Here, the first target is "all"
all: $(TARGET) $(SO_TARGET) tests

# The following is a makefile trick that, in effect, "piggybacks" on another target.  (i.e. you can change options for a given target)
# Step 1: Specify a target name on one line, with flags
# Step 2: On the next line, use the same target name, with the target to 'piggyback' on
dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all


# Builds the target library (whatever it is -- assuming the user specifies it at the command line)
# Here, we use the same 'piggybacking' trick
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

# Notes from above:  The ar command actually makes the TARGET
# The syntax $@ $(OBJECTS) is a way of saying, "put the target for this Makefile source here, and all the OBJECTS after that"
# Here, the $@ maps back to the $(TARGET) above (line 47), which in turn, maps back to build/libYOUR_LIBRARY.a
# Finally, to make the library, run ranlib


$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# ===== The Unit Tests =====

# Make the tests target "phony" -- this ensures that make runs and builds the target, even if there is a folder or file with the same name as the target. Normally, make would skip a target if it sees that the target file is already built/up to date.   
#(so e.g. we have a "tests" target and also a "tests" folder. We declare the "tests" target as PHONY, so that make to runs and builds the tests target, if specified.
.PHONY: tests

# Use the 'piggyback' trick again for the tests target
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# Notes on the clean target:
# 1st line removes build folder, as well as build objects and test executables
# 2nd line removes the test log
# 3rd line removes some junk that the compiler leaves behind
# 4th line removes junk that Apple's XCode leaves behind


# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
# The following appears to be a nonsensically long regular expression
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

# Note about the Checker - It has a big-ass regex to check for 'bad functions', like strcpy (stuff that could allow for buffer overflows and such?
# Also, the || true at the end of egrep is there to prevent make from thinking that a search returning no results is a failure
