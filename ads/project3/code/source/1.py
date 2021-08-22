# O(N^2)
import sys
import time
N = 200050
mod = 1000000007

# Input data, the name of array is the same as the problem
n, m = map(int,sys.stdin.readline().split())
a = [0] + list(map(int, sys.stdin.readline().split()))

start = time.time()

# Setting initial value
ans = 1
f = [0] * N
for i in range(1, n+1):
    ans = ans * 2 % mod

# dynamic programming
f[0] = 1
a[0] = -N # Set a [0] to a small enough value
for i in range(1, n+1):
    for j in range(0, i):
        if (abs(a[i] - a[j]) > m):
            f[i] = (f[i] + f[j]) % mod
    ans = (ans - f[i] + mod) % mod

# This step is to remove the empty subsequence
ans = (ans - 1 + mod) % mod

end = time.time()
# Output answer
print("The ans of program O(N^2) is: ",ans)
print("The time of program O(N^2) is: ",end-start)
print("\n")