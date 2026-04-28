for i in range(5):
    row = input().split()  # read each row
    for j in range(5):
        if row[j] == '1':  # found the 1
            print(abs(i - 2) + abs(j - 2))  # distance to centre (row 3, col 3 = index 2,2)