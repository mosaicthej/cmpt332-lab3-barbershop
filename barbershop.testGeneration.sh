#!/bin/sh
# generating test cases for Lab3.synchproblem

# run the executable Lab3 with 2 arguments
#    - MaxCustomers, between 10 and 50
#    - numChairs, between 3 and 10
# 20 test cases are generated
# each case is generated randomly

# the output of the executable is redirected file "Lab3.test.results.txt"

for ((i=0;i<20;i++))
do
    MaxCustomers=$(( (RANDOM % 40) + 10))
    numChairs=$(( (RANDOM % 7) + 3))
    echo -e "Test Case $i : MaxCustomers = $MaxCustomers, numChairs = $numChairs" >> Lab3.test.results.txt
    ./barbershop $MaxCustomers $numChairs >> barbershop.test.results.txt
    # append 3 new lines between each test case
    echo -e "\n\n\n" >> barbershop.test.results.txt   
done


