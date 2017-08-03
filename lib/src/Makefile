TARGETEXT = exe
TARGET = libext.$(TARGETEXT)
CXXFLAGS = -Wall -Werror -std=c++11 -g -framework OpenGL
INCLUDES = $(CURDIR)/../include
OUTDIR = ../../bin/

SOURCES = \
	handle.cpp \
	graphics/graphics_device.cpp \
	graphics/gl/graphics_device.cpp \
	test.cpp

CXXFLAGS += -I $(INCLUDES)

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p $(OUTDIR)
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $(OUTDIR)$@
