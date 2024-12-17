#ifndef ROUNDEDDOUBLE_H
#define ROUNDEDDOUBLE_H
//#include <cstdint>
#include <stdint.h>

#include "qobject.h"
#include <cmath>
#include <stdexcept>

#include <iostream>
#include <sstream>
#include <string>
//-------------------------------------------------------------------
extern int peredacha_decimalPlaces;
//-------------------------------------------------------------------
class RoundedDouble {
private:
    double value;  // Само значение типа double
    int decimalPlaces;  // Количество знаков после запятой
public:
    // Конструктор, который принимает значение и округляет его
    RoundedDouble(double val, int decimalPlaces = peredacha_decimalPlaces=
   // 4
  //  8
     //             2
              //    3
            //      5
                 // 6
                  7
                  ) // NOTE: округление к 8 цифрам после запятой
        : value(roundToDecimal(val, decimalPlaces)) {}
 //-------------------------------------------------------------------
 //int   peredacha_decimalPlaces=decimalPlaces;
//-------------------------------------------------------------------
    // Метод для получения строкового представления RoundedDouble
    std::string toString() const {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
#//-----------------------------------------------------------------------------
            // Метод для округления до заданного количества знаков
    double roundToDecimal(double val, int decimalPlaces) const {
        double scale = std::pow(10.0, decimalPlaces);
        return std::round(val * scale) / scale;
    }
//-------------------------------------------------------------------
    // Конструктор по умолчанию
    RoundedDouble() : value(0.0) {}

    // Конструктор с параметром
  //  RoundedDouble(double val) : value(val) {}

    // Метод для округления к ближайшему целому числу
    double roundNearest() const {
        return std::round(value);
    }

    // Метод для округления вниз (к ближайшему целому снизу)
    double roundDown() const {
        return std::floor(value);
    }

    // Метод для округления вверх (к ближайшему целому сверху)
    double roundUp() const {
        return std::ceil(value);
    }

    // Округление до заданного числа знаков после запятой
    double roundToDecimal(int decimalPlaces=
  //  8
   // 4
   //                       2
                         // 3
                          //5
                         // 6
 7
    ) const { // NOTE: явное округление к 8 цифрам после запятой
    //decimalPlaces=8;
        double scale = std::pow(10.0, decimalPlaces);
        return std::round(value * scale) / scale;
    }

    // Перегрузка оператора приведения к типу double
    operator double() const {
        return value;
    }

    // Перегрузка оператора присваивания для удобного использования
    RoundedDouble& operator=(double val) {
        value = val;
        return *this;
    }

    // Перегрузка операторов арифметики для удобного использования
    RoundedDouble operator+(const RoundedDouble& other) const {
        return RoundedDouble(value + other.value);
    }

    RoundedDouble operator-(const RoundedDouble& other) const {
        return RoundedDouble(value - other.value);
    }

    RoundedDouble operator*(const RoundedDouble& other) const {
        return RoundedDouble(value * other.value);
    }

    RoundedDouble operator/(const RoundedDouble& other) const {
        return RoundedDouble(value / other.value);
    }

    // Метод для получения значения
    double getValue() const {
        return value;
    }

    // Метод для задания значения
    void setValue(double val) {
        value = val;
    }
//-------------------------------------------------------------------
// Перегрузка оператора деления для деления на int
    RoundedDouble operator/(int other) const {
        if (other == 0) {
            throw std::runtime_error("Division by zero!");
        }
        return RoundedDouble(value / static_cast<double>(other));
    }

    // Перегрузка оператора деления для деления на double
    // RoundedDouble operator/(double other) const {
    //     if (other == 0.0) {
    //         throw std::runtime_error("Division by zero!");
    //     }
    //     return RoundedDouble(value / other);
    // }


//-------------------------------------------------------------------    
    // Перегрузка оператора += для другого RoundedDouble
    RoundedDouble& operator+=(const RoundedDouble& other) {
        this->value += other.value;
        return *this;
    }

//-------------------------------------------------------------------


    // Перегрузка оператора * для int
    RoundedDouble operator*(int other) const {
        return RoundedDouble(this->value * other);
    }

    // Перегрузка оператора * для обратного порядка: int * RoundedDouble
    friend RoundedDouble operator*(int lhs, const RoundedDouble& rhs) {
        return RoundedDouble(lhs * rhs.value);
    }
//-------------------------------------------------------------------
    // Перегрузка оператора *= для другого RoundedDouble
    RoundedDouble& operator*=(const RoundedDouble& other) {
        this->value *= other.value;
        return *this;
    }

    // Перегрузка оператора *= для int
    RoundedDouble& operator*=(int other) {
        this->value *= other;
        return *this;
    }
//-------------------------------------------------------------------

    // Перегрузка оператора ввода (чтение из потока)
    friend QDataStream& operator>>(QDataStream& in, RoundedDouble& rd) {
        in >> rd.value;
        return in;
    }

    // Перегрузка оператора вывода (запись в поток)
    friend QDataStream& operator<<(QDataStream& out, const RoundedDouble& rd) {
        out << rd.value;
        return out;
    }

    // Перегрузка оператора <<
//    QDataStream& operator<<(QDataStream& out, const RoundedDouble& rd) {
//        out << rd.getValue();
//        return out;
//    }

//-------------------------------------------------------------------
    // Установка decimalPlaces и пересчёт значения
    void setDecimalPlaces(int newDecimalPlaces) {
        decimalPlaces = newDecimalPlaces;
        value = roundToDecimal(value, decimalPlaces); // Пересчёт с новым количеством знаков
    }


};
#endif // ROUNDEDDOUBLE_H
