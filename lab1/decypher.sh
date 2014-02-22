for i in {0..11};
do
    cat cyrillic/example/input.txt | ./divide_vigenere.py 12 $i | ./SortCharacters;
    echo "";
done;
