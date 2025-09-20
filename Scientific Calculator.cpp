#include <iostream>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

class BasicCalculator {
public:
    double add(const vector<double>& numbers) const {
        double sum = 0;
        for (double num : numbers) {
            sum += num;
        }
        return sum;
    }

    double subtract(const vector<double>& numbers) const {
        if (numbers.empty()) throw runtime_error("No numbers to subtract");
        double result = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            result -= numbers[i];
        }
        return result;
    }

    double multiply(const vector<double>& numbers) const {
        if (numbers.empty()) throw runtime_error("No numbers to multiply");
        double result = 1;
        for (double num : numbers) {
            result *= num;
        }
        return result;
    }

    double divide(const vector<double>& numbers) const {
        if (numbers.empty()) throw runtime_error("No numbers to divide");
        double result = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            if (numbers[i] == 0) throw runtime_error("Division by zero");
            result /= numbers[i];
        }
        return result;
    }
};

class ScientificCalculator {
public:
    double sin(double angle) const { return std::sin(angle); }
    double cos(double angle) const { return std::cos(angle); }
    double tan(double angle) const { return std::tan(angle); }

    double log(double value) const {
        if (value <= 0) throw runtime_error("Logarithm of non-positive value");
        return std::log(value); 
    }
    double log10(double value) const {
        if (value <= 0) throw runtime_error("Logarithm of non-positive value");
        return std::log10(value); 
    }

    double pow(double base, double exponent) const { return std::pow(base, exponent); }
    double sqrt(double value) const {
        if (value < 0) throw runtime_error("Square root of negative value");
        return std::sqrt(value); 
    }

    double exp(double value) const { return std::exp(value); }
    double abs(double value) const { return std::fabs(value); }
};

void displayOperationMenu() {
    cout << "\nScientific Calculator Operation Menu" << endl;
    cout << "1. Addition" << endl;
    cout << "2. Subtraction" << endl;
    cout << "3. Multiplication" << endl;
    cout << "4. Division" << endl;
    cout << "5. Sine" << endl;
    cout << "6. Cosine" << endl;
    cout << "7. Tangent" << endl;
    cout << "8. Logarithm (base e)" << endl;
    cout << "9. Logarithm (base 10)" << endl;
    cout << "10. Power" << endl;
    cout << "11. Square Root" << endl;
    cout << "12. Exponential" << endl;
    cout << "13. Absolute Value" << endl;
    cout << "14. Exit" << endl;
    cout << "Enter your choice: ";
}

vector<double> readValues() {
    vector<double> values;
    double value;
    cout << "Enter values (type 'done' to finish): ";
    while (cin >> value) {
        values.push_back(value);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return values;
}

void saveResult(const string& operation, const vector<double>& values, double result) {
    ofstream outFile("results.txt", ios_base::app);
    if (outFile.is_open()) {
        outFile << operation << " (";
        for (size_t i = 0; i < values.size(); ++i) {
            outFile << values[i];
            if (i != values.size() - 1) {
                outFile << ", ";
            }
        }
        outFile << "): " << result << endl;
        outFile.close();
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}

void performBasicOperation(BasicCalculator& basicCalc, int choice) {
    vector<double> values = readValues();
    double result;
    string operation;

    switch (choice) {
        case 1:
            result = basicCalc.add(values);
            operation = "Addition";
            break;
        case 2:
            result = basicCalc.subtract(values);
            operation = "Subtraction";
            break;
        case 3:
            result = basicCalc.multiply(values);
            operation = "Multiplication";
            break;
        case 4:
            result = basicCalc.divide(values);
            operation = "Division";
            break;
        default:
            throw invalid_argument("Invalid basic operation choice");
    }
    
    cout << "Result: " << result << endl;
    saveResult(operation, values, result);
}

void performScientificOperation(ScientificCalculator& sciCalc, int choice) {
    double num1, num2;
    double result;
    string operation;
    vector<double> values;

    switch (choice) {
        case 5:
            cout << "Enter angle in radians: ";
            cin >> num1;
            values.push_back(num1);
            result = sciCalc.sin(num1);
            operation = "Sine";
            break;
        case 6:
            cout << "Enter angle in radians: ";
            cin >> num1;
            values.push_back(num1);
            result = sciCalc.cos(num1);
            operation = "Cosine";
            break;
        case 7:
            cout << "Enter angle in radians: ";
            cin >> num1;
            values.push_back(num1);
            result = sciCalc.tan(num1);
            operation = "Tangent";
            break;
        case 8:
            cout << "Enter a number: ";
            cin >> num1;
            values.push_back(num1);
            result = sciCalc.log(num1);
            operation = "Logarithm (base e)";
            break;
        case 9:
            cout << "Enter a number: ";
            cin >> num1;
            values.push_back(num1);
            result = sciCalc.log10(num1);
            operation = "Logarithm (base 10)";
            break;
        case 10:
            cout << "Enter base and exponent: ";
            cin >> num1 >> num2;
            values.push_back(num1);
            values.push_back(num2);
            result = sciCalc.pow(num1, num2);
            operation = "Power";
            break;
        case 11:
            cout << "Enter a number: ";
            cin >> num1;
            values.push_back(num1);
            result = sciCalc.sqrt(num1);
            operation = "Square Root";
            break;
        case 12:
            cout << "Enter a number: ";
            cin >> num1;
            values.push_back(num1);
            result = sciCalc.exp(num1);
            operation = "Exponential";
            break;
        case 13:
            cout << "Enter a number: ";
            cin >> num1;
            values.push_back(num1);
            result = sciCalc.abs(num1);
            operation = "Absolute Value";
            break;
        default:
            throw invalid_argument("Invalid scientific operation choice");
    }

    cout << "Result: " << result << endl;
    saveResult(operation, values, result);
}

int main() {
    BasicCalculator basicCalc;
    ScientificCalculator sciCalc;
    int choice;

    do {
        displayOperationMenu();
        cin >> choice;

        try {
            if (choice >= 1 && choice <= 4) {
                performBasicOperation(basicCalc, choice);
            } else if (choice >= 5 && choice <= 13) {
                performScientificOperation(sciCalc, choice);
            } else if (choice != 14) {
                cout << "Invalid choice. Please try again." << endl;
            }
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 14);

    cout << "Exiting..." << endl;
    return 0;
}
