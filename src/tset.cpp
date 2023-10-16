// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int _MaxPower):bf(_MaxPower)
{
    MaxPower = _MaxPower;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bf(s.bf)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &_bf) : bf(_bf), MaxPower(_bf.GetLength())
{

}

TSet::operator TBitField()
{
    return this->bf;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
}

bool TSet::IsMember(const int Elem) const // элемент множества?
{
    return bf.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    bf.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    bf.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    bf = s.bf;
    MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower) return 0;
    else 
        if (bf != s.bf) return 0;
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (*this == s) return 0;
    else
        return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet res(*this);
    res.bf = bf | s.bf;
    res.MaxPower = res.bf.GetLength();
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.InsElem(Elem);
    res.MaxPower++;
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(*this);
    res.DelElem(Elem);
    res.MaxPower--;
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet res(*this);
    res.bf = bf & s.bf;
    res.MaxPower = res.bf.GetLength();
    return res;
}

TSet TSet::operator~(void) // дополнение
{

    return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int m;
    char d;
    istr >> d;
    while (d != '}') {
        istr >> m;
        s.InsElem(m);
        istr >> d;
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << '{';
    for (int i = 0; i < s.MaxPower; i++)
        if (s.IsMember(i))
            ostr << i << ",";
    ostr << '}' << endl;
    return ostr;
}
