#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <string>
#include <cctype>

using namespace std;

// Функция для генерации случайного вещественного числа в диапазоне [min, max]
double random_double(double min, double max) {
    static mt19937_64 gen(time(nullptr));
    uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

// Функция для генерации случайного целого числа в диапазоне [min, max]
int random_int(int min, int max) {
    static mt19937_64 gen(time(nullptr));
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// Задание 1: Создание и инициализация массива
vector<double> create_array(int n) {
    vector<double> arr(n);
    for (auto& x : arr) {
        x = random_double(-100, 100);
    }
    return arr;
}

// Задание 2: Произведение отрицательных и сумма положительных элементов до максимального
void process_array(const vector<double>& arr) {
    if (arr.empty()) return;
    
    auto max_it = max_element(arr.begin(), arr.end());
    int max_pos = distance(arr.begin(), max_it);
    
    double product = 1.0;
    double sum = 0.0;
    
    for (int i = 0; i < max_pos; ++i) {
        if (arr[i] < 0) {
            product *= arr[i];
        } else if (arr[i] > 0) {
            sum += arr[i];
        }
    }
    
    cout << "Произведение отрицательных элементов до максимального: " << product << endl;
    cout << "Сумма положительных элементов до максимального: " << sum << endl;
}

// Задание 3: Смена регистра строки
string reverse_case(const string& s) {
    string result;
    for (char c : s) {
        if (isupper(c)) {
            result += tolower(c);
        } else if (islower(c)) {
            result += toupper(c);
        } else {
            result += c;
        }
    }
    return result;
}

// Задание 4: Количество элементов больше соседних
int count_greater_than_neighbors(const vector<int>& arr) {
    int count = 0;
    int n = arr.size();
    
    if (n < 2) return 0;
    
    for (int i = 1; i < n - 1; ++i) {
        if (arr[i] > arr[i-1] && arr[i] > arr[i+1]) {
            ++count;
        }
    }
    
    // Проверяем краевые элементы
    if (n > 1) {
        if (arr[0] > arr[1]) ++count;
        if (arr[n-1] > arr[n-2]) ++count;
    }
    
    return count;
}

// Функция для перестановки цифр в числе
int shuffle_digits(int num) {
    if (num == 0) return 0;
    
    bool negative = num < 0;
    num = abs(num);
    
    string s = to_string(num);
    shuffle(s.begin(), s.end(), mt19937_64(random_device{}()));
    
    int result = stoi(s);
    return negative ? -result : result;
}

// Задание 5: Обработка целочисленного массива
void process_int_array(vector<int>& arr) {
    // Вычисляем исходную сумму
    int original_sum = accumulate(arr.begin(), arr.end(), 0);
    cout << "Исходная сумма элементов: " << original_sum << endl;
    
    // Перемешиваем цифры в каждом элементе
    for (auto& x : arr) {
        x = shuffle_digits(x);
    }
    
    // Сортируем массив
    sort(arr.begin(), arr.end());
    
    // Вычисляем новую сумму
    int new_sum = accumulate(arr.begin(), arr.end(), 0);
    cout << "Сумма после преобразований: " << new_sum << endl;
    
    // Сравниваем суммы
    if (original_sum == new_sum) {
        cout << "Суммы равны" << endl;
    } else {
        cout << "Суммы различны: разница = " << abs(original_sum - new_sum) << endl;
    }
}

int main() {
    // Задание 1
    const int n = 15;
    vector<double> arr = create_array(n);
    
    cout << "Сгенерированный массив (" << n << " элементов):" << endl;
    for (auto x : arr) cout << x << " ";
    cout << endl << endl;
    
    // Задание 2
    process_array(arr);
    cout << endl;
    
    // Задание 3
    string test_str = "Hello World! 123";
    cout << "Исходная строка: " << test_str << endl;
    cout << "С обратным регистром: " << reverse_case(test_str) << endl << endl;
    
    // Задание 4
    vector<int> int_arr = {1, 3, 2, 5, 4, 7, 6, 9, 8};
    cout << "Количество элементов больше соседей: " 
         << count_greater_than_neighbors(int_arr) << endl << endl;
    
    // Задание 5
    vector<int> random_int_arr(10);
    generate(random_int_arr.begin(), random_int_arr.end(), []() { return random_int(-1000, 1000); });
    
    cout << "Исходный массив целых чисел:" << endl;
    for (auto x : random_int_arr) cout << x << " ";
    cout << endl;
    
    process_int_array(random_int_arr);
    
    cout << "Массив после преобразований:" << endl;
    for (auto x : random_int_arr) cout << x << " ";
    cout << endl;
    
    return 0;
}
