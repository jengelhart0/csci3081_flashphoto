SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
BINDIR = ./bin
EXE = $(BINDIR)/FlashPhoto
CXXFLAGS += -I. -W -Wall -Wextra -Weffc++ -std=c++11
EXTFLAG = -isystem./ext/glui/include -isystem./ext/jpeg-9a -isystem./ext/libpng-1.6.16
LINKLIBS = -lglut -lGL -lGLU -lglui -lpng -ljpeg -lz
LIBDIR = -L./ext/lib
GLUILIB = -L./ext/glui/lib


SRC_CXX = $(wildcard $(SRCDIR)/*.cc)
OBJ_CXX = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC_CXX))

.PHONY: all glui

all: $(EXE)

$(EXE): $(OBJ_CXX) glui jpeg-9a png-1.6.16 | $(BINDIR)
	g++ -o $@ $(OBJ_CXX) $(LIBDIR) $(LINKLIBS)

$(OBJDIR)/main.o: $(SRCDIR)/main.cc | $(OBJDIR)
	g++ $(CXXFLAGS) $(EXTFLAG) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(INCDIR)/%.h | $(OBJDIR)
	g++ $(CXXFLAGS) $(GLUIFLAG) -c -o $@ $<

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

