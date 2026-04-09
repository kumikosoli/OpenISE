import math

def calculate_noise(x, y, z, m):
    """
    计算公式：
    x + 10 * log10(y / z) + 10 * log10((7.5 / m)^1.5) - 16
    """
    result = x + 10 * math.log10(y / z) + 10 * math.log10((7.5 / m) ** 1.5) - 16
    return result

# 示例用法（你可以修改这些值）
x = 79
y = 149
z = 40
m = 200

value = calculate_noise(x, y, z, m)
print("计算结果为：", value)
