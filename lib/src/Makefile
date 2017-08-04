ifeq ($(OS),Windows_NT)
override CXX = clang
CFLAGS += -DWIN32
OUTDIR = ..\..\bin
MKDIRCMD = mkdir $(OUTDIR)
else
OUTDIR = ../../bin
MKDIRCMD = mkdir -p $(OUTDIR)
endif

TARGETEXT = exe
TARGET = libext.$(TARGETEXT)
CFLAGS += -Wall -Werror -std=c++14 -g -framework OpenGL
INCLUDES = $(CURDIR)/../include

SOURCES = \
	handle.cpp \
	graphics/graphics_device.cpp \
	graphics/gl/graphics_device.cpp \
	test.cpp

CFLAGS += -I $(INCLUDES)

all: $(TARGET)

$(OUTDIR):
	$(MKDIRCMD)

$(TARGET): $(SOURCES)
	$(CXX) $(CFLAGS) $? $(LDFLAGS) -o $(OUTDIR)\$@
