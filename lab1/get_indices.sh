if [[ -z "$1" ]]; then
    START=1
else
    START=$1
fi
if [[ -z "$2" ]]; then
    END=$START
else
    END=$2
fi
make CalculateIndex >/dev/null 2>/dev/null
TEXT=$(cat)
for i in $(seq $START $END); do
    for j in $(seq 1 $i); do
        echo $TEXT | ./filter.pl | ./divide_vigenere.py $i $j | ./CalculateIndex
        echo -n " ";
    done;
    echo ""
done;
