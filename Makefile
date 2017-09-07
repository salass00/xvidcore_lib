TARGET  := xvidcore.library
VERSION := 53

XVIDCOREDIR := xvidcore-1.3.4

CC     := ppc-amigaos-gcc
STRIP  := ppc-amigaos-strip
AR     := ppc-amigaos-ar
RANLIB := ppc-amigaos-ranlib

BUILDSYS := $(shell uname -s)

# Only use host argument if cross-compiling
ifneq ($(BUILDSYS),AmigaOS)
	HOSTARG := --host=ppc-amigaos
else
	HOSTARG := 
endif

CFLAGS  := -O2 -g -Wall -Wwrite-strings -Werror -I./include -I./$(XVIDCOREDIR)/src
LDFLAGS := -static
LIBS    := xvidcore-build/libxvidcore.a

main_SRCS := main/Obtain.c main/Release.c main/xvid_get_plugin_func.c \
             main/xvid_global.c main/xvid_decore.c main/xvid_encore.c
main_OBJS := $(main_OBJS:.c=.o)

SRCS := init.c
OBJS := $(main_SRCS:.c=.o) $(SRCS:.c=.o)

.PHONY: all
all: $(TARGET)

init.o: $(TARGET)_rev.h xvidcore_vectors.c xvidcore_vectors.h
$(main_OBJS): xvidcore_vectors.h

$(XVIDCOREDIR)/build/generic/platform.inc: $(XVIDCOREDIR)/build/generic/configure
	cd $(XVIDCOREDIR)/build/generic && ./configure --prefix=/SDK/local/newlib $(HOSTARG) --disable-pthread

xvidcore-build/libxvidcore.a: $(XVIDCOREDIR)/build/generic/platform.inc
	mkdir -p xvidcore-build
	rm -rf xvidcore-build/*
	$(MAKE) -C $(XVIDCOREDIR)/build/generic BUILD_DIR=../../../xvidcore-build

.PHONY: build-xvidcore
build-xvidcore: xvidcore-build/libxvidcore.a

$(TARGET): build-xvidcore $(OBJS)
	$(CC) $(LDFLAGS) -nostartfiles -o $@.debug $(OBJS) $(LIBS)
	$(STRIP) -R.comment -o $@ $@.debug

.PHONY: clean
clean:
	$(MAKE) -C $(XVIDCOREDIR)/build/generic BUILD_DIR=../../../xvidcore-build distclean
	rm -f $(TARGET) $(TARGET).debug $(OBJS)

.PHONY: revision
revision:
	bumprev $(VERSION) $(TARGET)

