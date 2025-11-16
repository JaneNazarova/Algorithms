#include <iostream>
#include <vector>
#include <random>

struct Circle {
    double x, y, r;
};

int main() {
    std::vector<Circle> circles(3);

    // Чтение входных данных
    for (int i = 0; i < 3; i++) {
        std::cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }

    // Определяем ограничивающий прямоугольник
    double min_x = 1e9, max_x = -1e9, min_y = 1e9, max_y = -1e9;
    for (const auto& circle : circles) {
        min_x = std::min(min_x, circle.x - circle.r);
        max_x = std::max(max_x, circle.x + circle.r);
        min_y = std::min(min_y, circle.y - circle.r);
        max_y = std::max(max_y, circle.y + circle.r);
    }

    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist_x(min_x, max_x);
    std::uniform_real_distribution<double> dist_y(min_y, max_y);

    // Количество испытаний
    const int num_points = 1000000;
    int count = 0;

    // Метод Монте-Карло
    for (int i = 0; i < num_points; i++) {
        double x = dist_x(gen);
        double y = dist_y(gen);

        bool in_all_circles = true;
        for (const auto& circle : circles) {
            double dx = x - circle.x;
            double dy = y - circle.y;
            if (dx * dx + dy * dy > circle.r * circle.r) {
                in_all_circles = false;
                break;
            }
        }

        if (in_all_circles) {
            count++;
        }
    }

    // Вычисление площади
    double area_rect = (max_x - min_x) * (max_y - min_y);
    double area_intersection = (static_cast<double>(count) / num_points) * area_rect;

    std::cout.precision(20);
    std::cout << area_intersection << std::endl;

    return 0;
}