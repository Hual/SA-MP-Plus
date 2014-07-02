CC = g++ -m32

# Release
#CFLAGS = -c -O3 --std=c++11 -I../Shared/include -Wno-write-strings
#LDFLAGS = -fshort-wchar -O2 -shared -lpthread

#Debug
CFLAGS = -c -g --std=c++11 -I../Shared/include -Wno-write-strings
LDFLAGS = -fshort-wchar -g -shared -lpthread

LDLIBS = -L../Shared/lib -lsampgdk -lsubhook

PROJDIRS = ./
OBJDIR = obj/

SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cpp")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")
OBJFILES := $(patsubst %.cpp, %.o, $(SRCFILES))
DEPFILES := $(patsubst %.cpp, %.d, $(SRCFILES))

BINARY = bin/sampp.so

all: $(BINARY)

$(BINARY): $(OBJFILES)
	@$(CC) $(LDFLAGS) $(OBJFILES) $(LDLIBS) -o $(BINARY)

%.o: %.cpp Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

.PHONY: clean
clean:
	@rm -rf $(DEPFILES) $(OBJFILES) $(BINARY) 
