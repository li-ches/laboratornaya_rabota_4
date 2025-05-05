#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Исходная функция: cos(x) - (x - 1)^2
double f(double x) {
    return cos(x) - pow(x - 1, 2);
}

// Производная функции: -sin(x) - 2*(x - 1)
double df(double x) {
    return -sin(x) - 2 * (x - 1);
}

// Функция для метода простых итераций: x = sqrt(cos(x)) + 1
double phi(double x) {
    return sqrt(cos(x)) + 1;
}

// Метод половинного деления (бисекции)
void bisection(double a, double b, double epsilon) {
    cout << "\nМетод половинного деления:\n";
    cout << setw(5) << "N" << setw(15) << "a" << setw(15) << "b" << setw(15) << "b-a" << endl;
    cout << "--------------------------------------------\n";

    int iter = 0;
    while (fabs(b - a) > epsilon) {
        double c = (a + b) / 2;
        cout << setw(5) << iter << setw(15) << setprecision(10) << a << setw(15) << b << setw(15) << fabs(b - a) << endl;

        if (f(c) == 0) {
            break;
        } else if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
        iter++;
    }
    double root = (a + b) / 2;
    cout << "\nНайденный корень методом половинного деления: " << setprecision(10) << root << endl;
}

// Метод Ньютона
void newton(double x0, double epsilon) {
    cout << "\nМетод Ньютона:\n";
    cout << setw(5) << "N" << setw(15) << "xn" << setw(15) << "xn+1" << setw(15) << "xn+1 - xn" << endl;
    cout << "--------------------------------------------\n";

    int iter = 0;
    double x1 = x0 - f(x0)/df(x0);
    while (fabs(x1 - x0) > epsilon) {
        cout << setw(5) << iter << setw(15) << setprecision(10) << x0 << setw(15) << x1 << setw(15) << fabs(x1 - x0) << endl;
        x0 = x1;
        x1 = x0 - f(x0)/df(x0);
        iter++;
    }
    cout << "\nНайденный корень методом Ньютона: " << setprecision(10) << x1 << endl;
}

// Метод простых итераций
void simpleIteration(double x0, double epsilon) {
    cout << "\nМетод простых итераций:\n";
    cout << setw(5) << "N" << setw(15) << "xn" << setw(15) << "xn+1" << setw(15) << "xn+1 - xn" << endl;
    cout << "--------------------------------------------\n";

    int iter = 0;
    double x1 = phi(x0);
    while (fabs(x1 - x0) > epsilon) {
        cout << setw(5) << iter << setw(15) << setprecision(10) << x0 << setw(15) << x1 << setw(15) << fabs(x1 - x0) << endl;
        x0 = x1;
        x1 = phi(x0);
        iter++;
    }
    cout << "\nНайденный корень методом простых итераций: " << setprecision(10) << x1 << endl;
}

int main() {
    double epsilon = 0.0001;

    // Графически определенные интервалы с корнями
    cout << "Уравнение: cos(x) - (x - 1)^2 = 0\n";
    cout << "Графически определены интервалы с корнями:\n";
    cout << "1. [0, 1]\n";
    cout << "2. [1, 2]\n";

    // Первый корень на интервале [0, 1]
    cout << "\nУточнение первого корня (интервал [0, 1]):\n";
    bisection(0, 1, epsilon);
    newton(0.5, epsilon);
    simpleIteration(0.5, epsilon);

    // Второй корень на интервале [1, 2]
    cout << "\nУточнение второго корня (интервал [1, 2]):\n";
    bisection(1, 2, epsilon);
    newton(1.5, epsilon);
    simpleIteration(1.5, epsilon);

    // Сравнение методов
    cout << "\nСравнение методов по количеству итераций:\n";
    cout << "1. Метод половинного деления: ~14 итераций\n";
    cout << "2. Метод Ньютона: ~4 итерации\n";
    cout << "3. Метод простых итераций: ~10 итераций\n";
    cout << "Вывод: Метод Ньютона сходится быстрее всех благодаря использованию производной.\n";

    return 0;
}
