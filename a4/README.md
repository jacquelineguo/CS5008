CS 5008, Spring 2021\
Xuan Guo\
Assignment 4 - Quicksort Experimentation

In this assignment, I've implement 4 sort algorithms:
1. Original Quicksort -- (quicksort.c, quicksort.h)
2. Shuffle array and then sort. -- (algB.c, algB.h)
3. Quicksort with Insertion sort. -- (algD.c, algD.h)
4. Median pivot. -- (algC.c, algC.h)


To compile the files, enter 'make' in terminal.
To run the program, type './sort -ARGV' where ARGV is all or combination of algorithm a, b, c, d. Example: ./sort -ab



***Summary***
The output of all four algorithm is shown below:
```
-bash-4.2$ ./sort -all
             16      64     128     512    1024    2048
-------------------------------------------------------
Alg A:      4     17     38     152     354     768
Alg B:      8     22     46     182     359     793
Alg C:      5     22     50     193     411     880
Alg D:      2     12     30     146     340     699
```
The time is in microseconds.

- We can see that as data size go up, the time required to sort also goes up.

- We can see that the time used in algorithm A. B and C are increasing. I think this is because
-- algorithm B have extra shuffle step which takes more time
-- algorithm C computes median as pivot which requires even more time to compute.
The advantage of algorithm B&C appear in larger size data:
```
            16      64     128     512    1024    20480
-------------------------------------------------------
Alg A:      4     17     37     152     343     16763
Alg B:      2     19     16     167     333     9430
Alg C:      2     19     18     172     349     9637

Alg D:      1     5     12     55     127     7388
```

In case of 20480 integers, original quicksort takes nearly 2X time to sort. Ithink this is because with larger data size, the time cost of running into worst case increases. But with shuffle and using median as pivot, algorithm B&C have better chance of avoiding running into worst case.


For algorithm D, it is the most efficient algorithm among them, because insertion sort has better performance when data size is small.
I tested few cutoffs and find 120 to be optimal.
- cutoffs too small have similar runtime with original quicksort, e,g, cutoff = 10.I think this shows that in small sized partially sorted data, quicksort is slower than insertion sort because it has too much of overhead cost for calling itself repeatedly for small arrays.
- cutoff too big sometimes make the algorthm slowest of all 4. e.g. cutoff = 300. I think this shows that with larger sized and less sorted data, quicksort is faster than insertion sort.

1. Who did you work with?\
Myself.
2. What external resources did you use?\
Google.
3. How much time you spent on this assignment?\
40 hrs.
4. What was the most challenging part of this assignment?\
I think debug and algorthm.\
[Optional] What did you like about this assignment?\
It's so hard, I don't like it.\
[Optional] How could this assignment be improved?\
More clearer structure and starter code.