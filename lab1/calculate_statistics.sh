if [[ -z "$2" ]]; then
    OFFSET=1
else
    OFFSET=$2
fi
if [[ -z "$1" ]]; then
    END=30
else
    END=$1
fi
TEXT=$(cat)
for i in $(seq $OFFSET $END); do
    for j in $(seq 1 $i); do
        echo $TEXT | ./divide_vigenere.py $i $j | ./CalculateIndex
        echo -n " ";
    done;
    echo ""
done;
