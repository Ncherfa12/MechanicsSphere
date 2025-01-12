using Pkg
Pkg.add(["DifferentialEquations", "CSV", "DataFrames", "Plots"])

using DifferentialEquations, CSV, DataFrames

# Define the ODE system
function shortest_path!(du, u, p, t)
    du[1] = u[2]  # dy/dx = y'
    du[2] = 0.0   # d^2y/dx^2 = 0
end

# Solve
y0 = [0.0, 1.0]  # ICs
tspan = (0.0, 1.0)
prob = ODEProblem(shortest_path!, y0, tspan)
sol = solve(prob)

# Save as CSV
df = DataFrame(x=sol.t, y=sol.u[:, 1])
CSV.write("shortest_path_solution.csv", df)
println("Solution saved to shortest_path_solution.csv")
