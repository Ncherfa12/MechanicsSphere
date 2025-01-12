#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// Define the system of ODEs (e.g., Shortest Path Problem)
void shortest_path_ode(double x, const std::vector<double>& y, std::vector<double>& dydx) {
    dydx[0] = y[1];  // dy/dx = y'
    dydx[1] = 0.0;   // d^2y/dx^2 = 0 (Euler-Lagrange for shortest path)
}

// Numerical solver using the Euler method
void euler_solver(double x0, double x1, double h, const std::vector<double>& y0, 
                  void (*ode)(double, const std::vector<double>&, std::vector<double>&), 
                  const std::string& output_file) {
    double x = x0;
    std::vector<double> y = y0;
    std::vector<double> dydx(y.size());

    // Open output file
    std::ofstream file(output_file);
    file << "x,y\n";

    // Write initial conditions
    file << x << "," << y[0] << "\n";

    // Euler integration loop
    while (x <= x1) {
        // Compute derivatives
        ode(x, y, dydx);

        // Update y values using Euler's method
        for (size_t i = 0; i < y.size(); ++i) {
            y[i] += h * dydx[i];
        }

        // Update x
        x += h;

        // Write to file
        file << x << "," << y[0] << "\n";
    }

    file.close();
    std::cout << "Solution saved to " << output_file << std::endl;
}

int main() {
    // Define problem parameters
    double x0 = 0.0;        // Start of the interval
    double x1 = 1.0;        // End of the interval
    double h = 0.01;        // Step size
    std::vector<double> y0 = {0.0, 1.0}; // Initial conditions: y(0) = 0, y'(0) = 1

    // Output file
    std::string output_file = "shortest_path_solution.csv";

    // Solve the problem
    euler_solver(x0, x1, h, y0, shortest_path_ode, output_file);

    return 0;
}
