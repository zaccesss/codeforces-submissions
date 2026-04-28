# Read the 5x5 matrix and find the position of the single 1
for i in range(5):
    row = input().split()  # read each row as a list of strings
    for j in range(5):
        if row[j] == '1':  # found the 1
            # minimum moves = manhattan distance to centre (row 3, col 3 = index 2,2)
            print(abs(i - 2) + abs(j - 2))