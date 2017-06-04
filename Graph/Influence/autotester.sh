NODE_COUNT=1000
TEST_COUNT=5
TIME_CONSTRAINT=5

SCALE=10
make
# Generate the password files
rm -f "test/data.dat"
echo >> test/data.dat "lf \$Run_time\$"
for i in {2..10}
do
    for j in `seq 2 $TEST_COUNT`
    do
        seed=$i*$j*$j
        echo "Testing $i"
        filename="test/load_factor_${i}.test"
        rm -f $filename
        build/influence -g $filename $NODE_COUNT $i $seed
        build/influence $filename $TIME_CONSTRAINT
        total_time=$(($?*$SCALE))
        echo >> test/data.dat "$i $total_time"
    done
done
#build/influence test/wiki_example.txt 100
#build/influence test/facebook_small.txt 100
#build/influence test/facebook_large.txt 100
#build/influence test/gnutella.txt 100