# O(N*logN)

import sys
import time
N = 200050
mod = 1000000007
MAXA = 100000

# This part is the program of Binary Indexed Tree(B.I.T)
# including the sum of query prefix and single modification.
# B.I.T

# Take the lowest bit of binary number.
def lowbit(t):
    return t&(-t)

# This function is used to query the prefix sum.
def query(t):
    ret = 0
    i = t
    while (i >= 1):
        ret = (ret + tr[i]) % mod
        i -= lowbit(i)
    return ret

# This procedure is used to modify a value in B.I.T.
def update(t, v):
    i = t
    while (i <= MAXA):
        tr[i] = (tr[i] + v) % mod
        i += lowbit(i)

# Input data, the name of array is the same as the problem
n, m = map(int,sys.stdin.readline().split())
a = [0] + list(map(int, sys.stdin.readline().split()))

start = time.time()
# Setting initial value
ans = 1
f = [0] * N
tr = [0] * N
for i in range(1, n+1):
    ans = ans * 2 % mod

# dynamic programming
f[0] = 1
S = 1
for i in range(1, n+1):
    f[i] = S

    # Using data structure to calculate the value 
    # of dynamic programming
    cur = query(a[i]+m)
    if (a[i]-m-1 >= 0):
        cur = (cur - query(a[i]-m-1) + mod) % mod

    f[i] = (f[i] - cur + mod) % mod
    S = (S + f[i]) % mod
    ans = (ans - f[i] + mod) % mod

    # Update values in B.I.T.
    update(a[i], f[i]) 
    
# This step is to remove the empty subsequence
ans = (ans - 1 + mod) % mod

end = time.time()
# Output answer
print("The ans of program O(N*logN) is: ",ans)
print("The time of program O(N*logN) is: ",end-start)
print("\n")