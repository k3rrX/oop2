#include <iostream>
#include <string>
#include <vector>

class Money {
private:
    std::vector<unsigned char> digits;
    static const int SIZE = 13;
    
    void initFromString(const std::string& str) {
        for(int i = 0; i < SIZE; i++) digits[i] = 0;
        int rubles = 0, kopeeks = 0, pos = 0;
        
        while(pos < str.size() && str[pos] != '.' && str[pos] != ',') {
            rubles = rubles * 10 + (str[pos] - '0');
            pos++;
        }
        pos++;
        
        if(pos < str.size()) kopeeks = (str[pos] - '0') * 10;
        if(pos + 1 < str.size()) kopeeks += str[pos + 1] - '0';
        
        digits[0] = kopeeks % 10;
        digits[1] = kopeeks / 10;
        
        int idx = 2;
        while(rubles > 0) {
            digits[idx++] = rubles % 10;
            rubles /= 10;
        }
    }
    
    int compare(const Money& other) const {
        for(int i = SIZE - 1; i >= 0; i--) {
            if(digits[i] != other.digits[i]) {
                return (digits[i] > other.digits[i]) ? 1 : -1;
            }
        }
        return 0;
    }
    
public:
    Money() : digits(SIZE, 0) {}
    
    Money(const std::string& str) : digits(SIZE, 0) {
        initFromString(str);
    }
    
    Money(const Money& other) : digits(other.digits) {}
    
    Money add(const Money& other) const {
        Money result;
        int carry = 0;
        
        for(int i = 0; i < SIZE; i++) {
            int sum = digits[i] + other.digits[i] + carry;
            result.digits[i] = sum % 10;
            carry = sum / 10;
        }
        return result;
    }
    
    Money subtract(const Money& other) const {
        if(compare(other) < 0) {
            return other.subtract(*this);
        }
        
        Money result;
        int borrow = 0;
        
        for(int i = 0; i < SIZE; i++) {
            int diff = digits[i] - other.digits[i] - borrow;
            if(diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits[i] = diff;
        }
        return result;
    }
    
    bool equals(const Money& other) const {
        return compare(other) == 0;
    }
    
    bool greaterThan(const Money& other) const {
        return compare(other) > 0;
    }
    
    bool lessThan(const Money& other) const {
        return compare(other) < 0;
    }
    
    std::string toString() const {
        std::string result;
        bool leadingZero = true;
        
        for(int i = SIZE - 1; i >= 2; i--) {
            if(digits[i] != 0) leadingZero = false;
            if(!leadingZero || i == 2) {
                result += char(digits[i] + '0');
            }
        }
        
        if(result.empty()) result = "0";
        
        result += '.';
        result += char(digits[1] + '0');
        result += char(digits[0] + '0');
        
        return result;
    }
};

int main() {
    Money amount1("1234.56");
    Money amount2("1000.00");
    
    std::cout << "Amount 1: " << amount1.toString() << std::endl;
    std::cout << "Amount 2: " << amount2.toString() << std::endl;
    
    Money sum = amount1.add(amount2);
    std::cout << "Sum: " << sum.toString() << std::endl;
    
    Money difference = amount1.subtract(amount2);
    std::cout << "Difference: " << difference.toString() << std::endl;
    
    if(amount1.greaterThan(amount2)) {
        std::cout << amount1.toString() << " is greater than " 
                  << amount2.toString() << std::endl;
    }
    
    return 0;
}
