YELLOW	= \033[0;33m
NC		= \033[0m # No Color

TARGET = libmemphis.a

SRCDIR = src
INCDIR = src/include

CC = riscv64-elf-gcc
AR = riscv64-elf-gcc-ar
OBJDUMP = riscv64-elf-objdump
OBJCOPY = riscv64-elf-objcopy

CFLAGS	= -march=rv32im -mabi=ilp32 -Os -std=c17 -fdata-sections -ffunction-sections -flto -Wall -I$(INCDIR)

SRCC = $(wildcard $(SRCDIR)/*.c)
SRCS = $(wildcard $(SRCDIR)/*.S)
OBJ = $(patsubst %.c, %.o, $(SRCC)) $(patsubst %.S, %.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(AR) rcs $@ $^libmutils.a

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@printf "${YELLOW}Compiling lib: %s ...${NC}\n" "$<"
	@$(CC) -c $< -o $@ $(CFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.S
	@printf "${YELLOW}Compiling lib: %s ...${NC}\n" "$<"
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm -f $(SRCDIR)/*.o
	@rm -f *.a

.PHONY: clean
