SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
BINDIR = ./bin
EXTDIR = ./ext
EXE = $(BINDIR)/FlashPhoto
CXXFLAGS += -I. -fopenmp -std=c++11
EXTFLAG = -isystem./ext/glui/include -isystem./ext/jpeg-9a -isystem./ext/libpng-1.6.16 -isystem./ext
LINKLIBS = -lglut -lGL -lGLU -lglui -lpng -ljpeg -lz
LIBDIR = -L./ext/glui/lib
GLUILIB = -L./ext/glui/lib

SRC_CXX = $(wildcard $(SRCDIR)/*.cc)
OBJ_CXX = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC_CXX))

# On some computers, make produces ext/lib. On others ext/lib64
ifneq ($(wildcard $(EXTDIR)/lib64/),)
	LIBDIR += -L./ext/lib64
else
	LIBDIR += -L./ext/lib
endif

.PHONY: all glui

all: $(EXE)

$(EXE): $(OBJ_CXX) glui jpeg-9a png-1.6.16 | $(BINDIR)
	g++ -g -o $@ $(OBJ_CXX) $(LIBDIR) $(LINKLIBS) $(CXXFLAGS)

$(OBJDIR)/main.o: $(SRCDIR)/main.cc | $(OBJDIR)
	g++ -g $(CXXFLAGS) $(EXTFLAG) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(INCDIR)/%.h | $(OBJDIR)
	g++ -g $(CXXFLAGS) $(EXTFLAG) -c -o $@ $<

jpeg-9a:
	$(MAKE) -C./ext/jpeg-9a all install

png-1.6.16:
	$(MAKE) -C./ext/libpng-1.6.16 all install	

glui:
	$(MAKE) -Cext/glui all

$(BINDIR) $(OBJDIR):
	mkdir -p $@

clean:
	rm -rf obj bin
