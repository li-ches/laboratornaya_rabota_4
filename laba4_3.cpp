#include <iostream>
#include <cstdint>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class Xorshift {
private:
    uint32_t state;

public:
    Xorshift(uint32_t seed = 0) {
        state = (seed != 0) ? seed : static_cast<uint32_t>(time(nullptr));
        // Прогрев генератора
        for (int i = 0; i < 10; i++) next();
    }

    uint32_t next() {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state;
    }

    uint32_t next(uint32_t max) {
        return next() % max;
    }

    int32_t next(int32_t min, int32_t max) {
        return min + static_cast<int32_t>(next()) % (max - min + 1);
    }

    double next_double() {
        return static_cast<double>(next()) / static_cast<double>(UINT32_MAX);
    }
};

void demonstrate_basic_usage() {
    Xorshift rng;
    cout << "\n1. Basic Xorshift output (10 numbers):\n";
    for (int i = 0; i < 10; i++) {
        cout << rng.next() << " ";
    }
}

void demonstrate_range_usage() {
    Xorshift rng(12345); // Фиксированный seed для воспроизводимости
    cout << "\n\n2. Numbers in range [0, 100):\n";
    for (int i = 0; i < 10; i++) {
        cout << rng.next(100) << " ";
    }
}

void demonstrate_signed_range() {
    Xorshift rng;
    cout << "\n\n3. Numbers in range [-50, 50]:\n";
    for (int i = 0; i < 10; i++) {
        cout << rng.next(-50, 50) << " ";
    }
}

void demonstrate_double_usage() {
    Xorshift rng;
    cout << "\n\n4. Double numbers in [0.0, 1.0):\n";
    for (int i = 0; i < 5; i++) {
        cout << rng.next_double() << " ";
    }
}

void demonstrate_shuffle() {
    Xorshift rng;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "\n\n5. Vector before shuffle:\n";
    for (int n : numbers) cout << n << " ";
    
    // Фишер-Йетс shuffle
    for (size_t i = numbers.size() - 1; i > 0; i--) {
        size_t j = rng.next(i + 1);
        swap(numbers[i], numbers[j]);
    }
    
    cout << "\nAfter shuffle:\n";
    for (int n : numbers) cout << n << " ";
}

int main() {
    cout << "Xorshift Random Number Generator Demonstration\n";
    cout << "--------------------------------------------\n";
    
    demonstrate_basic_usage();
    demonstrate_range_usage();
    demonstrate_signed_range();
    demonstrate_double_usage();
    demonstrate_shuffle();
    
    cout << "\n\nDemonstration complete.\n";
    return 0;
}
