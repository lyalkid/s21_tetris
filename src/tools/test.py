n = 20
m = 10
b = [[0 for i in range(m)] for i in range(n)]
k = 0
a = [0,0,1, 0, -1, 0]

dx = 5
dy = 5
for i in range(0, len(a), 2):
    x = a[i] + dx 
    y = a[i+1] + dy
    b[x][y] = 1

for i in range( n):
    for j in range(m):
        if ( (b[i][j] == 1)):
            print("*", end='')
        else:
            print("`", end='')
    print()