NAME=philo
CC=cc
UTILS= ph_atoi.c ph_utils2.c ph_errors.c ph_utils1.c\
		ph_lstutils1.c ph_lstutils2.c prepare_philosophers.c

FILES= philo.c $(UTILS)
OFILES=$(FILES:.c=.o)
INCLUDES= philo.h
F= -fsanitize=thread -g
FF= -g -fsanitize=address
CFLAGS= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OFILES) $(INCLUDES)
	$(CC) $(CFLAGS) $(OFILES) -o $@

.%o : .%.c $(INCLUDES)
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OFILES)

fclean : clean
	rm -rf $(NAME)

re : fclean all

