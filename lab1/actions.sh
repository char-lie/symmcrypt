cat cyrillic/example/input.txt | ./prepare_statistics.sh | ./analyse_statistics.py
cat cyrillic/example/input.txt | ./decipher_vigenere.sh 12
cat cyrillic/example/input.txt | ./decipher_vigenere.sh 12 | ./correct_vigenere.py б к 12 3 --key
