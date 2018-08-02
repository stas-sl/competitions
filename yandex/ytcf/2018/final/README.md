https://contest.yandex.ru/ytcf/contest/8527/enter/

# A. Subsystems test

The task is to check if it is possible combine 2 strings **a** and **b** to get string **c** preserving character order.

We can use dynamic programming here. **dp(i, j)** - will store **true** if using **i** first characters of string **a** and **j** first characters of string **b** we can get **i+j** first characters of string **c**, and **false** otherwise.

Then recursive rule will be:

**dp(0, 0)** = true

**dp(i, j)** = (**dp(i-1, j)** if c[i+j-1] == a[i-1]) OR (**dp(i, j-1)** if c[i+j-1] == b[j-1])

Then the answer wil be **dp(length(a), length(b))**.

Time complexity is **O(length(a) * length(b))**. 

Unfortunately python solution was very slow and got TL running **> 6 sec** for large inputs. While C++ solution took only **50ms**. I wonder if there exists more optimal solution, so that python version got accepted.

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

Though if we will proceed with this approach as is we'll easily will run out of time. Thus we need to clip some paths: we'll precalculate for each **(i, j)** maximal distance to the source cell that is it possible to obtain at all. Then during computation of **dp(i, j, d)** we'll check if **d** is greater that maximal possible distance we'll just return false.

Overal complexity is **O(M^N)**, where **N** - is number of layers and **M** - is number of cells in each layer. Though this can become a really large number in worst case, probably because final tests were not that hard this solutions worked under **3ms** for each case.

Alternative (better) approach is known as **"meet in the middle"**, where we actually perform the same search but separatly for 2 halves of the graph and then merge the result. Namely we will start from the source cell in the bottom layer and collect all the distances that we can obtain from it to all cells in the middle layer. Then we'll perfrom the same procedure but staring from the target cell of the top layer and going from the top layer down to the middle layer. We'll end up with 2 sets of distances for each cell in the middle layer. Then we will just check for each cell in the middle layer if it is possible to find a pair of such distances that will sum to **D**. 

The complexity in this case will be **O(N\*M\*M^(N/2)\*log M)**.

Implementation details. My first implementation of this algorithm timed out because of slowness of `undordered_set`. When I replaced it with `vector,` though it might contain duplicates and needs sorting, it actually worked faster and the longest test took **259ms**. Unfortunately this algorithm run out of memory/time implemented in python using either `list` or `dict`.

# D. Fate lines

In this task we are given a binary tree with **N** nodes. Each node has some number in it - positive or negative. We can delete at most **K** nodes (deleting node also deletes all its descendents). The task to maximize total sum of all numbers in the tree deleting some of nodes.

Again, let's use dynamic programming. Let **dp(i, k)** - be the maximal sum we can obtain in subtree with root in **i**-th node deleting at most **k** nodes. Then the answer will be **dp(root, K)**.

The recurrent rule:

**dp(i, k)** = max{**dp(left, j)** + **dp(right, k-j)** + weight(i); 0 if k > 0} for j=0..k

When implementing this rule we'd like to sort the nodes in such order that when calculating **dp** for the parent we already have calculated results for its children. We can do this by assigning an order to each node as we traverse the tree using BFS. Then if we reverse resulting order we'll get exacly what we need: childs before parent.

Time complexity is **O(N*K^2)**.