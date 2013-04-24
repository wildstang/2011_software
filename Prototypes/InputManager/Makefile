##############################################################################
# Application specific info.  Specify the object target basename, object
# files to be created, and any precompiled libraries here.
##############################################################################
TARGET = inputManagerTest.exe

OBJS = inputManagerTest.o \
       InputManager.o \
       Gamepad.o \


FILES = inputManagerTest.cpp \
        InputManager.cpp \
        Gamepad.cpp \

LIBS =

##############################################################################
# Compiler settings.  Specify compiler/linker flags here, as well as default
# directories for system headers/libraries.
##############################################################################
CFLAGS= -g -Wall -ansi -O2
COPTS =
LIBDIRS =
INCLUDEDIRS =

##############################################################################
# Executable defines & rules - shouldn't need to change anything below here.
##############################################################################
CC  = g++
LD  = ld
RM  = rm

.SUFFIXES: .o .cpp .i

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(CC) -enable-auto-import -o $(TARGET) $(OBJS) $(LIBS) $(LIBDIRS)

.cpp.o:
	$(CC) $(INCLUDEDIRS) $(COPTS) $(CFLAGS) -c ${FILES}

clean:
	@echo Cleaning build directory...
	-@$(RM) *.o $(TARGET)
	@echo Done!



CC = g++

CFLAGS = -Wall -O2

COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))



all: inputManagerTest



inputManagerTest: $(OBJFILES)

	$(CC) -o inputManagerTest $(OBJFILES)



%.o: %.cpp

	$(COMPILE) -o $@ $<

all: inputManagerTest
