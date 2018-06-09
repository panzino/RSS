## RSS Makefile
## COPIED FROM SCHOOL PROJECT W/ CHANGES. HOPEFULLY IT WORKS

# The main driver of the project
EXECUTABLE 	= RSS

# designate which compiler to use
CXX			= g++

# list of test drivers (with main()) for development
TESTSOURCES = $(wildcard test*.cpp)
# names of test executables
TESTS       = $(TESTSOURCES:%.cpp=%)

# list of sources used in project
SOURCES 	= $(wildcard *.cpp)
SOURCES     := $(filter-out $(TESTSOURCES), $(SOURCES))
# list of objects used in project
OBJECTS		= $(SOURCES:%.cpp=$(ODIR)/%.o)

# If main() is in another file delete the line above, edit and uncomment below
PROJECTFILE = main.cpp

# If we want to make a tarball of this directory
TAR = RSS.tar.gz

#Default Flags
#CXXFLAGS = -std=c++14 -Wall -Werror -Wextra -pedantic
CXXFLAGS = -std=c++14 -I$(IDIR)
LDFLAGS = -L/usr/local/lib
LDLIBS = -lcurl -ltidy

#Define directories for cleaner directory
IDIR = ../include
ODIR = obj
LDIR = ../lib


# make release - will compile "all" with $(CXXFLAGS) and the -O3 flag
#				 also defines NDEBUG so that asserts will not check
release: CXXFLAGS += -O3 -DNDEBUG
release: all

# make debug - will compile "all" with $(CXXFLAGS) and the -g flag
#              also defines DEBUG so that "#ifdef DEBUG /*...*/ #endif" works
debug: CXXFLAGS += -g3 -DDEBUG
debug: clean all

# make profile - will compile "all" with $(CXXFLAGS) and the -pg flag
profile: CXXFLAGS += -pg
profile: clean all

# highest target; sews together all objects into executable
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
ifeq ($(EXECUTABLE), executable)
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJECTS) $(LDLIBS)
else
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJECTS) $(LDLIBS) -o $(EXECUTABLE)
endif

# Automatically generate any build rules for test*.cpp files
define make_tests
    ifeq ($$(PROJECTFILE),)
	    @echo Edit PROJECTFILE variable to .cpp file with main\(\)
	    @exit 1
    endif
    SRCS = $$(filter-out $$(PROJECTFILE), $$(SOURCES))
    OBJS = $$(SRCS:%.cpp=%.o)
    HDRS = $$(wildcard *.h)
    $(1): CXXFLAGS += -g3 -DDEBUG
    $(1): $$(OBJS) $$(HDRS) $(1).cpp
	$$(CXX) $$(CXXFLAGS) $$(OBJS) $(1).cpp -o $(1)
endef
$(foreach test, $(TESTS), $(eval $(call make_tests, $(test))))

alltests: clean $(TESTS)

# rule for creating objects
$(ODIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $*.cpp

# make clean - remove .o files, executables, tarball
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TESTS) $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE)

# make fullsubmit.tar.gz - cleans, runs dos2unix, creates tarball including test cases
TARs=$(filter-out $(TESTSOURCES), $(wildcard Makefile *.h *.cpp test*.txt))
$(TAR): $(TAR)
	rm -f $(TAR)
	-dos2unix $(TARs)
	tar -vczf $(TAR) $(TARs)
	@echo !!! Tarball Finished !!!

# shortcut for making tarball
tarball: $(TAR)

define MAKEFILE_HELP
EECS281 Advanced Makefile Help
* This Makefile uses advanced techniques, for more information:
    $$ man make

* General usage
    1. Follow directions at each "TODO" in this file.
       a. Set EXECUTABLE equal to the name given in the project specification.
       b. Set PROJECTFILE equal to the name of the source file with main()
       c. Add any dependency rules specific to your files.
    2. Build, test, submit... repeat as necessary.

* Preparing submissions
    A) To build 'partialsubmit.tar.gz', a tarball without tests used to find
       buggy solutions in the autograder.  This is useful for faster autograder
       runs during development and free submissions if the project does not
       build.
           $$ make partialsubmit
    B) Build 'fullsubmit.tar.gz' a tarball complete with autograder test cases.
       ALWAYS USE THIS FOR FINAL GRADING!  It is also useful when trying to
       find buggy solutions in the autograder.
           $$ make fullsubmit

* Unit testing support
    A) Source files for unit testing should be named test*.cpp.  Examples
       include test_input.cpp or test3.cpp.
    B) Automatic build rules are generated to support the following:
           $$ make test_input
           $$ make test3
           $$ make alltests        (this builds all test drivers)
    C) If test drivers need special dependencies, they must be added manually.
    D) IMPORTANT: NO SOURCE FILES THAT BEGIN WITH test WILL BE ADDED TO ANY
       SUBMISSION TARBALLS.
endef
export MAKEFILE_HELP

help:
	@echo "$$MAKEFILE_HELP"

#######################
# TODO (begin) #
#######################
# individual dependencies for objects
# Examples:
# "Add a header file dependency"
# project2.o: project2.cpp project2.h
#
# "Add multiple headers and a separate class"
# HEADERS = some.h special.h header.h files.h
# myclass.o: myclass.cpp myclass.h $(HEADERS)
# project5.o: project5.cpp myclass.o $(HEADERS)
#
# ADD YOUR OWN DEPENDENCIES HERE

# tests

HEADERS = http.h parser.h readops.h email.h fixer.h

parser.o: parser.cpp parser.h $(HEADERS)
http.o: http.cpp http.h $(HEADERS)
readops.o: readops.cpp readops.h $(HEADERS)
email.o: email.cpp email.h $(HEADERS)
fixer.o: fixer.cpp fixer.h $(HEADERS)
main.o: main.cpp $(HEADERS)

######################
# TODO (end) #
######################

# these targets do not create any files
.PHONY: all release debug profile clean alltests partialsubmit fullsubmit help
# disable built-in rules
.SUFFIXES:
