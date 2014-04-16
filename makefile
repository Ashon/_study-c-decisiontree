# suffixes
.SUFFIXES : .c.o

## predefined macros.
# c compiler
CC = gcc

# file path
SRC_PATH = ./src/
OBJ_PATH = ./obj/

# all of c files in ./src/
SRCS = $(wildcard $(SRC_PATH)*.c)
OBJS = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRCS))

TARGET = main

## make procedures
# generate exacute file
all : $(OBJ_PATH) $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

# generate object file
$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	$(CC) -c $(addprefix $(SRC_PATH), $(notdir $(@:.o=.c))) -o $@

# make directory
$(OBJ_PATH) :
	mkdir -p $@

# clean
clean :
	rm -rf $(OBJ_PATH) $(TARGET) core
