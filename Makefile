# Define compiler
CC = cc

BREW = $(shell which brew | rev | cut -c 9- | rev)
BREW_VERSION = $(shell ls $(BREW)/Cellar/glfw/)
GLFW = $(BREW)Cellar/glfw/$(BREW_VERSION)
LIBS = -L$(GLFW)/lib -lglfw -L./lib/MLX42 -lmlx42 -L./lib/libft -lft ./lib/gnl/get_next_line.c ./lib/gnl/get_next_line_utils.c

# Define source directories
SRCDIR = src
TEST_SRCDIR = test/src
UNITY_SRCDIR = test/Unity/src

# Define object directories
OBJDIR = obj
TEST_OBJDIR = test/obj
UNITY_OBJDIR = test/Unity/obj

# Define include directories
INCLUDES = -I./src/include
GLFW_INCLUDES = -I$(GLFW)/include/GLFW
MLX42_INCLUDES = -I./lib/MLX42/include
TEST_INCLUDES = -I./$(UNITY_SRCDIR) $(INCLUDES) $(GLFW_INCLUDES) $(MLX42_INCLUDES)

# Define compiler flags
CFLAGS = -g -fsanitize=address
TEST_CFLAGS = -g -fsanitize=address

# Define main source file
MAIN = main.c

# Define source files
MAIN_SRC = $(SRCDIR)/$(MAIN)
SRC := $(filter-out $(MAIN_SRC), $(shell find $(SRCDIR) -name '*.c'))
TEST_SRC = $(TEST_SRCDIR)/test_my_module.c
UNITY_SRC = $(UNITY_SRCDIR)/unity.c

# Define object files
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAIN_OBJ = obj/main.o
TEST_OBJ = $(TEST_OBJDIR)/test_my_module.o
UNITY_OBJ = $(UNITY_OBJDIR)/unity.o

# Define executables
EXE = a.out
TEST_EXE = test.out

# Define default target
all: libft $(EXE) $(TEST_EXE)
# Comment out the line above and uncomment the line below to compile without tests
# all: $(EXE)

# Define build target for production executable
$(EXE): $(OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MAIN_OBJ) $(LIBS) -o $(EXE)

# Define build target for test executable
$(TEST_EXE): $(OBJ) $(TEST_OBJ) $(UNITY_OBJ)
	$(CC) $(TEST_CFLAGS) $(OBJ) $(TEST_OBJ) $(UNITY_OBJ) $(LIBS) -o $(TEST_EXE)

# Define build target for production object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/parser
	$(CC) $(CFLAGS) $(INCLUDES) $(GLFW_INCLUDES) $(MLX42_INCLUDES) -c $< -o $@

# Define build target for test object files
$(TEST_OBJDIR)/%.o: $(TEST_SRCDIR)/%.c
	mkdir -p $(TEST_OBJDIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

$(UNITY_OBJDIR)/%.o: $(UNITY_SRCDIR)/%.c
	mkdir -p $(UNITY_OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Define target to run tests
test: all
	./$(TEST_EXE)

run: all
	./$(EXE)

# Define target to clean up build files
clean:
	rm -rf obj $(TEST_OBJDIR)
	make -C lib/libft clean

fclean : clean
	rm -f $(EXE) $(TEST_EXE)
	make -C lib/libft fclean

re : fclean all

debug: CFLAGS += -g -fsanitize=address
debug: TEST_CFLAGS += -g -fsanitize=address
debug: re

libft:
	make -C lib/libft

.PHONY: all test clean fclean re
