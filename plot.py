import numpy as np
import matplotlib.pyplot as plt

method1_data = []
method2_data = []

with open("output.txt", "r") as f:
    lines = f.readlines()
current_method = None

for line in lines:
    line = line.strip()
    if not line:
        continue
    if "# Method 1" in line:
        current_method = "method1"
        continue
    elif "# Method 2" in line:
        current_method = "method2"
        continue
    elif line.startswith("#"):
        continue

    parts = line.split()
    if len(parts) == 2:
        try:
            N = int(parts[0])
            S_rec = float(parts[1])
            if current_method == "method1":
                method1_data.append((N, S_rec))
            elif current_method == "method2":
                method2_data.append((N, S_rec))
        except ValueError:
            continue

method1_data = np.array(method1_data)
method2_data = np.array(method2_data)
N1, S1 = method1_data[:, 0], method1_data[:, 1]
N2, S2 = method2_data[:, 0], method2_data[:, 1]

exact_area = 0.9445
relative_error1 = np.abs(S1 - exact_area) / exact_area * 100
relative_error2 = np.abs(S2 - exact_area) / exact_area * 100

# График 1
plt.figure(figsize=(10, 6))

plt.plot(N1, S1, label='Способ 1 (Широкая область)', color='blue', linewidth=1.5)
plt.plot(N2, S2, label='Способ 2 (Узкая область)', color='red', linewidth=1.5)
plt.axhline(y=exact_area, color='green', linestyle='--', linewidth=2, label=f'Точная площадь ({exact_area:.4f})')

plt.xlabel('Количество точек N')
plt.ylabel('Приближенная площадь $S_{rec}$')
plt.title('Зависимость приближенной площади от количества точек N')
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()

# График 2:
def moving_average(data, window_size=50):
    if len(data) < window_size:
        return data
    cumsum = np.cumsum(np.insert(data, 0, 0))
    return (cumsum[window_size:] - cumsum[:-window_size]) / window_size
smooth_error1 = moving_average(relative_error1, window_size=50)
smooth_error2 = moving_average(relative_error2, window_size=50)
N1_smooth = N1[len(N1) - len(smooth_error1):]
N2_smooth = N2[len(N2) - len(smooth_error2):]

plt.figure(figsize=(10, 6))
plt.plot(N1_smooth, smooth_error1, label='Способ 1', color='blue', linewidth=1.5)
plt.plot(N2_smooth, smooth_error2, label='Способ 2', color='red', linewidth=1.5)
plt.xlabel('Количество точек N')
plt.ylabel('Отклонение (%)')
plt.title('Зависимость относительного отклонения от количества точек')
plt.legend()
plt.grid(True, alpha=0.3)
plt.ylim(0, 25)
plt.tight_layout()
plt.show()