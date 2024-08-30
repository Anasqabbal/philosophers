NAME=philo
CC=cc
UTILS= ph_atoi.c ph_putstr_fd.c ph_errors.c ft_get_timeofday.c ph_utils1.c\
		ph_utils2.c ph_lstutils1.c ph_lstutils2.c prepare_philosophers.c
FILES= $(UTILS) philo.c
OFILES=$(FILES:.c=.o)
INCLUDES= philo.h
F= -fsanitize=thread -g
FF= -g -fsanitize=address 
CFLAGS= -Wall -Wextra -Werror -pthread

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

