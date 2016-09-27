################################################################################
# Name            : Makefile
# Project         : Project
# Description     : Makefile Template
# Creation Date   : Fri May 16 14:59:49 2014
# Original Author : jharwell
#
# Note: This file is -j (parallel build) safe, provided you don't mess with it
# too much.
#
#  Products:
#  Make Target     Product                  Description
#  ===========     =======                  ===================
#  all             bin/FlashPhoto           The main executable
#  clean           N/A                      Removes excutable, all .o,
#                                           .preproc files
#  veryclean       N/A                      Everything clean removes, +
#                                           the external libraries and the
#                                           results of ALL analyses.
################################################################################

###############################################################################
# Directory Definitions
###############################################################################
# src/      - Root of the source tree for the project
# bin/      - Directory where all executables are built
# obj/      - Directory where all object files are built
# doc/      - Directory where all documentation lives

SRCDIR          = ./src
BINDIR          = ./bin
OBJDIR          = ./obj
EXTDIR          = ./ext
GLUIDIR         = $(EXTDIR)/glui
JPEGDIR         = $(EXTDIR)/jpeg-9a
PNGDIR          = $(EXTDIR)/libpng-1.6.16
DOCDIR          = ./doc

###############################################################################
# Definitions
###############################################################################

# Tell make we want to execute all commands using bash (otherwise it uses sh)
SHELL           = bash

###############################################################################
# C++ Compilation Options
###############################################################################
CXXLIBDIRS ?= -L$(GLUIDIR)/lib -L$(JPEGDIR)/lib -L$(PNGDIR)/lib

# We don't have control over GLUI, so suppress all compiler warnings its
# headers may generate
define CXXINCDIRS
-I. \
-isystem$(GLUIDIR)/include \
-isystem$(JPEGDIR) \
-isystem$(PNGDIR)
endef

CXXFLAGS = $(OPT) -g -W -Wall -Wextra -Weffc++ -std=gnu++11 -Wno-unused-parameter $(CXXINCDIRS)

# In general, note that the order libraries are specified to the linker
# MATTERS. If a library is specified too early on the command line, which can
# happen when:
# 1. It is specified on the command line before the linker processes any
#    source files that contain references to it
# 2. It is specified on the command line with the libraries to link against
#    before another library that contains references to it.
#
# In both these cases the linker will "drop" the library and you will see
# unresolved reference errors.
CXXLIBS     = -ljpeg -lpng -lz -lm -lpthread

# For graphics support, we also need to link with the Glut and OpenGL libraries.
# This is specified differently depending on whether we are on linux or OSX.
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin) # Mac OSX
CXXLIBS += -framework glut -framework opengl -lglui
else # LINUX
CXXLIBS += -lglut -lGL -lGLU -lglui
endif

# On some lab machines the glut and opengl libraries are located in the directory
# where the nvidia graphics driver was installed rather than the default /usr/lib
# directory.  In this case, we need to tell the linker to search this nvidia directory
# for libraries as well.  Uncomment the line below.
#NVIDIA_LIB =  /usr/lib/nvidia-304  #or whichever nvidia driver number shows up in that dir
ifneq ($(NVIDIA_LIB), )
CXXLIBS += -L$(NVIDIA_LIB)
endif

CXX         = g++
OPT         = -O0

###############################################################################
# Functions
###############################################################################
# Recursive wildcard: search a list of directories for all files that match a pattern
# usage: $(call rwildcard, $(DIRS1) $(DIRS2) ..., pattern)
#
# All directory lists passed as first arg must be separated by spaces, and they
# themselves must be space separated as well. There must NOT be a space between
# the last dir list the , and the start of the pattern.
#
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)  $(filter $(subst *,%,$2),$d))

# make-depend: generate dependencies for C++ source files dynamically. Very useful
# for including .h files as target dependencies.
# usage: $(call make-depend,source-file,object-file,depend-file)
#
# Note that this will not work on files in $(TESTDIR) without modification to
# this makefile.
#
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $1

###############################################################################
# Target Definitions
###############################################################################
# Define what directories to search for source code
SOURCES    = $(SRCDIR)

# Define the list of files to compile for this project
SRC_CXX    = $(call rwildcard,$(SOURCES),*.cc)

# For each of the .cc files found above, determine the name of the
# corresponding .o file to create.
OBJECTS_CXX  = $(notdir $(patsubst %.cc,%.o,$(SRC_CXX)))

# The target executable (what you are building)
TARGET = $(BINDIR)/FlashPhoto

###############################################################################
# All targets
###############################################################################

# Phony targets: targets of this type will be run everytime by make (i.e. make
# does not assume that the target recipe will build the target name)
.PHONY: clean veryclean all documentation

# The default target
all: $(TARGET)

# Unless invoked with make clean, include generated dependencies. This makes
# it so that anytime you make an edit in a .h file, all .cc files that
# include it will automatically be recompiled.
ifneq "$MAKECMDGOALS" "clean"
-include $(addprefix $(OBJDIR)/,$(OBJECTS_CXX:.o=.d))
endif

# The Target Executable
$(addprefix $(OBJDIR)/, $(OBJECTS_CXX)): | $(OBJDIR)
$(TARGET): $(GLUIDIR)/lib/libglui.a $(JPEGDIR)/lib/libjpeg.a $(PNGDIR)/lib/libpng.a $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) $(addprefix $(OBJDIR)/, $(OBJECTS_CXX)) -o $@ $(CXXLIBS)

# GLUI, JPEG, and PNG libraries
$(GLUIDIR)/lib/libglui.a:
	@$(MAKE) -C$(GLUIDIR)
$(JPEGDIR)/lib/libjpeg.a:
	@$(MAKE) -C$(JPEGDIR)
$(PNGDIR)/lib/libpng.a:
	@$(MAKE) -C$(PNGDIR)

# Bootstrap Bill. This creates all of the order-only prerequisites; that is,
# files/directories that have to be present in order for a given target build
# to succeed, but that make knows do not need to be remade each time their
# modification time is updated and they are newer than the target being built.
$(BINDIR)  $(OBJDIR):
	@mkdir -p $@

# The Cleaner
clean:
	@rm -rf $(BINDIR) $(OBJDIR)

# The Super Cleaner
veryclean: clean
	@$(MAKE) -C$(GLUIDIR) clean
	@$(MAKE) -C$(JPEGDIR) uninstall distclean
	@$(MAKE) -C$(PNGDIR) uninstall distclean

# The Documenter
documentation:
	cd $(DOCDIR) && doxygen Doxyfile
	cd ..

###############################################################################
# Pattern Rules
###############################################################################
# For compiling the C++ source. Specify that any .o file in the object
# directory can be build
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) $(CXXLIBDIRS) -c -o  $@ $<
