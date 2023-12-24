    // ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
    //
    // tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
    //   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
    //
    // Множество - реализация через битовые поля

    #include "tset.h"

    TSet::TSet(int _MaxPower):bf(_MaxPower), MaxPower(_MaxPower) { }

    // конструктор копирования
    TSet::TSet(const TSet &s) : bf(s.bf), MaxPower(s.MaxPower) { }

    // конструктор преобразования типа
    TSet::TSet(const TBitField &_bf) : bf(_bf), MaxPower(_bf.GetLength()) { }

    TSet::operator TBitField()
    {
        return bf;
    }

    int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
    {
        return MaxPower;
    }

    bool TSet::IsMember(const int Elem) const // элемент множества?
    {
        int res = bf.GetBit(Elem);
        return res;
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

    bool TSet::operator==(const TSet &s) const // сравнение
    {
        return (bf == s.bf);
    }

    bool TSet::operator!=(const TSet &s) const // сравнение
    {
        return (bf != s.bf);
    }

    TSet TSet::operator+(const TSet &s) // объединение
    {
        TSet res(s);
        res.bf = res.bf | bf;
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
        TSet res(s);
        res.bf = res.bf & bf;
        return res;
    }

    TSet TSet::operator~(void) // дополнение
    {
        TSet res(*this);
        res.bf = ~(res.bf);
        return res;
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
