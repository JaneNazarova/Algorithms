#include <iostream>
#include <vector>
#include <cmath>
#include <random>

bool is_inside_circle(double center_x, double center_y, double radius, double x, double y);
void calculate_area_monte_carlo(std::vector<double>& circle1_params, std::vector<double>& circle2_params, std::vector<double>& circle3_params, bool use_intersection_bounds);

int main() {
    std::vector<double> circle1_params = {1.0, 1.0, 1.0};
    std::vector<double> circle2_params = {1.5, 2.0, std::sqrt(5.0) / 2.0};
    std::vector<double> circle3_params = {2.0, 1.5, std::sqrt(5.0) / 2.0};

    calculate_area_monte_carlo(circle1_params, circle2_params, circle3_params, true);
    return 0;
}

bool is_inside_circle(double center_x, double center_y, double radius, double x, double y) {
    double dx = x - center_x;
    double dy = y - center_y;
    return dx * dx + dy * dy <= radius * radius;
}

void calculate_area_monte_carlo(std::vector<double>& circle1_params, std::vector<double>& circle2_params, std::vector<double>& circle3_params, bool use_intersection_bounds) {
    double x_min, x_max, y_min, y_max;

    if (use_intersection_bounds) {
        x_min = std::max(std::max(circle1_params[0] - circle1_params[2], circle2_params[0] - circle2_params[2]), circle3_params[0] - circle3_params[2]);
        x_max = std::min(std::min(circle1_params[0] + circle1_params[2], circle2_params[0] + circle2_params[2]), circle3_params[0] + circle3_params[2]);
        y_min = std::max(std::max(circle1_params[1] - circle1_params[2], circle2_params[1] - circle2_params[2]), circle3_params[1] - circle3_params[2]);
        y_max = std::min(std::min(circle1_params[1] + circle1_params[2], circle2_params[1] + circle2_params[2]), circle3_params[1] + circle3_params[2]);
    } else {
        x_min = std::min(std::min(circle1_params[0] - circle1_params[2], circle2_params[0] - circle2_params[2]), circle3_params[0] - circle3_params[2]);
        x_max = std::max(std::max(circle1_params[0] + circle1_params[2], circle2_params[0] + circle2_params[2]), circle3_params[0] + circle3_params[2]);
        y_min = std::min(std::min(circle1_params[1] - circle1_params[2], circle2_params[1] - circle2_params[2]), circle3_params[1] - circle3_params[2]);
        y_max = std::max(std::max(circle1_params[1] + circle1_params[2], circle2_params[1] + circle2_params[2]), circle3_params[1] + circle3_params[2]);
    }

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_real_distribution<> x_distribution(x_min, x_max);
    std::uniform_real_distribution<> y_distribution(y_min, y_max);

    for (int total_points = 100; total_points <= 100000; total_points += 500) {
        double points_inside = 0;

        for (int point_index = 0; point_index < total_points; ++point_index) {
            double x_coord = x_distribution(generator);
            double y_coord = y_distribution(generator);

            bool inside_circle1 = is_inside_circle(circle1_params[0], circle1_params[1], circle1_params[2], x_coord, y_coord);
            bool inside_circle2 = is_inside_circle(circle2_params[0], circle2_params[1], circle2_params[2], x_coord, y_coord);
            bool inside_circle3 = is_inside_circle(circle3_params[0], circle3_params[1], circle3_params[2], x_coord, y_coord);

            if (inside_circle1 && inside_circle2 && inside_circle3) {
                ++points_inside;
            }
        }

        double bounding_area = (x_max - x_min) * (y_max - y_min);
        double intersection_area = (points_inside / total_points) * bounding_area;

        std::cout << total_points << ' ' << intersection_area << '\n';
    }
}