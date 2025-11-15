# txt to csv
with open("output.txt", "r") as f:
    lines = f.readlines()

method1_started = False
method2_started = False
data1 = []
data2 = []

for line in lines:
    line = line.strip()
    if "# Method 1" in line:
        method1_started = True
        method2_started = False
        continue
    elif "# Method 2" in line:
        method1_started = False
        method2_started = True
        continue
    elif line == "":
        continue

    if method1_started and not line.startswith("#"):
        parts = line.split()
        if len(parts) == 2:
             data1.append(f"{parts[0]},{parts[1]}\n")
    elif method2_started and not line.startswith("#"):
        parts = line.split()
        if len(parts) == 2:
             data2.append(f"{parts[0]},{parts[1]}\n")

with open("data_method1.csv", "w") as f:
    f.write("N,S_rec\n")
    f.writelines(data1)

with open("data_method2.csv", "w") as f:
    f.write("N,S_rec\n")
    f.writelines(data2)
