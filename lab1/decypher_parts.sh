if [[ -z "$1" ]]; then
    END=0
    LENGTH=1
else
    END=`expr $1 - 1`
    LENGTH=$1
fi
make DecryptCaesar >/dev/null 2>/dev/null
TEXT=$(cat)
for i in $(seq 0 $END);
do
    echo $TEXT | ./divide_vigenere.py $LENGTH $i | ./DecryptCaesar;
    echo ""
done;
