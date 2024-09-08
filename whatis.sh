#!/bin/bash
nb_of_phi=$1
tm_to_die=$2
tm_to_eat=$3
tm_to_sle=$4
nb_of_mls=$5

make 

if [[ -n ${nb_of_mls} ]]
then
{
    ./philo $1 $2 $3 $4 $5 > file | echo "EOF" >> file
    awk '/is died/ {found = 1} found && !EOF {print}' file > out_file
    # cat out_file | awk '{print $2 " " $4}' > out_file2
    cat out_file
}
else
{
        ./philo $1 $2 $3 $4 
        # > file | echo "EOF" >> file
        # awk '/is died/ {found = 1} found && !EOF {print}' file > out_file
        # cat out_file | awk '{print $2 " " $4}' > out_file2
        # cat out_file2
}
fi

# /*
# 	creat a new function printf to delay the time of execution of 
# 	your philo because it is printed all at the same time

# */


# make -C ./analyse
# ./analyse/outfd

# cat out_file2

#     awk '{
#             if ($1 % 2 == 1) 
#             {
#                 if ($2 != "died")
#                 {
#                     died_odd++
#                 }
#                 if ( $2 == "sleeping" ) 
#                 {
#                     sleep_odd++
#                 }
#                 else if ( $2 == "eating" )
#                 {
#                     eating_odd++;
#                 }
#                 else if ( $2 == "thinking" ) 
#                 {
#                     think_odd++ ;
#                 }
#                 else if ($2 == "taken")
#                 {
#                     if (oone_fork == 1)
#                     {
#                         otwo_fork++;
#                         oone_fork = 0;
#                     }
#                     else
#                         oone_fork++;
#                     taken_odd++ ;
#                 }
#             } 
#             else 
#             {
#                 if ($2 != "died")
#                 {
#                     died_even++
#                 }
#                 if ($2 == "sleeping")
#                 {
#                     slp_even++; 
#                 }
#                 else if ($2 == "eating")
#                 {
#                     et_even++;
#                 }
#                 else if ($2 == "thinking")
#                 {
#                     th_even++;
#                 }
#                 else if ($2 == "taken")
#                     taken_even++;
#             }
#         } END {
#                 printf "the philo who is died is "
#                 if (died_even == 1)
#                 {
#                     printf "is EVEN\n\n\n"
#                 }
#                 else
#                 {
#                     printf "is ODD\n\n\n"
#                 }
#                 printf "----ODD----\n"
#                 printf "taken fork  is %d\n", taken_odd
#                 printf "eating      is %d\n", eating_odd
#                 printf "sleeping    is %d\n", sleep_odd
#                 printf "thinking    is %d\n", think_odd
#                 printf "two fork == %d\n", otwo_fork
#                 printf "----EVEN----\n"
#                 printf "taken fork is %d\n", taken_even
#                 printf "eating     is %d\n", et_even
#                 printf "sleeping   is %d\n", slp_even
#                 printf "thinking   is %d\n", th_even
#             }' out_file2


#     awk '{ 
#             if ($1 % 2 == 1)
#             {
#                 odd++;
#             }
#             else
#             {
#                 even++;
#             }
#         } END {
#             printf "your odd value %d\n", odd
#             printf "your even value %d\n", even
#             }' out_file2


# awk '/is e/' out_file

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