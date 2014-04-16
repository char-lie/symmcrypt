if [[ -z "$1" ]]; then
    PART_SIZE=1
else
    PART_SIZE=$1
fi
cat | ./decipher_parts.sh $PART_SIZE | ./merge_texts.py $PART_SIZE
