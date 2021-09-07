# ############ diff with test.txt ############# #
tac text.txt | cat -e > test_tac
./revert text.txt | cat -e > test_revert
diff test_tac test_revert
rm test_tac test_revert
# ############################################# #

# ###### diff with random char generator ###### #
# python3 random_chars_generator.py > py.txt
# tac py.txt | cat -e > test_tac
# ./revert py.txt | cat -e > test_revert
# diff test_tac test_revert
# rm test_tac test_revert py.txt
# ############################################# #