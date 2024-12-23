NAME_PREFIX := aocSolver_
BIN_DIR := ./bin
FLAGS := -Wall -Wextra -Werror -Wshadow -std=c++17
COMPILER := c++
VALGRIND := valgrind --leak-check=full

BRIGHT_YELLOW := \033[0;93m
YELLOW := \033[0;33m
COLOR_RESET := \033[0m

DAY ?= 01
SRC_DIR := ./srcs/day$(DAY)
SRC := $(SRC_DIR)/Day$(DAY).cpp $(SRC_DIR)/main.cpp
NAME := $(BIN_DIR)/$(NAME_PREFIX)$(DAY)

all:
	@echo "Usage: make run DAY=<day_number> to compile and run, make leaks DAY=<day_number> to check leaks"

help:
	@echo "Usage:"
	@echo "  make run DAY=<day_number>    Compile and run the program (e.g., make run DAY=01)"
	@echo "  make leaks DAY=<day_number>  Check memory leaks using valgrind (e.g., make leaks DAY=01)"
	@echo "  make clean                  Remove binaries"

run: $(NAME)
	@./$(NAME)

leaks: $(NAME)
	@$(VALGRIND) ./$(NAME)

$(NAME): $(SRC)
	@mkdir -p $(BIN_DIR)
	@$(COMPILER) $(FLAGS) $(SRC) -o $(NAME)
	@echo "$(BRIGHT_YELLOW)Built $(NAME)$(COLOR_RESET)"

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(YELLOW)Removed binaries$(COLOR_RESET)"
