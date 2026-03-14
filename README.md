# 1D Heat Diffusion Problem Solver

This repository contains C++ code for solving the **1D heat diffusion problem** (steady-state) using a **finite difference method** and a **tridiagonal matrix solver**. The solution computes the temperature distribution along a one-dimensional rod given boundary conditions and a forcing term.

---

## Features

- **Tridiagonal Matrix Representation**: Efficiently stores and operates on tridiagonal matrices, common in 1D finite difference schemes.  
- **Thomas Algorithm Solver**: Implements the Thomas algorithm (specialized Gaussian elimination) for solving tridiagonal systems.  
- **Customizable Forcing Term**: Users can define any spatial forcing function `f(x)` for the heat equation.  
- **Dirichlet Boundary Conditions**: Supports fixed temperatures at the ends of the rod (`alpha` and `beta`).  
- **Error Analysis**: Computes the error norm by comparing the numerical solution with the analytical solution when available.

---

## Mathematical Model

We solve the **1D steady-state heat equation**:

\[
-\frac{d^2 u}{dx^2} = f(x), \quad x \in [0, L]
\]

with **Dirichlet boundary conditions**:

\[
u(0) = \alpha, \quad u(L) = \beta
\]

The domain `[0, L]` is discretized into `N` intervals with spacing `h = L / (N + 1)`. The finite difference approximation leads to a tridiagonal system:

\[
A \mathbf{u} = \mathbf{f}
\]

where `A` is a tridiagonal matrix and `f` is the forcing term scaled by `h^2`.

---

## File Structure

- **main.cpp** – Contains the main program:
  - Defines the domain and forcing term.
  - Constructs the tridiagonal matrix.
  - Solves the linear system.
  - Computes and prints the error norm.
  
- **TridiagonalMatrix** – Class implementing:
  - Matrix storage for sub-diagonal, diagonal, and super-diagonal.
  - Element access and modification.
  - Thomas algorithm solver.

- **HeatDiffusion** – Class for managing problem parameters:
  - Domain length `L`.
  - Forcing term `f(x)`.
  - Boundary conditions `alpha` and `beta`.

---

## How to Run

1. Clone the repository:  
   ```bash
   git clone https://github.com/username/1D-heat-diffusion-problem.git
   cd 1D-heat-diffusion-problem

2. Compile the program
   ```bash
   g++ -o heat_solver main.cpp -std=c++17 -lm

3. Run the executable
   ```bash
   ./heat_solver
