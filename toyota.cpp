#include <iostream>
#include <string>
#include <vector>

class Money {
private:
    std::vector<unsigned char> numbers;
    
    static const int TOTAL_DIGITS = 13;
    static const int KOPEEK_DIGITS = 2;
    
    void setup(const std::string& value) {
        numbers.assign(TOTAL_DIGITS, 0);
        
        int point = value.find('.');
        if (point == std::string::npos) point = value.find(',');
        
        long rubles = 0;
        for (int i = 0; i < (point != std::string::npos ? point : (int)value.length()); i++) {
            rubles = rubles * 10 + (value[i] - '0');
        }
        
        int kopeeks = 0;
        if (point != std::string::npos && point + 1 < value.length()) {
            kopeeks = (value[point + 1] - '0') * 10;
        }
        if (point != std::string::npos && point + 2 < value.length()) {
            kopeeks += value[point + 2] - '0';
        }
        
        numbers[0] = kopeeks % 10;
        numbers[1] = kopeeks / 10;
        
        int pos = 2;
        while (rubles > 0) {
            numbers[pos++] = rubles % 10;
            rubles /= 10;
        }
    }
    
    int checkDifference(const Money& other) const {
        for (int i = TOTAL_DIGITS - 1; i >= 0; i--) {
            if (numbers[i] != other.numbers[i]) {
                return numbers[i] - other.numbers[i];
            }
        }
        return 0;
    }

public:
    Money() : numbers(TOTAL_DIGITS, 0) {}
    
    Money(const std::string& value) {
        setup(value);
    }
    
    Money(const Money& source) : numbers(source.numbers) {}
    
    Money combine(const Money& other) const {
        Money result;
        int extra = 0;
        
        for (int i = 0; i < TOTAL_DIGITS; i++) {
            int total = numbers[i] + other.numbers[i] + extra;
            result.numbers[i] = total % 10;
            extra = total / 10;
        }
        
        return result;
    }
    
    Money takeAway(const Money& other) const {
        Money result;
        int need = 0;
        
        for (int i = 0; i < TOTAL_DIGITS; i++) {
            int current = numbers[i] - other.numbers[i] - need;
            if (current < 0) {
                current += 10;
                need = 1;
            } else {
                need = 0;
            }
            result.numbers[i] = current;
        }
        
        return result;
    }
    
    bool isSame(const Money& other) const {
        return checkDifference(other) == 0;
    }
    
    bool isBigger(const Money& other) const {
        return checkDifference(other) > 0;
    }
    
    bool isSmaller(const Money& other) const {
        return checkDifference(other) < 0;
    }
    
    std::string display() const {
        std::string text;
        
        bool foundNonZero = false;
        for (int i = TOTAL_DIGITS - 1; i >= KOPEEK_DIGITS; i--) {
            if (numbers[i] != 0) foundNonZero = true;
            if (foundNonZero || i == KOPEEK_DIGITS) {
                text.push_back('0' + numbers[i]);
            }
        }
        
        text.push_back('.');
        text.push_back('0' + numbers[1]);
        text.push_back('0' + numbers[0]);
        
        return text;
    }
};

int main() {
    Money first("1500.75");
    Money second("750.25");
    
    std::cout << "First amount: " << first.display() << std::endl;
    std::cout << "Second amount: " << second.display() << std::endl;
    
    Money total = first.combine(second);
    std::cout << "Total: " << total.display() << std::endl;
    
    Money remaining = first.takeAway(second);
    std::cout << "Remaining: " << remaining.display() << std::endl;
    
    if (first.isBigger(second)) {
        std::cout << first.display() << " is bigger than " << second.display() << std::endl;
    }
    
    return 0;
}
