# suffixes
.SUFFIXES : .c .o

## predefined macros.
# c compiler
CC = gcc

# files
SRC_PATH = ./src
OBJ_PATH = ./obj

# all of c files in ./src/
SRCS = $(wildcard $(SRC_PATH)/*.c)
OBJS = $(addprefix $(OBJ_PATH)/, $(notdir $(SRCS:.c=.o)))

TARGET = main

## make procedures
# generate exacute file

$(TARGET) : $(OBJ_PATH) $(OBJS)
	@echo "# make : generate execute file : OBJS - $(OBJS)"
	$(CC) -o $@ $(OBJS)

# generate object file
$(OBJS) : $(SRCS)
	@echo "# make : generate obj file : SRCS - $(SRCS)"
	$(CC) -c $(addprefix $(SRC_PATH)/, $(notdir $(@:.o=.c))) -o $@

# make directory
$(OBJ_PATH) : $(SRCS)
	@echo "# make : make obj directory : OBJ_PATH - $(OBJ_PATH)"
	mkdir -p $@

# clean
clean :
	@echo "# make : cleanup"
	rm -rf $(OBJ_PATH) $(TARGET) core
