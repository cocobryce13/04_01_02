#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

class Address {
private:
    std::string city_;
    std::string street_;
    int number_home_;
    int number_flat_;

public:
    Address() = default;

    Address(const std::string& city, const std::string& street, int number_home, int number_flat)
        : city_(city), street_(street), number_home_(number_home), number_flat_(number_flat) {
    }

    std::string GetOutputAddress() const {
        return city_ + ", " + street_ + ", " + std::to_string(number_home_) + ", " + std::to_string(number_flat_);
    }

    const std::string& GetCity() const {
        return city_;
    }
};

void ReadFile(std::ifstream& in, Address* ad, int number) {
    std::string s;
    for (int i = 0; i < number; ++i) {
        std::getline(in, s);
        std::string city = s;
        std::getline(in, s);
        std::string street = s;
        std::getline(in, s);
        int number_home = std::stoi(s);
        std::getline(in, s);
        int number_flat = std::stoi(s);
        ad[i] = Address(city, street, number_home, number_flat);
    }
}

void BubbleSortAddresses(Address* ad, int number) {
    for (int i = 0; i < number - 1; ++i) {
        for (int j = 0; j < number - i - 1; ++j) {
            if (ad[j].GetCity() > ad[j + 1].GetCity()) {
                Address temp = ad[j];
                ad[j] = ad[j + 1];
                ad[j + 1] = temp;
            }
        }
    }
}

void WriteAddressesToFile(std::ofstream& out, Address* ad, int number) {
    out << number << std::endl;
    for (int i = 0; i < number; ++i) {
        out << ad[i].GetOutputAddress() << std::endl;
    }
}

void PrintAddresses(Address* ad, int number) {
    std::cout << number << std::endl;
    for (int i = 0; i < number; ++i) {
        std::cout << ad[i].GetOutputAddress() << std::endl;
    }
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");

    std::ifstream in("in.txt");
    if (!in.is_open()) {
        std::cout << "File not open!" << std::endl;
        return 1;
    }

    std::ofstream out("out.txt");
    if (!out.is_open()) {
        std::cout << "File not open!" << std::endl;
        return 1;
    }

    int number;
    in >> number;
    in.ignore();

    Address* ad = new Address[number];
    ReadFile(in, ad, number);

    BubbleSortAddresses(ad, number);

    PrintAddresses(ad, number);

    WriteAddressesToFile(out, ad, number);

    delete[] ad;
    in.close();
    out.close();

    return 0;
}
