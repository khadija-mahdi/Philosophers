NAME = philo

SRC= main.c\
	philosophers.c\
	utils.c\
	init.c\
	libft_utils.c\
	action.c\


OBJ_DIR = objects

OBJ= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

CC = cc

CFLAGS = -Wall -Wextra -Werror 

$(RM) = rm
  
all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) ${CFLAGS} -c $< -o $@

$(NAME): $(OBJ)  
	$(CC) $(CFLAGS) $(OBJ) -g  -fsanitize=thread -o  $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) 
	$(RM) -rf $(OBJ_DIR)
	
re: fclean all