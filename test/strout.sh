mv strout.c.test strout.c
gcc -Wall -Wextra -Werror strout.c ../get_next_line.c ../libft/libft.a -o get_next_line

cat testfiles/16char_out | ./get_next_line
cat testfiles/16char_12line | ./get_next_line
cat testfiles/16char_2line | ./get_next_line
cat testfiles/16char_1line | ./get_next_line
cat testfiles/8char_out | ./get_next_line
cat testfiles/8char_6line | ./get_next_line
cat testfiles/8char_2line | ./get_next_line
cat testfiles/8char_1line | ./get_next_line
cat testfiles/4char_out | ./get_next_line
cat testfiles/4char_5line | ./get_next_line
cat testfiles/4char_2line | ./get_next_line
cat testfiles/4char_1line | ./get_next_line
cat testfiles/random_test | ./get_next_line
cat testfiles/two_newlines | ./get_next_line
cat testfiles/one_newline| ./get_next_line
cat testfiles/empty | ./get_next_line

rm get_next_line
mv strout.c strout.c.test
