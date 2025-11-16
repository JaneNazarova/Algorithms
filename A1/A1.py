import math
import numpy as np
import matplotlib.pyplot as plt

def check_point_in_circle(x_coord, y_coord, center_x, center_y, radius):
    return (x_coord - center_x)**2 + (y_coord - center_y)**2 <= radius**2

def estimate_area_monte_carlo(num_points, boundary_limits, circle_list):
    x_lower, x_upper, y_lower, y_upper = boundary_limits
    random_points = np.random.uniform([x_lower, y_lower], [x_upper, y_upper], size=(num_points, 2))
    
    inside_flags = np.all([
        check_point_in_circle(random_points[:, 0], random_points[:, 1], cx, cy, r) 
        for cx, cy, r in circle_list
    ], axis=0)
    
    rectangle_area = (x_upper - x_lower) * (y_upper - y_lower)
    return rectangle_area * np.sum(inside_flags) / num_points


circle_definitions = [(1, 1, 1), (1.5, 2, 5**0.5 / 2), (2, 1.5, 5**0.5 / 2)]
boundary_set_1 = (0, 3, 0, 3)
boundary_set_2 = (2 - 5**0.5 / 2, 2, 2 - 5**0.5 / 2, 2)

exact_area_value = 0.25 * math.pi + 1.25 * math.asin(0.8) - 1

point_counts = range(100, 100001, 500)
area_estimates_1 = []
error_percentages_1 = []
area_estimates_2 = []
error_percentages_2 = []

for current_points in point_counts:
    calculated_area_1 = estimate_area_monte_carlo(current_points, boundary_set_1, circle_definitions)
    area_estimates_1.append(calculated_area_1)
    relative_error_1 = abs(calculated_area_1 - exact_area_value) / exact_area_value * 100
    error_percentages_1.append(relative_error_1)

    calculated_area_2 = estimate_area_monte_carlo(current_points, boundary_set_2, circle_definitions)
    area_estimates_2.append(calculated_area_2)
    relative_error_2 = abs(calculated_area_2 - exact_area_value) / exact_area_value * 100
    error_percentages_2.append(relative_error_2)

plt.figure(figsize=(10, 6))
plt.plot(point_counts, area_estimates_1, label='Метод 1', color='blue')
plt.plot(point_counts, area_estimates_2, label='Метод 2', color='red')
plt.axhline(y=exact_area_value, color='black', linestyle='--', label='Точное значение площади')
plt.xlabel('Количество точек N')
plt.ylabel('Площадь')
plt.title('Зависимость оценки площади от количества точек')
plt.legend()
plt.grid()
plt.show()

plt.figure(figsize=(12, 6))
plt.plot(point_counts, error_percentages_1, label='Метод 1', color='blue')
plt.plot(point_counts, error_percentages_2, label='Метод 2', color='red')
plt.xlabel('Количество точек N')
plt.ylabel('Относительная погрешность (%)')
plt.title('Зависимость относительной погрешности от количества точек')
plt.legend()
plt.grid()
plt.show()
