CC = g++
CFLAGS = -Wall
LDFLAGS =
LIBS =
INCLUDE = -I./Inc
BUILDDIR = Build
BINDIR = $(BUILDDIR)/bin
OBJDIR = $(BUILDDIR)/obj
TARGET = $(BINDIR)/simulator.out
SOURCEDIR = Src
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SOURCEDIR)/%.cpp
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@[ -d $(OBJDIR) ]
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: $(TARGET)

clean:
	-rm -f $(wildcard $(BINDIR)/*) $(wildcard $(OBJDIR)/*)