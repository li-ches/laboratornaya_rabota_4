package main

import (
	"fmt"
	"math/rand"
	"strconv"
	"strings"
	"time"
	"unicode"
)

// 1. Создание массива из n случайных вещественных чисел [-100, 100]
func createRandomArray(n int) []float64 {
	rand.Seed(time.Now().UnixNano())
	arr := make([]float64, n)
	for i := range arr {
		arr[i] = -100 + 200*rand.Float64()
	}
	return arr
}

// 2. Произведение отрицательных и сумма положительных до максимального элемента
func processArray(arr []float64) {
	if len(arr) == 0 {
		return
	}

	maxIndex := 0
	for i, v := range arr {
		if v > arr[maxIndex] {
			maxIndex = i
		}
	}

	product := 1.0
	sum := 0.0

	for i := 0; i < maxIndex; i++ {
		if arr[i] < 0 {
			product *= arr[i]
		} else if arr[i] > 0 {
			sum += arr[i]
		}
	}

	fmt.Printf("Произведение отрицательных до максимального: %.4f\n", product)
	fmt.Printf("Сумма положительных до максимального: %.4f\n", sum)
}

// 3. Смена регистра строки
func reverseCase(s string) string {
	result := []rune(s)
	for i, c := range result {
		if unicode.IsUpper(c) {
			result[i] = unicode.ToLower(c)
		} else if unicode.IsLower(c) {
			result[i] = unicode.ToUpper(c)
		}
	}
	return string(result)
}

// 4. Количество элементов больше соседних
func countGreaterThanNeighbors(arr []int) int {
	count := 0
	n := len(arr)

	if n < 2 {
		return 0
	}

	for i := 1; i < n-1; i++ {
		if arr[i] > arr[i-1] && arr[i] > arr[i+1] {
			count++
		}
	}

	// Проверка краевых элементов
	if n > 1 {
		if arr[0] > arr[1] {
			count++
		}
		if arr[n-1] > arr[n-2] {
			count++
		}
	}

	return count
}

// 5.1 Перемешивание цифр в числе
func shuffleDigits(num int) int {
	if num == 0 {
		return 0
	}

	negative := num < 0
	if negative {
		num = -num
	}

	s := strconv.Itoa(num)
	runes := []rune(s)
	rand.Shuffle(len(runes), func(i, j int) {
		runes[i], runes[j] = runes[j], runes[i]
	})

	result, _ := strconv.Atoi(string(runes))
	if negative {
		return -result
	}
	return result
}

// 5.2 Обработка целочисленного массива
func processIntArray(arr []int) {
	// Исходная сумма
	originalSum := 0
	for _, v := range arr {
		originalSum += v
	}
	fmt.Printf("Исходная сумма: %d\n", originalSum)

	// Перемешиваем цифры
	for i := range arr {
		arr[i] = shuffleDigits(arr[i])
	}

	// Сортировка
	for i := 0; i < len(arr)-1; i++ {
		for j := 0; j < len(arr)-i-1; j++ {
			if arr[j] > arr[j+1] {
				arr[j], arr[j+1] = arr[j+1], arr[j]
			}
		}
	}

	// Новая сумма
	newSum := 0
	for _, v := range arr {
		newSum += v
	}
	fmt.Printf("Новая сумма: %d\n", newSum)

	// Сравнение
	if originalSum == newSum {
		fmt.Println("Суммы равны")
	} else {
		fmt.Printf("Суммы различны, разница: %d\n", originalSum-newSum)
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())

	// Задание 1
	n := 15
	arr := createRandomArray(n)
	fmt.Printf("Сгенерированный массив (%d элементов):\n", n)
	fmt.Println(strings.Trim(fmt.Sprint(arr), "[]"))
	fmt.Println()

	// Задание 2
	processArray(arr)
	fmt.Println()

	// Задание 3
	testStr := "Hello World! 123"
	fmt.Printf("Исходная строка: %s\n", testStr)
	fmt.Printf("С обратным регистром: %s\n\n", reverseCase(testStr))

	// Задание 4
	intArr := []int{1, 3, 2, 5, 4, 7, 6, 9, 8}
	fmt.Printf("Количество элементов больше соседей: %d\n\n", countGreaterThanNeighbors(intArr))

	// Задание 5
	randomIntArr := make([]int, 10)
	for i := range randomIntArr {
		randomIntArr[i] = rand.Intn(2001) - 1000 // [-1000, 1000]
	}

	fmt.Println("Исходный массив целых чисел:")
	fmt.Println(strings.Trim(fmt.Sprint(randomIntArr), "[]"))
	processIntArray(randomIntArr)

	fmt.Println("Массив после преобразований:")
	fmt.Println(strings.Trim(fmt.Sprint(randomIntArr), "[]"))
}
