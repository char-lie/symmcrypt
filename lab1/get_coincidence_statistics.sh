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

TEXT=$(cat)
for i in $(seq $START $END); do
    echo $TEXT | ./calculate_coincidence_statistics.py $i
done;
