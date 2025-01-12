import sympy as sp

def euler_lagrange(functional, y, x, save_to_file = False, output_file = "euler_lagrande_output.txt"):

    """ Function that derives the EL equation from a functional
    functional param: F(y, y', x)
    y param: dependent variable (function of x)
    x param: independent variable
    save_to_file param: saving derived equation (.txt)
    output_file: saving file path 
    return: EL equation as a symbolic expression
    """

    y_prime = sp.Derivative(y, x)
    dF_dy = sp.diff(functional, y)  # ∂F/∂y
    dF_dyprime = sp.diff(functional, y_prime)  # ∂F/∂y'
    d_dyprime_dx = sp.diff(dF_dyprime, x)  # d/dx (∂F/∂y')
    euler_eq = sp.simplify(dF_dy - d_dyprime_dx)  # ∂F/∂y - d/dx (∂F/∂y')
    
    if save_to_file:
        with open(output_file, "w") as f:
            f.write(f"Functional: {functional}\n")
            f.write(f"Euler-Lagrange Equation: {euler_eq}\n")
        print(f"Euler-Lagrange equation saved to {output_file}")
    return euler_eq

if __name__ == "__main__":
    x = sp.Symbol('x')
    y = sp.Function('y')(x)
    
    # Example Functional: Shortest Path Problem
    functional = sp.sqrt(1 + sp.diff(y, x)**2)  # ∫sqrt(1 + (y')^2) dx
    euler_eq = euler_lagrange(functional, y, x, save_to_file=True)
    print(f"Euler-Lagrange Equation: {euler_eq}")