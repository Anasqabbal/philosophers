#!/bin/bash
tm_to_die=$1
tm_to_eat=$2
tm_to_sle=$3
nb_of_mls=$4

# make re

if [[ -n ${nb_of_mls} ]]
then
    ./philo $1 $2 $3 $4 > file | echo "EOF" >> file
else
    ./philo $1 $2 $3 > file | echo "EOF" >> file
fi

awk '/is died/ {found = 1} found && !EOF {print}' file > out_file

cat out_file

# read -p "enter the time to die: " tm_to_die
# read -p "time to eat: " tm_to_eat
# read -p "time to sleep: " tm_to_slp
# read -p "number of meals: " nb_of_mls
 #also you can use the read with the opts -p to ask the user for something before entering its value
 #
 #

# echo "SLICING IN BASH"

# my_array=("val" "value2" "value3" "value4")
# echo ${my_array[0]:0:2}