NAME=philo
CC=cc
UTILS= ph_atoi.c ph_putstr_fd.c ph_errors.c ph_lstadd_back_bonus.c ph_lstadd_front_bonus.c ph_lstclear_bonus.c\
		ph_lstdelone_bonus.c ph_lstlast_bonus.c ph_lstnew_bonus.c ph_lstsize_bonus.c ft_get_timeofday.c philo_utils1.c
FILES= $(UTILS) philo.c
OFILES=$(FILES:.c=.o)
INCLUDES=philo.h
F= -fsanitize=address
CFLAGS= -Wall -Wextra -Werror $F -pthread

all : $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $@

.%o : .%.c $(INCLUDES)
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(OFILES)

fclean : clean
	rm -rf $(NAME)

re : fclean all

