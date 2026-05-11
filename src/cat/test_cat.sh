#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

# Создаем тестовые файлы
echo "Hello World" > my.txt
echo -n "No newline here" > no_newline.txt
echo -e "Line 1\n\nLine 3\n\n\nLine 6" > original.txt
echo -e "\tTabbed line\nLine with \033 control char\nEnd" > test.txt
echo -e "Hello\r\nWorld\r\n" > windows.txt

# Массивы флагов и файлов
declare -a flags=(
    "-b" "-e" "-n" "-s" "-t" "-v" "-E" "-T"
    "--number-nonblank" "--number" "--squeeze-blank"
    "-bn" "-bs" "-bt" "-be" "-bv" "-nb" "-ns" "-nt" "-ne" "-nv"
    "-sb" "-sn" "-st" "-se" "-sv" "-tb" "-tn" "-ts" "-te" "-tv"
    "-eb" "-en" "-es" "-et" "-ev" "-vb" "-vn" "-vs" "-vt" "-ve"
    "-bns" "-bnt" "-bne" "-bnv" "-bsn" "-bst" "-bse" "-bsv"
    "-nst" "-nse" "-nsv" "-stn" "-ste" "-stv" "-ent" "-ets"
    "-bnst" "-bnse" "-bnsv" "-nste" "-nstv" "-stne" "-stnv"
    "-bnste" "-bnstv" "-stneb" "-nsteb"
    "-bnstev" "-vetsnb"
)

declare -a files=(
    "my.txt" "no_newline.txt" "original.txt" "test.txt" "windows.txt"
)

echo "Сборка s21_cat..."
make s21_cat

echo "Начинаем тестирование..."

for file in "${files[@]}"; do
    for flag in "${flags[@]}"; do
        ./s21_cat $flag $file > s21_cat_res.txt
        cat $flag $file > sys_cat_res.txt

        DIFF_RES="$(diff -s s21_cat_res.txt sys_cat_res.txt)"
        (( COUNTER++ ))

        if [ "$DIFF_RES" == "Files s21_cat_res.txt and sys_cat_res.txt are identical" ]; then
            (( SUCCESS++ ))
            echo "SUCCESS: s21_cat $flag $file"
        else
            (( FAIL++ ))
            echo "FAIL: s21_cat $flag $file"
            # Раскомментируй строку ниже, если хочешь видеть, в чем именно разница при ошибке
            diff s21_cat_res.txt sys_cat_res.txt
        fi
        rm -f s21_cat_res.txt sys_cat_res.txt
    done
done

echo "======================================"
echo "УСПЕШНО: $SUCCESS"
echo "УПАЛО: $FAIL"
echo "ВСЕГО: $COUNTER"
echo "======================================"

# Убираем за собой тестовые файлы
rm -f my.txt no_newline.txt original.txt test.txt windows.txt