# Humorous Sorting Algorithms
**A few sorting algorithms intended to perform poorly**.

Below is a table outlining the details of each algorithm

|  Algorithm | Worst Complexity  | Average Complexity | Best Complexity   | Space Complexity  | Stable  |
| ------------ | ------------ | ------------ | ------------ | ------------ | ------------ |
| **Bogosort**  | Unbounded  |  *Ω((n+1)!)* | *Θ(n)*  |  *O(1)* | No  |
| **Slowsort**  | *O(n<sup> log n</sup>)*  | *Ω(n<sup> log n</sup>)*  | *Θ(n<sup> log n</sup>)*  |  *O(n)* | No  |
| **Stooge Sort**  |  *O(n<sup>2.709</sup>)* |  *Ω(n<sup>2.709</sup>)* | *Θ(n<sup>2.709</sup>)*  | *O(n)*  | No |

## Bogosort
Bogosort is a deliberately ineffective algorithm which works by generating a random permutation of the array and then checks if the array is sorted.

This occurs repeatedly until the array is sorted.

[!Bogosort](https://c.tenor.com/Dmema-SD11UAAAAC/bogo-moment-bogo-sort.gif)

## Slowsort
Slowsort is a humorous algorithm based on the principle of *multiply and surrender*, opposed to *divide and conquer*.
This principle involved replacing the problem with slightly simpler subproblems, continuing to do so over and over recursilvely for as long as possible until the problem is solved and the algorithm "surrenders".

An example for performance is the algorithm hanging for arrays of only size 1000.

[!Slowsort](http://5b0988e595225.cdn.sohucs.com/images/20190619/9ef07b65b9ca4995991c33ee06974655.gif)

## Stooge Sort
Stooge sort is a recursive sorting algorithm named after the film, *The Three Stooges*.

The algorithm simply recursively calls stooge sort for each third of the array, consequently resulting in it's poor performance.

[!Stooge Sort](https://upload.wikimedia.org/wikipedia/commons/f/f8/Sorting_stoogesort_anim.gif)
