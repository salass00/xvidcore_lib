TARGET  := xvidcore.library
VERSION := 53

XVIDCOREDIR := xvidcore-1.3.4

CC     := ppc-amigaos-gcc
STRIP  := ppc-amigaos-strip
AR     := ppc-amigaos-ar
RANLIB := ppc-amigaos-ranlib

CFLAGS  := -O2 -g -Wall -Wwrite-strings -Werror -I./include -I./$(XVIDCOREDIR)/src
LDFLAGS := -static
LIBS    := 

main_SRCS := main/Obtain.c main/Release.c main/xvid_get_plugin_func.c \
             main/xvid_global.c main/xvid_decore.c main/xvid_encore.c
main_OBJS := $(main_OBJS:.c=.o)

SRCS := init.c
OBJS := $(main_SRCS:.c=.o) $(SRCS:.c=.o)

.PHONY: all
all: $(TARGET)

init.o: $(TARGET)_rev.h xvidcore_vectors.c xvidcore_vectors.h
$(main_OBJS): xvidcore_vectors.h

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -nostartfiles -o $@.debug $^ $(LIBS)
	$(STRIP) -R.comment -o $@ $@.debug

.PHONY: clean
clean:
	$(RM) $(TARGET) $(TARGET).debug $(OBJS)

.PHONY: revision
revision:
	bumprev $(VERSION) $(TARGET)

