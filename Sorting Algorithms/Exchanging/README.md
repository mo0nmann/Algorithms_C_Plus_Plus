# Exchange Sorting Algorithms

**Exchange sorting algorithms *sort by exchanging* pairs of items until the sequence is sorted**.

Below is a table outlining the details of each algorithm

|  Algorithm | Worst Complexity  | Average Complexity | Best Complexity   | Space Complexity  | Stable  |
| ------------ | ------------ | ------------ | ------------ | ------------ | ------------ |
| **Bubble Sort**  | *O(n<sup>2</sup>)*  |  *Ω(n<sup>2</sup>)* | *Θ(n)*  |  *O(1)* | Yes  |
| **Cocktail Shaker Sort**  | *O(n<sup>2</sup>)*  | *Ω(n<sup>2</sup>)*  | *Θ(n)*  |  *O(1)* | Yes  |
| **Comb Sort**  |  *O(n<sup>2</sup>)* |  *Ω(n<sup>2</sup>/2<sup>p</sup>)*, <sup> where p is the  number of increments</sup> | *Θ(n log n)*  | *O(1)*  | No |
|   **Exchange Sort** |  *O(n<sup>2</sup>)* | *Ω(n<sup>2</sup>)*  |  *Θ(n<sup>2</sup>)* |  *O(1)* |   Yes|
|   **Gnome Sort** |  *O(n<sup>2</sup>)* |  *Ω(n<sup>2</sup>)* |  *Θ(n)* |  *(O(1)* |  Yes |
|  **Odd-Even Sort** | *O(n<sup>2</sup>)*  |  *O(n<sup>2</sup>)* |  *Θ(n)* | *O(1)*  |  Yes |
| **Quicksort**   | *O(n<sup>2</sup>)*  | *Ω(n log n)*  | *Θ(n log n)*  | *O(log n)*  | No  |

### Bubble Sort
Bubble sort simply moves repeatedly from right to left through the list, comparing adjacent elements and swapping them if they are in wrong order. 

![Bubble Sort]
(https://upload.wikimedia.org/wikipedia/commons/c/c8/Bubble-sort-example-300px.gif)

### Cocktail Shaker Sort
Cocktail Shaker Sort extends on Bubble sort by operating in two directions. The algorithm first moves from left to right, swapping elements. Once reaching the end, the algorithm then moves right to left, swapping any incorrectly ordered elements.

This offers marginal performance improvements over bubble sort.

![Cocktail Shaker Sort]
(https://upload.wikimedia.org/wikipedia/commons/e/ef/Sorting_shaker_sort_anim.gif)

### Comb Sort
Rather than, simply comparing elements that are 1 element apart, comb sort expands on bubble sort by being able to compare and swap elements further apart.

This is performed by changing the inner loop of bubble sort, such that the gap between swapped elements goes down each iteration in steps of a "shrink factor", *k*, which is generally 1.3.

The gap starts out as the list length dividied by *k* = 1.3, which has been suggested as the ideal shrink factor.

![Comb Sort]
(https://upload.wikimedia.org/wikipedia/commons/4/46/Comb_sort_demo.gif)

### Exchange Sort

### Gnome Sort

### Odd-Even Sort

### Quicksort
