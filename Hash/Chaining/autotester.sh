make
mkdir -p test
rm test/output.log
rm test/data.dat
echo >> test/data.dat "lf \$Test1\$ \$Test2\$ \$Test3$ \$Test4\$ \$Test5\$ \$Average\$"
count=1000
./checkpass -g test/passwords1.txt $count 1
./checkpass -g test/passwords2.txt $count 2
./checkpass -g test/passwords3.txt $count 3
./checkpass -g test/passwords4.txt $count 4
./checkpass -g test/passwords5.txt $count 5
for i in {1..15}
do
	size=$((i * 1000))
	echo >> test/output.log Testing "$size"
	echo Testing "$size"
	test1=$(./checkpass -t $size test/passwords1.txt)
	test2=$(./checkpass -t $size test/passwords2.txt)
	test3=$(./checkpass -t $size test/passwords3.txt)
	test4=$(./checkpass -t $size test/passwords4.txt)
	test5=$(./checkpass -t $size test/passwords5.txt)

	echo >> test/output.log "Collision Count: $test1" 
	echo >> test/output.log "Collision Count: $test2" 
	echo >> test/output.log "Collision Count: $test3" 
	echo >> test/output.log "Collision Count: $test4" 
	echo >> test/output.log "Collision Count: $test5"

	load_factor=$(bc <<< "scale=3;$count / $size")

	test_sum=$((test1 + test2 + test3 + test4 + test5))
	average=$((test_sum / 5))
	echo >> test/data.dat "$load_factor $test1 $test2 $test3 $test4 $test5 $average"
	
done