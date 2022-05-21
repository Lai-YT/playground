# Matrix Multiplication

Matrix multiplication can be calculated independently with respect to *rows* or *block*, so by multi-threading, we may have the calculation complete in shorter time. In this practice, 3 approaches of calculation are implemented:

1. 3-level nested loop (single thread)
2. one threads for every single *row* (multi-thread)
3. one threads for every single *block* (multi-thread)

## Matrix

Matrix *A* has it's elements defined by *a<sub>ij</sub> = 6.6i - 3.3j*; \
matrix *B* has it's elements defined by *b<sub>ij</sub> = 100 + 2.2i - 5.5j*; \
The result matrix *C = A x B*.

## Result

The 1<sup>st</sup> time table is when *A<sub>50x80</sub>* and *B<sub>80x50</sub>*, which results in *C<sub>50x50</sub>*.

|Approach |Time (ms) |
|---------|----------|
|1        |10.97     |
|2        |15.96     |
|3        |11.48     |

The 2<sup>nd</sup> time table is when *A<sub>50x8000</sub>* and *B<sub>8000x50</sub>*, which also results in *C<sub>50x50</sub>*.

|Approach |Time (ms) |
|---------|----------|
|1        |141.72    |
|2        |48.38     |
|3        |55.83     |

## Conclusion

we can see that when the matrix is small, multi-threadings are slower due the overhead of thread creation; when the matrix is sufficiently large, multi-threadings beat the brutal looping approach. \
Approach 2 and 3 serves different *shape*s of matrix and the `BLOCK_SIZE` of approach 3 can also be critical (approach 2 has better memory locality).
