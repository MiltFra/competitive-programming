import sys
if __name__ == "__main__":
    with open(sys.argv[1]) as f1:
        with open(sys.argv[2]) as f2:
            i = 0
            l1 = f1.readline()
            l2 = f2.readline()
            while l1 == l2 and l1:
                i += 1
                l1 = f1.readline()
                l2 = f2.readline()
            if l1:
                print(f"An error occurred on line {i+1}")
