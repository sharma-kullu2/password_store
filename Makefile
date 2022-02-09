# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

CC = gcc                        # compiler to use

LINKERFLAG = -lm

SRCS :=  main.c src/adt_def.c src/Reactor.c src/tmp_Writefile.c src/adt_file_handle.c src/tmp_Readfile.c
BINS := $(SRCS:%.c=%)
TARGET := Runnable
all:
	@echo "Checking.."
	${CC} ${SRCS} -o ${TARGET}

clean:
	@echo "Cleaning up..."
	rm -rvf ${TARGET} DATAFILE