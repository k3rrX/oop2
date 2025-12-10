#include <iostream>
#include <string>

class Money {
    char d[13];
public:
    Money() { for(int i=0;i<13;i++) d[i]=0; }
    
    Money(std::string s) {
        for(int i=0;i<13;i++) d[i]=0;
        int r=0,k=0,i=0;
        
        while(i<s.size() && s[i]!='.' && s[i]!=',')
            if(s[i]>='0' && s[i]<='9')
                r = r*10 + (s[i++]-'0');
        
        i++; 
        
        if(i<s.size()) k = (s[i]-'0')*10;
        if(i+1<s.size()) k += s[i+1]-'0';
        
        d[0]=k%10; d[1]=k/10;
        for(int j=2;r>0 && j<13;r/=10)
            d[j++] = r%10;
    }
    
    void show() {
        int i=12;
        while(i>=2 && d[i]==0 && i>2) i--;
        for(;i>=2;i--) std::cout<<(char)(d[i]+'0');
        std::cout<<'.'<<(char)(d[1]+'0')<<(char)(d[0]+'0');
    }
};

int main() {
    Money m("1234.56");
    std::cout << "Сумма: ";
    m.show();
    return 0;
}
