# Assignment 10: Multi-threaded Searching

This is some starter and example code for A6. 

* ```mt_search.c``` has some optional starter code you can use to help you get started with A6. 
    - Build and run with ```make run```
    - This runs the command ```./mt_search inputs/input1.txt 5 2 10``` 
    - To run with different parameters, you need to call something like: 
        + ```./mt_search <inputfile> <num_to_find> <num_threads> <num_numbers>```
* ```example.c``` has some code that creates 8 threads and uses a semaphore to synchronize them. 
    - Build and run this with ```make run_example```
* ```inputs``` is a folder that has files of numbers appropriate for A6. 
    - To see how many numbers are in the file: ```wc -l nums10000.txt``` , where "nums10000.txt" is the file you want to see the number of lines for. 
    - To see which lines (which index) a certain number is on, use the command: ```grep -n 805 nums10000.txt``` (where "805" is the number to search for and "nums10000.txt" is the file to search). This reports line number, which should correspond to the indices of the array you read the values into. It gives you the "right" answer :) 
    - To generate your own number file, you can run:

```shuf -i 0-999 -n 100 > nums.txt```

Where in this example, 100 numbers are being generated (between 0 and 999) and output into a file called ```num.txt```
```

CS5008, Spring 2021\
Xuan Guo

1. Who did you work with?\
Myself.
2. What external resources did you use?\
Google.
3. How much time you spent on this assignment?\
40 hrs.
4. [Optional] What did you like about this assignment?
5. [Optional] How could this assignment be improved?