# Performance analysis of different compilers in combination with BLAST library

The analysis aims to observe the differences in the execution times of the programs depending on the level of optimization used and the compiler. All programs perform an implementation to solve the equation C = (zerotr (ATB * BTA))^2 where A and B are two quadratic matrices. 

To compare the runtime, three different programs were created:
* solver_neopt.c - the simplest version to implement, without any optimization applied to the code
* solver_opt.c - the optimized version, using conventional optimization methods
* solver_blas.c - optimized version, using a specialized library

## Implementation

### Unoptimized variant
The non-optimized variant that implements the given equation in the most inefficient way. First perform the multiplication for ATBsi BTA. Then gather them and put 0 under the main diagonal. The last step he performs is to squaring the previous result. The complexity of the program is O (N3), but there are 3 multiplications of matrices with complexity O (N3) and two runs of matrices having an complexity of O (N2).
If we notice that we can do less multiplication and scrolling, this would be a first step in optimizing the code.

### Optimized version
This variant takes into account several aspects to achieve a much faster execution of the program. First of all, it is noticed that ATB is transposed to BTA, which would help us to reduce the number of trips and multiples. Thus, we can do the multiplication once to obtain the ATB and simultaneously keep and transpose the result to have calculated the result of BTA.

Also, we can add the two results when we compute them, to avoid a subsequent iteration through the result matrices. Another optimization we can do is use block matrix multiplication to optimize the cache usage mode. We divided the calculation of the multiplication of the two matrices into two, one for the blocks on or above the main diagonal and one for the blocks on or below the main diagonal. Another optimization used is that of indexing by pointers to the referred values and keeping the addresses in registers for faster access.
Last but not least, I reversed the order of the matrices and I arrived by to the classic i - j - k through the i - k - j to browse the data
in a constant or sequential order and not having big jumps in memory.

During the implementation of the optimized version, we tried several methods to obtain the optimal time. I tried the translation and the second matrix to get simpler steps in the matrix. I tried to keep the order i - j - k of the matrices, but using a battery to calculate a single cell from the resulting matrix, but these tests were slower. I also tried to keep the data calculated in global variables, but it did not bring any gain in terms of time. I also tried calculating in a single scan of the matrices, but following the experiments, going through two separate stages (first in the upper half and then in the lower half of the matrices) proved more efficient.
 
### Blas variant
For this variant I used the cblas_dgemm function in the Blas library to multiply matrices. We called the function to calculate ATBsi BTA, and then we gathered the results to obtain a triangular upper matrix which we then raised to the square to obtain the desired result. Adding the two partial results obtained from the calculation of ATBsi BTA we have it effective only for j> = i where j is the index of the line in the result matrix, and i is the index of the column.

### Optimized version with compilation flags

#### The gcc compiler
This is the variant of the non-optimized program that has been compiled with different compilation flags. For this program I tried several levels of optimization: O2, O3 and Ofast.

In the case of the latter, Ofast, it allows optimizations for floating point numbers, and these are perceived as being infinitely accurate and respecting normal algebra. For this flag we obtained the fastest results, but the optimizations made by it can lead to non-compliance
compilation standards. The results produced were mathematically correct. The running time for the last test was 49.6192 seconds.

For the O3 flag we obtained results on average 4 seconds slower than the Ofast flag. For the last test, the program ran 51.8954 in the most favorable case.

For the O2 flag we got slower results, for the last test reaching 54.0415 seconds.

#### The ICC compiler
For compiling with icc I tried the same flags as for the gcc compiler. The results were much better with the mention that in this case the order of flag efficiency was not maintained, and the O2 flag was much faster than the other two reaching a running time of 9.5099 while for O3 or Ofast were obtained times of 32-33 seconds.

Comparative analysis between the implementation methods for the GCC compiler

| N                 | 400    | 1000    | 1600     |
|-------------------|--------|---------|----------|
| Not optimized     | 2.2144 | 34.1755 | 166.0908 |
| Optimized with O3 | 1.4364 | 16.1637 | 55.299   |
| Optimized         | 0.36   | 5.3728  | 22.321   |
| BLAS              | 0.0488 | 0.7279  | 2.9441   |

It can be seen that the best results were obtained for the implementation that used a function from the BLAS library, as it is a specialized library for working with matrices. Also, the code optimizations were more efficient than the compiler optimizations, demonstrating the importance of how the code is structured. The compiler is limited in terms of how it can reorder the code. At a compilation of the optimized program, which used the O3 flag, a time of 7.79 seconds was obtained for the last test, so the compiler must come to complete the optimized code and will not be able to replace it.

Comparative analysis between the implementation methods for the ICC compiler

| N                 | 400    | 1000    | 1600     |
|-------------------|--------|---------|----------|
| Not optimized     | 2.287  | 30.4756 | 166.0104 |
| Optimized with O3 | 0.8187 | 5.3112  | 33.2954  |
| Optimized         | 0.611  | 8.311   | 33.1234  |
| BLAS              | 0.0554 | 0.8206  | 3.1457   |

And this time the best results were obtained with BLAS, but overall the duration of the programs was longer than in the case of the gcc compiler. The optimizations for the icc compiler are much more efficient than those of the gcc.

#### ICC vs GCC comparison

In the case of the performance of the two compilers, a significant improvement of the execution times can be observed within the programs optimized by compilation flags. The ICC compiler uses SIMD instructions compared to the GCC and performs several operations per clock cycle. GCC needs multiple clock cycles for a single operation.
However, the other three implementation variants (the non-optimized one, the manual optimized one and the one in which the BLAS library was used) are more efficient in the version compiled with GCC.

