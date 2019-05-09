Traveling Salesperson Problem - part 4
by Nicole Niesen and Alex Richter

The parameters that we used for both trials below were 
	-num_inter = 2,000,000
	-pop_size  = 1000
	-mut_rate  = .2

First, we ran the code as follows for nthread = 1:

>> time ./tsp challenge.tsv 1000 .2 1

This found the best distance of 6120.34 in 12.855s.

We then ran the code in parallel (nthread = 4) with the following command:

>> time ./tsp challenge.tsv 1000 .2 4

This produced a best distance of 5916.71 in 5.845s which is more than twice as fast as our baseline results. 
We did not beat Eitan's best distance :(