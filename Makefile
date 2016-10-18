SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
BINDIR = ./bin
EXE = $(BINDIR)/BrushWork
CXXFLAGS += -I. -W -Wall -Wextra -Weffc++ -Wno-unused-variable -std=c++11
GLUIFLAG = -I./ext/glui/include
LINKLIBS = -lglut -lGL -lGLU -lglui
GLUILIB = -L./ext/glui/lib


SRC_CXX = $(wildcard $(SRCDIR)/*.cc)
OBJ_CXX = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC_CXX))

.PHONY: all glui

all: $(EXE)

$(EXE): $(OBJ_CXX) glui | $(BINDIR)
	g++ -o $@ $(OBJ_CXX) $(GLUILIB) $(LINKLIBS)

$(OBJDIR)/main.o: $(SRCDIR)/main.cc | $(OBJDIR)
	g++ $(CXXFLAGS) $(GLUIFLAG) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(INCDIR)/%.h | $(OBJDIR)
	g++ $(CXXFLAGS) $(GLUIFLAG) -c -o $@ $<

glui:
	$(MAKE) -Cext/glui all

$(BINDIR) $(OBJDIR):
	mkdir -p $@

clean:
	rm -rf obj bin

