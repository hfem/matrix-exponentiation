## Finding Fibonacci Terms in O(log(N)) Using Matrix Exponentiation

***The*** Fibonacci sequence is 0, 1, 1, 2, 3,..., n but a popular problem to solve is how to find an arbitrary Fibonacci sequence's N<sup>th</sup> term. An arbitrary Fibonacci sequence is defined with some **F<sub>0</sub>**, some **F<sub>1</sub>**, and the formula:  
**F<sub>*k* >= 2</sub> = F<sub>k - 1</sub> + F<sub>k - 2</sub>**.  
The recursive solution even with memoization of the terms is O(N). Using matrices, matrix exponentiation, and binary exponentiation we can solve for that N<sup>th</sup> term in O(log(N)).

[excellent explanation of the math](https://youtu.be/EEb6JP3NXBI)

**Example:**  
Solve for the 19<sup>th</sup> term  
**N** = **19**  
~ *binary* : **`10011`** == <code>2<sup>4</sup> + 2<sup>1</sup> + 2<sup>0</sup></code> == 16 + 2 + 1 
<pre><code>where:
 | 1 1 | = <b>B</b>   
 | 1 0 |  
  <break>
 | F<sub>1</sub> | = <b>F<sup>[1|0]</sup></b>
 | F<sub>0</sub> |
 <break>
 | F<sub>20</sub> | = <b>F<sup>[20|19]</sup></b>
 | F<sub>19</sub> |
 <break>
 <break>
 <strong>Formula:</strong>
 <b>B<sup>19</sup></b> x <b>F<sup>[1|0]</sup></b> = <b>F<sup>[20|19]</sup></b>
 <break>
 Binary Exponentiation to Calculate <b>B<sup>19</sup></b>
 <b>B<sup>1</sup></b> x <b>B<sup>2</sup></b> x <b>B<sup>16</sup></b> x <b>F<sup>[1|0]</sup></b> = <b>F<sup>[20|19]</sup></b>
</code></pre>
The naive method of calculating <b>B<sup>16</sup></b> is to multiply <b>B</b> sixteen times, but we know that <b>B<sup>16</sup></b> = <b>(B<sup>8</sup>)<sup>2</sup></b> = <b>((B<sup>4</sup>)<sup>2</sup>)<sup>2</sup></b> = <b>((((B<sup>2</sup>)<sup>2</sup>)<sup>2</sup>)<sup>2</sup>)</b> which we can use to optimize the number of multiplications, each time just squaring the previous value.

## Implementation
- Matrix Class Template  
  - keeps track of rows and columns and matrix data values in an array 
  - implements matrix*matrix multiplication and operator<<
  - allows for any data type (currently: type alias BigNum for an unsigned 64-bit integer) 
- Fibonacci Class
  - keeps track of matrices calculated for the binary exponentiation of N and the first and second term of that sequence
  - implements algorithm for using matrices to find N<sup>th</sup> term
  - limited by current data type used, next item: find a large integer C++ library

*Why?* I just thought this was a really interesting use of matrices to speed up an algorithm that I had thought was already optimized.
