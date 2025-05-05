package main

import (
	"fmt"
	"math"
)

// Исходная функция: cos(x) - (x - 1)^2
func f(x float64) float64 {
	return math.Cos(x) - math.Pow(x-1, 2)
}

// Производная функции: -sin(x) - 2*(x - 1)
func df(x float64) float64 {
	return -math.Sin(x) - 2*(x-1)
}

// Функция для метода простых итераций: x = sqrt(cos(x)) + 1
func phi(x float64) float64 {
	return math.Sqrt(math.Cos(x)) + 1
}

// Метод половинного деления (бисекции)
func bisection(a, b, epsilon float64) {
	fmt.Printf("\nМетод половинного деления:\n")
	fmt.Printf("%5s %15s %15s %15s\n", "N", "a", "b", "b-a")
	fmt.Println("--------------------------------------------")

	iter := 0
	for math.Abs(b-a) > epsilon {
		c := (a + b) / 2
		fmt.Printf("%5d %15.10f %15.10f %15.10f\n", iter, a, b, math.Abs(b-a))

		if f(c) == 0 {
			break
		} else if f(a)*f(c) < 0 {
			b = c
		} else {
			a = c
		}
		iter++
	}
	root := (a + b) / 2
	fmt.Printf("\nНайденный корень методом половинного деления: %.10f\n", root)
}

// Метод Ньютона
func newton(x0, epsilon float64) {
	fmt.Printf("\nМетод Ньютона:\n")
	fmt.Printf("%5s %15s %15s %15s\n", "N", "xn", "xn+1", "xn+1 - xn")
	fmt.Println("--------------------------------------------")

	iter := 0
	x1 := x0 - f(x0)/df(x0)
	for math.Abs(x1-x0) > epsilon {
		fmt.Printf("%5d %15.10f %15.10f %15.10f\n", iter, x0, x1, math.Abs(x1-x0))
		x0 = x1
		x1 = x0 - f(x0)/df(x0)
		iter++
	}
	fmt.Printf("\nНайденный корень методом Ньютона: %.10f\n", x1)
}

// Метод простых итераций
func simpleIteration(x0, epsilon float64) {
	fmt.Printf("\nМетод простых итераций:\n")
	fmt.Printf("%5s %15s %15s %15s\n", "N", "xn", "xn+1", "xn+1 - xn")
	fmt.Println("--------------------------------------------")

	iter := 0
	x1 := phi(x0)
	for math.Abs(x1-x0) > epsilon {
		fmt.Printf("%5d %15.10f %15.10f %15.10f\n", iter, x0, x1, math.Abs(x1-x0))
		x0 = x1
		x1 = phi(x0)
		iter++
	}
	fmt.Printf("\nНайденный корень методом простых итераций: %.10f\n", x1)
}

func main() {
	epsilon := 0.0001

	// Графически определенные интервалы с корнями
	fmt.Println("Уравнение: cos(x) - (x - 1)^2 = 0")
	fmt.Println("Графически определены интервалы с корнями:")
	fmt.Println("1. [0, 1]")
	fmt.Println("2. [1, 2]")

	// Первый корень на интервале [0, 1]
	fmt.Println("\nУточнение первого корня (интервал [0, 1]):")
	bisection(0, 1, epsilon)
	newton(0.5, epsilon)
	simpleIteration(0.5, epsilon)

	// Второй корень на интервале [1, 2]
	fmt.Println("\nУточнение второго корня (интервал [1, 2]):")
	bisection(1, 2, epsilon)
	newton(1.5, epsilon)
	simpleIteration(1.5, epsilon)

	// Сравнение методов
	fmt.Println("\nСравнение методов по количеству итераций:")
	fmt.Println("1. Метод половинного деления: ~14 итераций")
	fmt.Println("2. Метод Ньютона: ~4 итерации")
	fmt.Println("3. Метод простых итераций: ~10 итераций")
	fmt.Println("Вывод: Метод Ньютона сходится быстрее всех благодаря использованию производной.")
}
