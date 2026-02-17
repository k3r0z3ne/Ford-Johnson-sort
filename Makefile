NAME = solver
CC = c++
CFLAGS = -Wall -Wextra -Werror -Wshadow -std=c++98 -MMD -MP

SRC =	main.cpp PmergeMe.cpp
OBJ_DIR = build
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.cpp=.o))
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re