The functions with chromosome.cc we had to implement were: is_valid(),
calculate_fitness(), constructor/destructor, mutate(), recombine(). As for
the deme.cc we had to implement: the constructor, get_best(), select_parent(),
compute_next_generation(). We were able to implement these functions, the
largest issues we had in our code:
1. We were not passing our threshold enough, so the parents were not changing
so the children were not changing which lead to getting a large and not
optimal solution that at times was not even better than the randomized solution.
Solution: We were not designing the threshold in a way that would ever allow us
to pass it. So we ended up changing the implementation so that we took the
median total which allowed us to get much better results. select_parent() was
not working how we thought it was; we were able to fix it by changing the
threshold value.
2. We were having memory issue. Solution: we found the issue was that we were forgetting to delete 
elements within the population vector. We had to delete things in the destructor
as well as in compute_next_generation().
3. Our solutions were not random. Solution: we realized that we were not seeding
the random generator_ each time so it was not random. So we added srand() before
using the generator_ so that we were getting random numbers. We might have
added srand() too many times but this way were positive that it works how we want it
to work and the numbers are random.
Another issue that we had was the we were forgetting to subract 1 from pop_.size()
so we were always out of range when using stl uniform_int_distribution or
uniform_real_distribution.

Aside from these issues which we were able to solve, we ran it under valgrind and
were satisfied with our solutions.

Nicole Niesen
Alex Richter
