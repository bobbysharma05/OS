include ../config.mk

LIBC_A = ../libc/lib/libc.a
LIBC_LIBS = $(wildcard ../libc/lib/*)
LIBC_INCS = $(wildcard ../libc/obj/include/**/*) $(wildcard ../libc/include/**/*)
LIBC_DEPS = $(LIBC_A) $(LIBC_LIBS) $(LIBC_INCS)

OBJ = ../obj/usr
BIN = $(OBJ)/bin
SRC = src

USER_DIRS := $(shell find $(SRC) -maxdepth 1 -mindepth 1 -type d)
USER_BINS := $(USER_DIRS:$(SRC)/%=$(BIN)/%)

# Compiler flags
CFLAGS = -std=gnu99 -O3 -MMD -MP -static -z max-page-size=4096 \
  -fno-omit-frame-pointer \
  -I. \
  -I.. \
  -I../.. \
  -I../libc/include/ \
  -I../inc \
  -I../libc/obj/include/ \
  -I../libc/arch/aarch64/ \
  -I../libc/arch/generic/

LDFLAGS = -L../libc/lib/ -nostartfiles ../libc/lib/crt1.o ../libc/lib/crti.o -lc ../libc/lib/crtn.o

USR_CC := $(CC)

# Object files for syscall.c and usys.S
SYSCALL_OBJS = $(OBJ)/syscall.o $(OBJ)/usys.o

all:
	$(MAKE) -C ../libc
	mkdir -p $(BIN)
	$(MAKE) $(USER_BINS)

$(OBJ)/%.c.o: %.c $(LIBC_DEPS)
	mkdir -p $(dir $@)
	$(USR_CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/syscall.o: syscall.c
	mkdir -p $(OBJ)
	$(USR_CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/usys.o: usys.S
	mkdir -p $(OBJ)
	$(USR_CC) $(CFLAGS) -c -o $@ $<

# Build user binaries
.SECONDEXPANSION:
$(BIN)/%: $$(addsuffix .o, $$(addprefix $(OBJ)/, $$(shell find $(SRC)/% -name "*.c"))) $(SYSCALL_OBJS)
	mkdir -p $(dir $@)
	$(USR_CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBC_A)
	$(OBJDUMP) -S -d $@ > $(OBJ)/src/$(notdir $@)/$(notdir $@).asm
	$(OBJDUMP) -x $@ > $(OBJ)/src/$(notdir $@)/$(notdir $@).hdr
	$(STRIP) --strip-debug $@

clean:
	rm -rf $(OBJ) $(BIN)

.PHONY: all clean

UPROGS = \
    _init \
    _sh \
    _ps \
    # Add other programs here