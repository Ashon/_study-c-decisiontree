# suffixes
.SUFFIXES : .c .o

## predefined macros.
# c compiler
CC = gcc

# files
SRC = main.c
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))
TARGET = main

## make procedures
# generate exacute file
$(TARGET) : $(OBJ)
	@echo "# make : generate execute file"
	$(CC) -o $@ $(OBJ)

# generate object file
$(OBJ) : $(OBJ_PATH) $(SRC)
	@echo "# make : generate obj file"
	$(CC) -c $(SRC) -o $(OBJ)

# make directory
$(OBJ_PATH) : $(SRC)
	@echo "# make : make obj directory"
	mkdir -p $@

# clean
clean :
	@echo "# make : cleanup"
	rm -rf $(OBJ_PATH) $(TARGET) core
