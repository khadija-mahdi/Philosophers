NAME= philo_bonus

SRC= main.c\
	parsing.c\
	utils.c\
	init.c\

OBJ= $(SRC:.c=.o)

OBJ_DIR = objects

OBJ= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

CC = cc

CFLAGS = -Wall -Wextra -Werror 

$(RM) = rm
  
all: $(NAME)
	@echo "Done compiling my program :)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) ${CFLAGS} -c $< -o $@

$(NAME): $(OBJ) 
	@$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)
	@echo "COMPILING MY PROGRAM ...\n"

clean:
	@ echo "REMOVING OBJECTS FILES ...\n"
	@$(RM) $(OBJ)
	@$(RM) -rf $(OBJ_DIR)
	@ echo "Done removing objects files :)"

fclean: clean
	@ echo "REMOVING $(NAME) ...\n"
	@$(RM) $(NAME) 
	@$(RM) -rf $(OBJ_DIR)
	@ echo "Done removing $(NAME) :)"
	
re: fclean all
