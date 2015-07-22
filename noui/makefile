CPP = g++
CPPFLAGS = -std=c++11 -lm -Wall
LFLAGS = -Wall

BINDIR = ./bin
SRCDIR = .
BUILDDIR = ./build

OBJS_NAMES = main.o
OBJS = $(addprefix $(BUILDDIR)/, $(OBJS_NAMES))

all: CPPFLAGS += -O3
all: noui

debug: CPPFLAGS += -g
debug: noui

prof: CPPFLAGS += -pg -O3
prof: LFLAGS += -pg
prof: noui

noui : $(OBJS)
	@mkdir -p $(BINDIR)
	$(CPP) $(OBJS) $(LFLAGS) -o $(BINDIR)/noui

./$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CPP) $(CPPFLAGS) -c $< -o $@
	
clean:
	@echo "Cleaning..."
	rm -f $(BUILDDIR)/*.o $(BINDIR)/noui
