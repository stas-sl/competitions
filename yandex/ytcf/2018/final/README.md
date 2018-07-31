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

# C. Ant taxi

# D. Fate lines

