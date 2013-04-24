##############################################################################
# Application specific info.  Specify the object target basename, object
# files to be created, and any precompiled libraries here.
##############################################################################
TARGET = VexCode

OBJS = ifi_startup.o \
       ifi_utilities.o \
       printf_lib.o \
       main.o \
       user_routines.o \
       user_routines_fast.o \
       ws_general.o \
       ws_io.o \
       ws_drive.o \
       ws_appendage.o \
       ws_autonomous.o \
#PicSerialDrv.o \

LIBS = Vex_2008_library.lib

##############################################################################
# Compiler settings.  Specify compiler/linker flags here, as well as default
# directories for system headers/libraries.
##############################################################################
ifndef MCC18PATH
MCC18PATH = /home/WS/mcc18
endif
# Compile for pre-2006 controller
# Must also:
# - replace FRC_Library.lib with FRC_Library_8520.lib
# - replace FRC_alltimers.lib with FRC_alltimers_8520.lib
#CFLAGS = -p=18F8520 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa- -nw=2066
#LINKER = 18f8520.lkr

CFLAGS = -p=18F8520 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa- -nw=2066
LINKER = 18f8520user.lkr

COPTS = -D_VEX_BOARD
LDFLAGS = -m$(TARGET).map -o$(TARGET).cof
LIBDIRS = -L`cygpath -w $(MCC18PATH)/lib`
INCLUDEDIRS = -I`cygpath -w $(MCC18PATH)/include`
PATH += :$(MCC18PATH)/bin

##############################################################################
# Executable defines & rules - shouldn't need to change anything below here.
##############################################################################
CC  = mcc18
LD  = mplink
RM  = rm
PCC = cpp18

.SUFFIXES: .o .c .i

all: $(TARGET).hex

$(TARGET).hex: $(OBJS) $(LIBS)
	$(LD) $(LINKER) $(OBJS) $(LIBS) $(LDFLAGS) $(LIBDIRS)

.c.o:
	$(CC) $*.c -fo $@ $(INCLUDEDIRS) $(COPTS) $(CFLAGS)

.c.i:
	$(PCC) $*.c $(INCLUDEDIRS) > $@

clean:
	@echo "Cleaning build directory..."
	-@$(RM) *.o *.hex *.cof *.cod *.lst *.map *.err
