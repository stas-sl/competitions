https://contest.yandex.ru/ytcf/contest/8527/enter/

# A. Subsystems test

The task is to check if it is possible combine 2 strings **a** and **b** to get string **c** preserving character order.

We can use dynamic programming here. **dp(i, j)** - will store **true** if using **i** first characters of string **a** and **j** first characters of string **b** we can get **i+j** first characters of string **c**, and **false** otherwise.

Then recursive rule will be:

**dp(0, 0)** = true

**dp(i, j)** = (**dp(i-1, j)** if c[i+j-1] == a[i-1]) OR (**dp(i, j-1)** if c[i+j-1] == b[j-1])

Then the answer wil be **dp(length(a), length(b))**.

Time complexity is **O(length(a) * length(b))**. 

Unfortunately python solution was very slow and got TL running **> 6 sec** for large inputs. While C++ solution took only **50ms**. I wonder if there are more optmal solutions so that python version got accepted.

# B. Teleport

In this task we have a teleport represented as a polygon and cars that at specific timestamps get into this polygon or outisde of it. Teleport is being opened at specific timestamps and when it is opened and a car is in inside it, it is being teleported. We should tell for each opening timestamp which cars are teleported if any at this moment.

The solution consists of 3 subtasks:

1. For each car and its position we should be able to determine whether the point is inside or outside the polygon. We can do it using [winding number algorithm](https://codeforces.com/blog/entry/48868). Note that polygon can be non-convex and points on its border are considered to be inside.
2. Then for each car we sequentially iterate over all its positions and build time intervals **[a; b)** when the car is inside the polygon. Note that a single car can have multiple disjoint time intervals. After collecting all such intervals, we sort them first by **a** and then by the car number.
3. When we have such a list of sorted time intervals and timestamps for which we'd like to tell what car will be teleported, we can just iterate over each timestamp and keep a pointer to "current interval". There could be a few cases how current interval **[a; b)** an be related to the current timestamp **k**:
   - if **b <= k**, then we increase the pointer
   - if **a <= k < b**, we print current car number and increase the pointer
   - if **k > a**, we print **-1** and keep the pointer at the same index and proceed to the next timestamp

Time complexity is **O(N*log(N))**, where **N** - is number of all car positions.

# C. Ant taxi

We have an anthill orgainzed as layers of multiple cells. Cells of each layer are connected with all cells in the layers directly below and above it. Given distances between all connected cells as well as source cell in the bottom layer and target cell in the top layer we should tell whether it is possible to get from source cell to the target cell passing exactly specified distance **D**.

We'll use dynamic programming here as well. Let's denote **dp(i, j, d)** - whether it is possible to get from the **j**-th cell of layer **i** into the source cell of the bottom layer passing exactly **d** meters. Then the answer will be stored in **dp(last layer number, target, D)**.

The recurrent rule will be:

**dp(0, source, 0)** = true

**dp(i, j, d)** = true if dp(i-1, k, d - distance(from k-th cell of i-1 layer to j-th cell of i-th layer)) is true for some k

Though if we will proceed with this approach as is we'll easily will run out of time. Thus we wll use 2 optimizations:

1. We'll precalculate for each **(i, j)** maximal distance to the source cell that is it possible to obtain at all. Then during computation of **dp(i, j, d)** we'll check if **d** is greater that maximal possible distance we'll just return false.
2. We'll cache all already calculated dp(i, j, d) to reuse the results if needed.

Overal complexity is **O(N\*M\*M)**, where **N** - is number of layers and **M** - is number of cells in each layer.

Using all these optimizations running time on the largest test case was just **3ms**.

# D. Fate lines

