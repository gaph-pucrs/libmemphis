YELLOW	= \033[0;33m
NC		= \033[0m # No Color

TARGET = libmemphis.a

SRCDIR = src
INCDIR = src/include
HEADERS = $(wildcard $(INCDIR)/*.h) $(wildcard $(INCDIR)/**/*.h)

CC = riscv64-elf-gcc
AR = riscv64-elf-gcc-ar
OBJDUMP = riscv64-elf-objdump
OBJCOPY = riscv64-elf-objcopy

CFLAGS	= -march=rv32imac -mabi=ilp32 -Os -std=c23 -fdata-sections -ffunction-sections -flto -Wall -I$(INCDIR)

SRCC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst %.c, %.o, $(SRCC))

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(AR) rcs $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@printf "${YELLOW}Compiling lib: %s ...${NC}\n" "$<"
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm -f $(SRCDIR)/*.o
	@rm -f *.a

.PHONY: clean
