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
- **Matrix** class template :  *Matrix.h* && *Matrix.cpp*
  - split into two files for readability
  - keeps track of number of rows and columns and keeps matrix data values in an array 
  - currently implements Matrix * Matrix multiplication and operator << (necessary for the Fibonacci problem)
  - templating the class allows for any data type (currently: type alias BigNum = unsigned 64-bit integer) 
- **Fibonacci** class : *Fibonacci.h* && *Fibonacci.cpp*
  - keeps track of matrices previously calculated for the binary exponentiation of N and the first and second term of the current sequence
  - updateExpMatrices () - updates the list of the calculated matrices if the last matrix in the list **!=** the initial matrix raised to 2<sup>k</sup>, where k is the highest bit set in the binary representation of **N**
  - setStartValues () - saves the initial values of the current Fibonacci sequence to be calculated
  - findNthTerm () - implements formula for using the exponentiation matrices to find N<sup>th</sup> term (as described above)
  - limited by current data type used :: find a large integer C++ library

*Why?* I just thought this was a really interesting use of matrices to speed up an algorithm that I had thought was already optimized.