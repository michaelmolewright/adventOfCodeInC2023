f = open("puzzle.txt", "r")
vals = [-7, -12, -17, -19, -1, 80, 320, 924, 2313, 5335, 11696, 24823, 51490, 104671, 208280, 404983, 769974, 1438716, 2670276, 5000869, 9616078]

def dif(a,b):
    if a > b:
        return a - b
    else:
        return b - a

def findVals(numbers):
    newline = []
    zeros = True
    for i in range(1, len(numbers)):
        newline.append(numbers[i] - numbers[i-1])
        
        if newline[i-1] != 0:
            zeros = False
    
    if zeros:
        return 0
    else:
        return newline[len(newline)-1] + findVals(newline)

total = 0
i = 0
for x in f:
    arr = x.strip("\n").split(" ")
    for a in range(0,len(arr)):
        arr[a] = int(arr[a])
    
    newval = arr[-1] + findVals(arr)
    total += newval
    print(i,", ",newval)
    i += 1

print(total)