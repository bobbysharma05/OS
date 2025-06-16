include ../config.mk

LIBC_A = ../libc/lib/libc.a
LIBC_DEPS = $(LIBC_A)

OBJ = ../obj/usr
BIN = $(OBJ)/bin

# Build ps, init, and sh
UPROGS = ps init sh

USER_BINS := $(UPROGS:%=$(BIN)/%)

CFLAGS = -std=gnu99 -Os -MMD -MP -static -z max-page-size=4096 \
  -fno-omit-frame-pointer \
  -I. \
  -I.. \
  -I../inc \
  -I../libc/include/ \
  -I../libc/obj/include/ \
  -I../libc/arch/aarch64/ \
  -I../libc/arch/generic/

LDFLAGS = -L../libc/lib/ -nostartfiles ../libc/lib/crt1.o ../libc/lib/crti.o -lc ../libc/lib/crtn.o

USR_CC := $(CC)

all:
	$(MAKE) -C ../libc
	mkdir -p $(BIN)
	$(MAKE) $(USER_BINS)

# Common object files
$(OBJ)/syscall.o: syscall.c
	mkdir -p $(OBJ)
	$(USR_CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/usys.o: usys.S
	mkdir -p $(OBJ)
	$(USR_CC) $(CFLAGS) -c -o $@ $<

# Rule for ps program
$(BIN)/ps: src/ps/ps.c $(OBJ)/syscall.o $(OBJ)/usys.o $(LIBC_DEPS)
	mkdir -p $(dir $@)
	$(USR_CC) $(CFLAGS) $(LDFLAGS) -o $@ src/ps/ps.c $(OBJ)/syscall.o $(OBJ)/usys.o $(LIBC_A)

# Rule for init program  
$(BIN)/init: src/init/main.c $(OBJ)/syscall.o $(OBJ)/usys.o $(LIBC_DEPS)
	mkdir -p $(dir $@)
	$(USR_CC) $(CFLAGS) $(LDFLAGS) -o $@ src/init/main.c $(OBJ)/syscall.o $(OBJ)/usys.o $(LIBC_A)

# Rule for sh program
$(BIN)/sh: src/sh/main.c $(OBJ)/syscall.o $(OBJ)/usys.o $(LIBC_DEPS)
	mkdir -p $(dir $@)
	$(USR_CC) $(CFLAGS) $(LDFLAGS) -o $@ src/sh/main.c $(OBJ)/syscall.o $(OBJ)/usys.o $(LIBC_A)

clean:
	rm -rf $(OBJ) $(BIN)

.PHONY: all clean
