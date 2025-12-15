#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Money {
private:
    std::vector<unsigned char> data; // 13 цифр
    
    void parse(const std::string& str) {
        for (int i=0;i<13;i++) data[i]=0;
        int rub=0,kop=0,p=0;
        while(p<str.size() && str[p]!='.' && str[p]!=',') 
            rub = rub*10 + str[p++]-'0';
        p++;
        if(p<str.size()) kop = (str[p]-'0')*10;
        if(p+1<str.size()) kop += str[p+1]-'0';
        data[0]=kop%10; data[1]=kop/10;
        for(int i=2;rub;rub/=10) data[i++]=rub%10;
    }
    
    int cmp(const Money& other) const {
        for(int i=12;i>=0;i--) {
            if(data[i]!=other.data[i]) 
                return data[i]-other.data[i];
        }
        return 0;
    }
    
public:
    Money() : data(13,0) {}
    
    Money(const std::string& str) : data(13,0) {
        if(str.empty()) throw std::invalid_argument("empty");
        parse(str);
    }
    
    Money(const Money& other) : data(other.data) {}
    
    Money(Money&& other) noexcept : data(std::move(other.data)) {
        other.data = std::vector<unsigned char>(13,0);
    }
    
    ~Money() noexcept {}
    
    Money add(const Money& other) const {
        Money result;
        int carry=0;
        for(int i=0;i<13;i++) {
            int sum = data[i]+other.data[i]+carry;
            result.data[i] = sum%10;
            carry = sum/10;
        }
        if(carry) throw std::overflow_error("overflow");
        return result;
    }
    
    Money subtract(const Money& other) const {
        if(lessThan(other)) throw std::invalid_argument("negative result");
        Money result;
        int borrow=0;
        for(int i=0;i<13;i++) {
            int diff = data[i]-other.data[i]-borrow;
            if(diff<0) { diff+=10; borrow=1; }
            else borrow=0;
            result.data[i]=diff;
        }
        return result;
    }
    
    bool equals(const Money& other) const { return cmp(other)==0; }
    bool greaterThan(const Money& other) const { return cmp(other)>0; }
    bool lessThan(const Money& other) const { return cmp(other)<0; }
    
    std::string toString() const {
        std::string s;
        int i=12;
        while(i>2 && !data[i]) i--;
        for(;i>=0;i--) {
            s += (char)(data[i]+'0');
            if(i==1) s += '.';
        }
        return s;
    }
};

int main() {
    try {
        Money m1("1234.56"), m2("1000.00");
        std::cout << "m1=" << m1.toString() 
                  << " m2=" << m2.toString() << "\n";
        std::cout << "sum=" << m1.add(m2).toString() << "\n";
        std::cout << "diff=" << m1.subtract(m2).toString() << "\n";
        std::cout << "m1>m2? " << (m1.greaterThan(m2)?"true":"false") << "\n";
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
