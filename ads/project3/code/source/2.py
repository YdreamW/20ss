# O(N*M)
import sys
import time
N = 200050
mod = 1000000007

f = [0] * N     # f[] is the array to be used for dynamic programming
tmp = [0] * N   # tmp[] is an array of value fields


# Input data, the name of array is the same as the problem
n, m = map(int,sys.stdin.readline().split())
a = [0] + list(map(int, sys.stdin.readline().split()))

start = time.time()

# Setting initial value
ans = 1
f[0] = 1
S = 1
for i in range(1, n+1):
    ans = ans * 2 % mod

# Dynamic programming
for i in range(1, n+1):
    
    # f[] equals the sum of all other elements minus the sum of adjacent intervals
    f[i] = S
    for j in range(max(0, a[i]-m), a[i]+m+1):
        f[i] = (f[i] - tmp[j] + mod) % mod
    
    # Update valuee
    tmp[ a[i] ] = (tmp[ a[i] ] + f[i]) % mod 
    S = (S + f[i]) % mod #
    ans = (ans - f[i] + mod) % mod

# This step is to remove the empty subsequence
ans = (ans - 1 + mod) % mod

end = time.time()

# Output answer
print("The ans of program O(N*M) is: ",ans)
print("The time of program O(N*M) is: ",end-start)
print("\n")