pi estimate for:
  10 = 3.44
  100 = 3.1796
  1000 = 3.14552
  10000 = 3.14199

bigO estimate = O(n^2)

run time for:
  10 =
      real	0m0.004s
      user	0m0.001s
      sys	  0m0.002s

  100 =
      real	0m0.004s
      user	0m0.001s
      sys	  0m0.002s

  1000 =
      real	0m0.011s
      user	0m0.007s
      sys	  0m0.002s

  10000 =
      real	0m0.299s
      user	0m0.295s
      sys	  0m0.002s

The time recorded for the program was roughly reflected the bigO estimate.
The real time and the user time exponentially increased from 100 to 1000 and 1000
to 10000. As the size of the input increased, the time to compute the answer
also increased.

with constexpr:
  pi estimate for:
    10 = 3.44
    100 = 3.1796
    1000 = 3.14552

  run time for:
    10 =
      real	0m0.005s
      user	0m0.002s
      sys	  0m0.002s

    100 =
      real	0m0.004s
      user	0m0.001s
      sys	  0m0.002s

    1000 =
      real	0m0.010s
      user	0m0.006s
      sys	0m0.002s

Observations on constexpr: The system time for the program remained the same;
however, the overall time for the program to run decreased. The program returned
the same estimates for pi but the time taken to estimate pi decreased. 
