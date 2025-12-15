#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Money {
private:
    std::vector<unsigned char> data;
    
    static const int TOTAL_SIZE = 13;
    static const int KOPEEK_PART = 2;
    
    void parseString(const std::string& value) {
        for (int i = 0; i < TOTAL_SIZE; i++) data[i] = 0;
        
        int rubles = 0, kopeeks = 0, pos = 0;
        
        while (pos < (int)value.size() && value[pos] != '.' && value[pos] != ',') {
            rubles = rubles * 10 + (value[pos] - '0');
            pos++;
        }
        
        pos++;
        if (pos < (int)value.size()) kopeeks = (value[pos] - '0') * 10;
        if (pos + 1 < (int)value.size()) kopeeks += value[pos + 1] - '0';
        
        data[0] = kopeeks % 10;
        data[1] = kopeeks / 10;
        
        for (int i = 2; rubles > 0; i++) {
            data[i] = rubles % 10;
            rubles /= 10;
        }
    }
    
    int compare(const Money& other) const {
        for (int i = TOTAL_SIZE - 1; i >= 0; i--) {
            if (data[i] > other.data[i]) return 1;
            if (data[i] < other.data[i]) return -1;
        }
        return 0;
    }

public:
    Money() : data(TOTAL_SIZE, 0) {}
    
    Money(const std::string& value) : data(TOTAL_SIZE, 0) {
        if (value.empty()) throw std::invalid_argument("empty string");
        parseString(value);
    }
    
    Money(const Money& other) : data(other.data) {}
    
    Money(Money&& other) noexcept : data(std::move(other.data)) {
        other.data = std::vector<unsigned char>(TOTAL_SIZE, 0);
    }
    
    ~Money() noexcept {}
    
    Money add(const Money& other) const {
        Money result;
        int carry = 0;
        
        for (int i = 0; i < TOTAL_SIZE; i++) {
            int sum = data[i] + other.data[i] + carry;
            result.data[i] = sum % 10;
            carry = sum / 10;
        }
        
        if (carry > 0) throw std::overflow_error("overflow");
        return result;
    }
    
    Money subtract(const Money& other) const {
        if (compare(other) < 0) throw std::invalid_argument("negative result");
        
        Money result;
        int borrow = 0;
        
        for (int i = 0; i < TOTAL_SIZE; i++) {
            int diff = data[i] - other.data[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.data[i] = diff;
        }
        
        return result;
    }
    
    bool isGreater(const Money& other) const {
        return compare(other) > 0;
    }
    
    bool isLess(const Money& other) const {
        return compare(other) < 0;
    }
    
    bool isEqual(const Money& other) const {
        return compare(other) == 0;
    }
    
    std::string toString() const {
        std::string result;
        int i = TOTAL_SIZE - 1;
        
        while (i > KOPEEK_PART && data[i] == 0) i--;
        for (; i >= 0; i--) {
            result += static_cast<char>(data[i] + '0');
            if (i == 1) result += '.';
        }
        
        return result;
    }
};

int main() {
    try {
        Money m1("1234.56");
        Money m2("1000.00");
        
        std::cout << m1.toString() << std::endl;
        std::cout << m2.toString() << std::endl;
        
        Money sum = m1.add(m2);
        std::cout << sum.toString() << std::endl;
        
        Money diff = m1.subtract(m2);
        std::cout << diff.toString() << std::endl;
        
        std::cout << m1.isGreater(m2) << std::endl;
        std::cout << m1.isLess(m2) << std::endl;
        std::cout << m1.isEqual(m1) << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
