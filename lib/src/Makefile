TARGETEXT = exe
TARGET = libext.$(TARGETEXT)
CFLAGS = 
INCLUDES = ../include
OUTDIR = ../../bin/

CFLAGS += -I $(INCLUDES)

all: $(TARGET)

$(TARGET): test.cpp
	mkdir -p $(OUTDIR)
	$(CXX) $(CFLAGS) $? $(LDFLAGS) -o $(OUTDIR)$@
