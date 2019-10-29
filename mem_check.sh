valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt  ./test/bin/randomized_stress_test
