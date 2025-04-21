#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }

    int multiply(int a, int b) {
        return a * b;
    }
};

;

int main() {
// Create object of Calculator class
Calculator calc;

// Call add function
int sum = calc.add(5, 7);

// Call multiply function
int product = calc.multiply(3, 4);

// Output results
cout << "Sum: " << sum << endl;
cout << "Product: " << product << endl;

    return 0;
}
