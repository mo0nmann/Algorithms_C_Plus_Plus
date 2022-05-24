# Exchange Sorting Algorithms

**Exchange sorting algorithms *sort by exchanging* pairs of items until the sequence is sorted**.

Below is a table outlining the details of each algorithm

|  Algorithm | Worst Complexity  | Average Complexity | Best Complexity   | Space Complexity  | Stable  |
| ------------ | ------------ | ------------ | ------------ | ------------ | ------------ |
| **Bubble Sort**  | *O(n<sup>2</sup>)*  |  *Ω(n<sup>2</sup>)* | *Θ(n)*  |  *O(1)* | Yes  |
| **Cocktail Shaker Sort**  | *O(n<sup>2</sup>)*  | *Ω(n<sup>2</sup>)*  | *Θ(n)*  |  *O(1)* | Yes  |
| **Comb Sort**  |  *O(n<sup>2</sup>)* |  *Ω(n<sup>2</sup>/2<sup>p</sup>)*, where p is the  number of increments | *Θ(n log n)*  | *O(1)*  | No |
|   **Exchange Sort** |  *O(n<sup>2</sup>)* | *Ω(n<sup>2</sup>)*  |  *Θ(n<sup>2</sup>)* |  *O(1)* |   Yes|
|   **Gnome Sort** |  *O(n<sup>2</sup>)* |  *Ω(n<sup>2</sup>)* |  *Θ(n)* |  *O(1)* |  Yes |
|  **Odd-Even Sort** | *O(n<sup>2</sup>)*  |  *O(n<sup>2</sup>)* |  *Θ(n)* | *O(1)*  |  Yes |
| **Quicksort**   | *O(n<sup>2</sup>)*  | *Ω(n log n)*  | *Θ(n log n)*  | *O(log n)*  | No  |

## Bubble Sort
Bubble sort simply moves repeatedly from right to left through the list, comparing adjacent elements and swapping them if they are in wrong order. 

![Bubble Sort](https://upload.wikimedia.org/wikipedia/commons/c/c8/Bubble-sort-example-300px.gif)

## Cocktail Shaker Sort
Cocktail Shaker Sort extends on Bubble sort by operating in two directions. The algorithm first moves from left to right, swapping elements. Once reaching the end, the algorithm then moves right to left, swapping any incorrectly ordered elements.

This offers marginal performance improvements over bubble sort.

![Cocktail Shaker Sort](https://upload.wikimedia.org/wikipedia/commons/e/ef/Sorting_shaker_sort_anim.gif)

## Comb Sort
Rather than simply comparing elements that are 1 element apart, comb sort expands on bubble sort by being able to compare and swap elements further apart.

This is performed by changing the inner loop of bubble sort, such that the gap between swapped elements goes down each iteration in steps of a "shrink factor", *k*, which is generally 1.3.

The gap starts out as the list length dividied by *k* = 1.3, which has been suggested as the ideal shrink factor.

![Comb Sort](https://upload.wikimedia.org/wikipedia/commons/4/46/Comb_sort_demo.gif)

## Exchange Sort
The exchange sort is similar to bubble sort, in that it compares elements of the array and swaps those that are out of order.

Unlike bubble sort, exchange sort compares the first element with each following element of the array, making any necessary swaps.

![Exchange Sort](https://mathbits.com/MathBits/Java/arrays/ExchangeChart.jpg)

## Gnome Sort
The gnome sort algorithm iteratively checks the order of pairs in an array. If they are in the right order it moves to the next pair, otherwise it swaps the elements, repeating the process until no more swaps are made.

The algorithm itself is based upon *how a garden gnome sorts a line of flower pots*. Which is as follows:

*"Basically, he looks at the flower pot next to him and the previous one; if they are in the right order he steps one pot forward, otherwise, he swaps them and steps one pot backward."* 
> "Gnome Sort - The Simplest Sort Algorithm". *Dickgrune.com*

![Gnome Sort](https://upload.wikimedia.org/wikipedia/commons/8/89/Visualization_of_Gnome_sort.gif)

## Odd-Even Sort
Odd-even sort is a variation of bubble-sort, which is divided into two phases-Odd and Even Phase. The algorithm runs until the array elements are sorted, and in each iteration bubble sort is performed on the odd elements and then the even elements. 

The algorithm was originally developed for use on parallel processors with local interconnections with each phase being run on a different processor.

![Odd-Even Sort](https://upload.wikimedia.org/wikipedia/commons/1/1b/Odd_even_sort_animation.gif)

## Quicksort
Quicksort is a divide and conquer algorithm suitable for small to medium arrays. For example, sorting an array of 1 million random integers took under 1 minute on my device.

The algorithm works by picking a 'pivot' element from the array, and partitioning the other elements into two sub-arrays. These sub-arrays involve an array with all elements lesser than the pivot element and one with all elements greater than the pivot element.

These sub-arrays are then sorted recursively until the array is sorted.

![Quicksort](https://upload.wikimedia.org/wikipedia/commons/6/6a/Sorting_quicksort_anim.gif)

There are a few ways of choosing the pivot element for partitioning.

- The first element
- The last element
- Random element
- Median-of-three

The first three are fairly explanitory, however the median-of-three method involves calculating the median of the first, last, and middle element of the array - whilst also sorting these three in order.
This is done to counter issues caused by the other methods, such as having the algorithm degrate to *O(n<sup>2</sup>)* when the array is already in order.

The code included in quicksort.cpp utilises the median-of-three method for optimisation.

