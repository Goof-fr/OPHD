# Source http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

SRCDIR := src/
BUILDDIR := .build/
OBJDIR := $(BUILDDIR)obj/
EXE := OPHD
NAS2DDIR := nas2d-core/
NAS2DINCLUDEDIR := $(NAS2DDIR)include/
NAS2DLIBDIR := $(NAS2DDIR)lib/
NAS2DLIB := $(NAS2DLIBDIR)libnas2d.a

CXXFLAGS := -std=c++17 -g -Wall -Wno-unknown-pragmas -I$(NAS2DINCLUDEDIR) $(shell sdl2-config --cflags)
LDFLAGS := -L$(NAS2DLIBDIR) $(shell sdl2-config --libs)
LDLIBS := -lnas2d -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lphysfs -lGL -lGLEW

DEPFLAGS = -MT $@ -MMD -MP -MF $(OBJDIR)$*.Td

COMPILE.cpp = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = @mv -f $(OBJDIR)$*.Td $(OBJDIR)$*.d && touch $@

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
OBJS := $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRCS))
FOLDERS := $(sort $(dir $(SRCS)))

.PHONY: all
all: $(EXE)

$(EXE): $(NAS2DLIB) $(OBJS)
	@mkdir -p ${@D}
	$(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(NAS2DLIB): nas2d

.PHONY: nas2d
nas2d:
	$(MAKE) -C nas2d-core

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.cpp $(OBJDIR)%.d | build-folder
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

.PHONY: build-folder
build-folder:
	@mkdir -p $(patsubst $(SRCDIR)%,$(OBJDIR)%, $(FOLDERS))

$(OBJDIR)%.d: ;
.PRECIOUS: $(OBJDIR)%.d

include $(wildcard $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.d,$(SRCS)))

.PHONY: clean clean-all
clean:
	-rm -fr $(OBJDIR)
clean-all:
	-rm -rf $(BUILDDIR)
	-rm -f $(EXE)
