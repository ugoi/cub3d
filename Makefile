# Define compiler
CC = cc

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
TEST_INCLUDES = -I./$(UNITY_SRCDIR) $(INCLUDES)

# Define compiler flags
CFLAGS = -Wall -Wextra -Werror
TEST_CFLAGS = 

# Define main source file
MAIN = main.c

# Define source files
MAIN_SRC = $(SRCDIR)/$(MAIN)
SRC := $(filter-out $(MAIN_SRC), $(shell find $(SRCDIR) -name '*.c'))
TEST_SRC = $(TEST_SRCDIR)/test_my_module.c
UNITY_SRC = $(UNITY_SRCDIR)/unity.c

# Define object files
OBJ = obj/my_module.o
MAIN_OBJ = obj/main.o
TEST_OBJ = $(TEST_OBJDIR)/test_my_module.o
UNITY_OBJ = $(UNITY_OBJDIR)/unity.o

# Define executables
EXE = my_module
TEST_EXE = my_module_tests

# Define default target
all: $(EXE) $(TEST_EXE)
# Comment out the line above and uncomment the line below to compile without tests
# all: $(EXE)

# Define build target for production executable
$(EXE): $(OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MAIN_OBJ) -o $(EXE)

# Define build target for test executable
$(TEST_EXE): $(OBJ) $(TEST_OBJ) $(UNITY_OBJ)
	$(CC) $(CFLAGS) $(TEST_CFLAGS) $(TEST_INCLUDES) $(OBJ) $(TEST_OBJ) $(UNITY_OBJ) -o $(TEST_EXE)

# Define build target for production object files
$(OBJ): $(SRC)
	mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC) -o $(OBJ)

# Define build target for main object files
$(MAIN_OBJ): $(MAIN_SRC)
	mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $(MAIN_SRC) -o $(MAIN_OBJ)

# Define build target for test object files
$(TEST_OBJ): $(TEST_SRC) $(UNITY_SRC)
	mkdir -p $(TEST_OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_CFLAGS) $(TEST_INCLUDES) -c $(TEST_SRC) -o $(TEST_OBJ)

$(UNITY_OBJ): $(UNITY_SRC)
	mkdir -p $(UNITY_OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_CFLAGS) $(TEST_INCLUDES) -c $(UNITY_SRC) -o $(UNITY_OBJDIR)/unity.o

# Define target to run tests
test: all
	./$(TEST_EXE)

# Define target to clean up build files
clean:
	rm -rf obj $(TEST_OBJDIR)

fclean : clean
	rm -f $(EXE) $(TEST_EXE)

re : fclean all

.PHONY: all test clean fclean re
