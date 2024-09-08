NAME=outfd
CC=cc
UTILS=analyses.c
FILES= $(UTILS)
OFILES=$(FILES:.c=.o)
INCLUDES= ./libft/libft.h
F= -fsanitize=thread -g
FF= -g -fsanitize=address
CFLAGS= -Wall -Wextra -Werror
LIBFT=./libft/libft.a

all : lib $(NAME)

lib :
	@make -C ./libft

$(NAME) : $(OFILES) $(INCLUDES)
	@$(CC) $(CFLAGS) $(OFILES)  $(LIBFT) -o $@

.%o : .%.c $(INCLUDES)
	@$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OFILES)

fclean : clean
	rm -rf $(NAME)

re : fclean all