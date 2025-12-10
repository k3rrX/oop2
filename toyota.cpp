#include <iostream>
#include <string>

class Money {
private:
    char digits[13];

public:
    Money() {
        for (int i = 0; i < 13; i++) digits[i] = 0;
    }

    Money(const std::string& str) {
        for (int i = 0; i < 13; i++) digits[i] = 0;

        // Простая реализация для формата "1234.56"
        int rub = 0, kop = 0;

        // Вручную парсим строку
        int i = 0;
        while (i < str.length() && str[i] != '.' && str[i] != ',') {
            if (str[i] >= '0' && str[i] <= '9') {
                rub = rub * 10 + (str[i] - '0');
            }
            i++;
        }

        i++; // Пропускаем разделитель

        // Читаем копейки
        if (i < str.length()) {
            kop = (str[i] - '0') * 10;
            i++;
        }
        if (i < str.length()) {
            kop += (str[i] - '0');
        }

        // Заполняем копейки
        digits[0] = kop % 10;
        digits[1] = kop / 10;

        // Заполняем рубли
        int index = 2;
        while (rub > 0 && index < 13) {
            digits[index++] = rub % 10;
            rub /= 10;
        }
    }

    void print() const {
        // Вывод рублей
        bool started = false;
        for (int i = 12; i >= 2; i--) {
            if (digits[i] != 0 || started || i == 2) {
                std::cout << char(digits[i] + '0');
                started = true;
            }
        }
        if (!started) std::cout << "0";

        // Вывод копейки
        std::cout << "." << char(digits[1] + '0') << char(digits[0] + '0');
    }
};

int main() {
    Money m("1234.56");
    std::cout << "Сумма: ";
    m.print();
    std::cout << std::endl;
    return 0;
}