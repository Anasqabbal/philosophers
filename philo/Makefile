NAME=philo
CC=cc
UTILS= ph_atoi.c ph_utils2.c ph_errors.c ph_utils1.c\
		ph_lstutils1.c ph_lstutils2.c  ph_utils3.c prepare_philosophers.c

FILES= philo.c $(UTILS)
OFILES=$(FILES:.c=.o)
INCLUDES= philo.h
CFLAGS= -Wall -Wextra -Werror
all : $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $@

.%o : .%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OFILES)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean
