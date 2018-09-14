#This should eventually be merged into the 'src Makefile'
#   once I figure out how

# The main driver of the project
EXECUTABLE 	= Test

# designate which compiler to use
CXX			= g++

# list of sources used in project
SOURCES 	= $(wildcard *.cpp)
SOURCES += http.cpp
SOURCES += readops.cpp
SOURCES += parser.cpp
SOURCES += fixer.cpp

# list of objects used in project
OBJECTS	= $(SOURCES:%.cpp=$(ODIR)/%.o)

# If main() is in another file delete the line above, edit and uncomment below
PROJECTFILE = test_main.cpp

#Default Flags
#CXXFLAGS = -std=c++14 -Wall -Werror -Wextra -pedantic
CXXFLAGS = -std=c++14 -I$(IDIR)
LDFLAGS = -L/usr/local/lib
LDLIBS = -lcurl -ltidy

#Define directories for cleaner directory
IDIR = ../include
ODIR = obj
SDIR = ../src

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

# rule for creating objects

$(ODIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $*.cpp

$(ODIR)/http.o: $(SDIR)/http.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SDIR)/http.cpp

$(ODIR)/parser.o: $(SDIR)/parser.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SDIR)/parser.cpp

$(ODIR)/readops.o: $(SDIR)/readops.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SDIR)/readops.cpp

$(ODIR)/fixer.o: $(SDIR)/fixer.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SDIR)/fixer.cpp

# make clean - remove .o files, executables, tarball
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TESTS) $(PARTIAL_SUBMITFILE) $(FULL_SUBMITFILE)


# these targets do not create any files
.PHONY: all release debug profile clean alltests partialsubmit fullsubmit help
# disable built-in rules
.SUFFIXES:
