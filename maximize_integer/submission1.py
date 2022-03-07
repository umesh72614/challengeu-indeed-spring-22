"""
    Language: python3
    Submitted By: 
        Umesh Yadav 
        (github.com/umesh72614)
        (hackerrank.com/2018ucs0078)
    Score: 40/40
"""

# use python as x can be very very large
# also no need to convert x into int as <,> are valid in strings also
x = input()
rx = x[::-1]
n = len(x)  # num of digits
d = max(list(x))    # maxDigit
m = '0'     # store ans
for i in range(1, n):
    # don't perform operation if digit is not maxDigit (GREEDY)
    if (x[i-1] != d):
        continue
    # y = x[:i][::-1] + x[i:][::-1]
    # Below is the optimization to avoid reverse at each step
    y = rx[n-i:] + rx[:n-i]
    # if y is smaller than m then discard it
    if y > m:
        m = y
print(x if m == '0' else m)
