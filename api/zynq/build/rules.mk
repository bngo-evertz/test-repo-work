# Copyright 2008 Evertz Microsystems Ltd.  All rights reserved.
# Rules for making an executable program
# author: grivers (modified from bliu)
# requires:
#    PROG = name of exectable
#    VER_PATH = path to version number file
#    OBJS = object file names
#    NON_CLEAN_OBJS = object files not to be clean
#    LIB  = library name
#    STATIC_LIB = static library name

#Cross-compiler
ifeq ($(shell expr $(VIVADO_VER) \>= 2016.1), 1)
  GNUCC    ?=  arm-linux-gnueabihf-gcc
  GNUCPP   ?=  arm-linux-gnueabihf-g++
  GNUAR    ?=  arm-linux-gnueabihf-ar
  GNURAN   ?=  arm-linux-gnueabihf-ranlib
  GNUSTRIP ?=  arm-linux-gnueabihf-strip
else
  GNUCC    ?=  arm-xilinx-linux-gnueabi-gcc
  GNUCPP   ?=  arm-xilinx-linux-gnueabi-g++
  GNUAR    ?=  arm-xilinx-linux-gnueabi-ar
  GNURAN   ?=  arm-xilinx-linux-gnueabi-ranlib
  GNUSTRIP ?=  arm-xilinx-linux-gnueabi-strip
endif
PPFLAGS := $(CFLAGS)
CFLAGS +=  -c

# Needed to activate the gdb debugger (only activate when available)
ifeq ($(MAKECMDGOALS), debug)
CFLAGS += -g
CFLAGS += -ggdb
GNUSTRIP := @echo debug version, not strip
else
#CFLAGS += -DNDEBUG
CFLAGS += -O3
endif

# Optimization Level #CFLAGS += -O0

# Option to put transaction hndlr into testing
# mode. Queue sizes and timeouts are adjusted.
# CFLAGS += -D TESTING

# Option to enable runtime debugging options.
# NOTE: If this is turned on the router cannot be run
# as a background process.
# CFLAGS += -D DEVELOPMENT

define MAKEDEPEND
cp $*.d $*.P; \
sed -e 's/#.*//; s/^[^:]*: *//; s/ *\\$$//; /^$$/ d; s/$$/ :/' \
	    < $*.d >> $*.P; \
rm -f $*.d
endef

%.o : %.cpp
	$(GNUCPP) $(CFLAGS) -MD $(CPPFLAGS) -o $@ $<
	@$(MAKEDEPEND)
%.o : %.c
	$(GNUCC) $(CFLAGS) -MD $(CPPFLAGS) -o $@ $<
	@$(MAKEDEPEND)
%.o : %.cc
	$(GNUCPP) $(CFLAGS) -MD $(CPPFLAGS) -o $@ $<
	@$(MAKEDEPEND)

%.c : %.y
	bison -y -o $@ $<


ifdef PROG
#OBJS += ver.o

.PHONY: mainentry
mainentry: $(PROG)

.PHONY: buildver
buildver:
	@echo generating version files
	@perl $(MKRULES_DIR)/version.pl --product $(PROG_NAME) --path $(VER_PATH)
	$(GNUCC) $(CFLAGS) $(CPPFLAGS) -o ver.o ver.c
#	rm -f ./main.o
	@sleep 1

CFLAGS += -W -Wall -Werror
$(PROG): $(OBJS) $(NON_CLEAN_OBJS) $(LIBS)
	$(GNUCPP) -g -W -Wall -Werror -o $(PROG) $(OBJS) $(LIBS) $(NON_CLEAN_OBJS) $(LDFLAGS) $(LDADD)
	$(GNUSTRIP) $@

install:
	install $(PROG)  $(PROG_TARGET)

all: $(PROG) install
debug: $(PROG)

else
ifdef LIB
CFLAGS += -fPIC
LDFLAGS += -shared
$(LIB): $(OBJS)  $(NON_CLEAN_OBJS)
	$(GNUCPP) $(LDFLAGS) -o lib$(LIB) $(OBJS) $(NON_CLEAN_OBJS)
#	$(GNUSTRIP) lib$@
#	$(GNUAR) rc $(LIB) $(OBJS) $(OBJs)
#	$(GNURAN) $@
#	cp $@ ../.
install:
	install lib$(LIB) $(TARGET_FOLDER)

all: $(LIB) install
debug: $(LIB)
else
ifdef STATIC_LIB
RANLIBFLAGS=
$(STATIC_LIB): $(OBJS)
	$(GNUAR) rc lib$(STATIC_LIB) $(OBJS) $(OBJs)
	$(GNURAN) lib$(STATIC_LIB)
	#$(GNUSTRIP) lib$@

install:
	install lib$(STATIC_LIB) $(TARGET_FOLDER)

all: $(STATIC_LIB) install
debug: $(STATIC_LIB)

endif
endif
endif


clean:
	rm -rf $(PROG) $(OBJS) lib$(LIB) lib$(STATIC_LIB)
	rm -f $(OBJS:.o=.P)

-include $(OBJS:.o=.P)

