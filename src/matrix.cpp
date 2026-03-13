#include <iostream>
#include <cmath>
#include <vector>

class Matrix {
public:
    virtual int getRows() const = 0;
    virtual int getColumns() const = 0;
    virtual double getElement(int i, int j) const = 0;
    virtual void setElement(int i, int j, double value) = 0;
    virtual void print() const = 0;
    virtual std::vector<double> solve(std::vector<double> &f) = 0; // Remove const
};

class TridiagonalMatrix : public Matrix {
public:
    TridiagonalMatrix(const std::vector<double> &a, const std::vector<double> &b, const std::vector<double> &c)
        : a(a), b(b), c(c) {}

    int getRows() const override {
        return b.size();
    }

    int getColumns() const override {
        return b.size();
    }

    double getElement(int i, int j) const override {
        if (i == j)
            return b[i];
        else if (i == j - 1)
            return a[i];
        else if (i == j + 1)
            return c[i];
        else
            return 0.0;
    }

    void setElement(int i, int j, double value) override {
        if (i == j)
            b[i] = value;
        else if (i == j - 1)
            a[i] = value;
        else if (i == j + 1)
            c[i] = value;
    }

    void print() const override {
    for (int i = 0; i < getRows(); ++i) {
        for (int j = 0; j < getColumns(); ++j) {
            if (i == j)
                std::cout << getElement(i, j) << "\t";
            else if (i == j - 1 || i == j + 1)
                std::cout << getElement(i, j) << "\t";
            else
                std::cout << "0\t";
        }
        std::cout << std::endl;
    }
}


    std::vector<double> solve(std::vector<double> &f) override { 
        int n = getRows();
        std::vector<double> u(n);

        // Step 1
        for (int i = 1; i < n; ++i) {
            double m = a[i] / b[i - 1];
            b[i] = b[i] - m * c[i - 1];
            f[i] = f[i] - m * f[i - 1];
        }

        // Step 2
        u[n - 1] = f[n - 1] / b[n - 1];

        for (int i = n - 1; i >= 1; --i)
            u[i - 1] = (f[i - 1] - c[i - 1] * u[i]) / b[i - 1];

        return u;
    }

private:
    std::vector<double> a, b, c;

};


class HeatDiffusion {
public:
    HeatDiffusion(double L, const std::function<double(double)> &forcingTerm, double alpha, double beta)
        : L(L), forcingTerm(forcingTerm), alpha(alpha), beta(beta) {}

    double getL() const {
        return L;
    }

    std::function<double(double)> getForcingTerm() const {
        return forcingTerm;
    }

    double getAlpha() const {
        return alpha;
    }

    double getBeta() const {
        return beta;
    }

private:
    double L;
    std::function<double(double)> forcingTerm;
    double alpha, beta;
};


int main() {

    double L = 1.0;
    auto forcingTerm = [](double x) { return -sin(M_PI * x); };
    double alpha = 0.0;
    double beta = 0.0;

    HeatDiffusion heatDiffusion(L, forcingTerm, alpha, beta);

    // Create TridiagonalMatrix from HeatDiffusion parameters
    int N = 5; // Adjust N as needed
    double h = L / (N + 1);

    std::vector<double> a(N, 1.0);
    std::vector<double> b(N + 1, -2.0);
    std::vector<double> c(N, 1.0);

    // Set the first and last elements of a and c
    a[0] = 0.0;
    b[0] = 1.0;
    b[N] = 1.0;
    c[N - 1] = 1.0;

    TridiagonalMatrix tridiagonalMatrix(a, b, c);

    std::cout << "Tridiagonal Matrix:" << std::endl;
    tridiagonalMatrix.print();


    // Create f vector
    std::vector<double> f(N + 2);
    f[0] = alpha;
    for (int i = 1; i <= N; ++i) {
        double x_i = i * h;
        f[i] = forcingTerm(x_i) * h * h;
    }
    f[N + 1] = beta;

    // Solve the system
    std::vector<double> solution = tridiagonalMatrix.solve(f);

    // Validate against the exact solution
    auto exactSolution = [&heatDiffusion](double x) {
        return sin(M_PI * x) / (M_PI * M_PI);
    };

    double errorNorm = 0.0;
    for (int i = 1; i <= N; ++i) {
        double x_i = i * h;
        errorNorm += pow(solution[i] - exactSolution(x_i), 2);
    }

    errorNorm = sqrt(errorNorm);

    std::cout << "Error Norm: " << errorNorm << std::endl;
    
    return 0;
}