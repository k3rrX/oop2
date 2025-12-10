#include <iostream>
#include <string>

struct Money {
    char d[13];
    Money(std::string s="0") {
        for(int i=0;i<13;i++) d[i]=0;
        int r=0,k=0,p=0;
        while(p<s.size() && s[p]!='.' && s[p]!=',')
            r = r*10 + s[p++]-'0';
        p++;
        if(p<s.size()) k = (s[p]-'0')*10;
        if(p+1<s.size()) k += s[p+1]-'0';
        d[0]=k%10; d[1]=k/10;
        for(int i=2;r;r/=10) d[i++]=r%10;
    }
    void print() {
        int i=12;
        while(i>2 && !d[i]) i--;
        for(;i>=0;i--)
            std::cout << (i==1?'.':'\0') << (char)(d[i]+'0');
    }
};

int main() {
    Money m("1234.56");
    m.print();
}
