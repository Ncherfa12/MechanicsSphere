#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

// Function to compute y'(x) for the Shortest Path Problem
double shortest_path_derivative(double y, double c) {
    return sqrt(fabs(1 + c));
}

// Function to compute y'(x) for the Broken Extremal Problem
double broken_extremal_derivative(double y, double c) {
    return sqrt(fabs(y * y - c));
}

// General solver function
void solve_problem(std::vector<double>& x_vals, std::vector<double>& y_vals,
                   double (*derivative_func)(double, double),
                   double x0, double y0, double x_end, double step, double c) {
    double x = x0;
    double y = y0;

    while (x < x_end) {
        x_vals.push_back(x);
        y_vals.push_back(y);

        // Compute y'(x), update y
        double dy = derivative_func(y, c) * step;
        y += dy;
        x += step;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./numerical_solver <problem_type>" << std::endl;
        std::cerr << "problem_type: shortest_path or broken_extremal" << std::endl;
        return 1;
    }

    std::string problem_type = argv[1];
    double c, x0, y0, x_end, step;
    std::vector<double> x_vals, y_vals;

    // Problem-specific ICs etc
    if (problem_type == "shortest_path") {
        std::cout << "Solving Shortest Path Problem..." << std::endl;
        c = 0;            // Constant for shortest path (can be ignored)
        x0 = 0.0;         // Starting x
        y0 = 0.0;         // Starting y
        x_end = 1.0;      // Ending x
        step = 0.01;      // Step size
        solve_problem(x_vals, y_vals, shortest_path_derivative, x0, y0, x_end, step, c);
    } else if (problem_type == "broken_extremal") {
        std::cout << "Solving Broken Extremal Problem..." << std::endl;
        c = 0.5;          // Example constant for y^2 - c
        x0 = 0.0;         // Starting x
        y0 = 0.0;         // Starting y
        x_end = 1.0;      // Ending x
        step = 0.01;      // Step size
        solve_problem(x_vals, y_vals, broken_extremal_derivative, x0, y0, x_end, step, c);
    } else {
        std::cerr << "Unknown problem type: " << problem_type << std::endl;
        return 1;
    }

    // Write as CSV
    std::string output_file = "src/" + problem_type + "_solution.csv";
    std::ofstream output(output_file);
    output << "x,y\n";  // for clarity
    for (size_t i = 0; i < x_vals.size(); ++i) {
        output << x_vals[i] << "," << y_vals[i] << "\n";
    }
    output.close();

    std::cout << "Solution written to " << output_file << std::endl;

    return 0;  // End
}
