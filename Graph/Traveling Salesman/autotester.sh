DENSITY=10
make

rm -f "test/data.dat"
echo >> test/data.dat "size \$Run_time\$"

# Building the test files
for i in {2..24}
do
    seed=$i
    filename="test/graph_${i}.test"
    rm -f $filename
    build/tsp -g $filename $i $DENSITY $seed
done

for i in {2..24}
do
    echo "Running TSP with $i notes"
    filename="test/graph_${i}.test"
    echo -n >> test/data.dat "${i} "
    build/tsp $filename
done


#build/influence test/wiki_example.txt 100
#build/influence test/facebook_small.txt 100
#build/influence test/facebook_large.txt 100
#build/influence test/gnutella.txt 100
