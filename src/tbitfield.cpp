// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) // конструктор по умолчанию
{
	if (len <= 0) throw ("Wrong size!");
	MemLen = len / 32 + 1;
	BitLen = len;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = nullptr;
	BitLen = 0;
	MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > BitLen - 1) || (n < 0))
		throw ("Index out!\n");
	return (n/32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM t = 1;
	int shift = n % 32;
	TELEM res = t << shift;
	return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0)||(n > BitLen - 1)) throw ("Wrong index!\n");
	TELEM m = GetMemMask(n);
	int idx = GetMemIndex(n);
	pMem[idx] = pMem[idx] | m;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen - 1)) throw ("Wrong index!\n");
	TELEM m = ~(GetMemMask(n));
	int idx = GetMemIndex(n);
	pMem[idx] = pMem[idx] & m;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen - 1)) throw ("Wrong index!\n");
	TELEM m = GetMemMask(n);
	int idx = GetMemIndex(n);
	TELEM res = pMem[idx] & m;
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (MemLen != bf.MemLen) {
		delete[] pMem;
		pMem = new TELEM[bf.MemLen];
	}
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) return false;
	{
		for (int i = 0; i < MemLen - 1; i++) {
			if (pMem[i] != bf.pMem[i])
				return false;
		}
		for (int i = (MemLen - 1) * 32; i < BitLen; i++) {
			if (GetBit(i) != bf.GetBit(i))
				return false;
		}
	}
	return true;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (*this == bf) return false;
	else return true;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	if (BitLen > bf.BitLen) {
		TBitField res(*this);
		for (int i = 0; i < bf.MemLen; i++) 
			res.pMem[i] = pMem[i] | bf.pMem[i];
		for (int i = (bf.MemLen - 1) * 32 + bf.BitLen % 32; i < BitLen; i++) {
			if (GetBit(i)) 
				res.SetBit(i);
			else 
				res.ClrBit(i);
		}
		return res;
	}
	else if (bf.BitLen > BitLen) {
		TBitField res(bf);
		for (int i = 0; i < MemLen; i++) 
			res.pMem[i] = pMem[i] | bf.pMem[i];
		for (int i = (MemLen - 1) * 32 + BitLen % 32; i < bf.BitLen; i++) {
			if (bf.GetBit(i)) 
				res.SetBit(i);
			else 
				res.ClrBit(i);
		}
		return res;
	}
	else {
		TBitField res(bf);
		for (int i = 0; i < MemLen; i++) 
			res.pMem[i] = pMem[i] | bf.pMem[i];
		return res;
	}
}	

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	if (BitLen > bf.BitLen) {
		TBitField res(*this);
		for (int i = 0; i < bf.MemLen; i++) {
			res.pMem[i] = bf.pMem[i] & pMem[i];
		}
		for (int i = (bf.MemLen - 1) * 32 + bf.BitLen % 32; i < BitLen; i++) {
			res.ClrBit(i);
		}
		return res;
	}
	else if (bf.BitLen > BitLen) {
		TBitField res(bf);
		for (int i = 0; i < MemLen; i++) {
			res.pMem[i] = bf.pMem[i] & pMem[i];
		}
		for (int i = (MemLen - 1) * 32 + BitLen % 32; i < bf.BitLen; i++) {
			res.ClrBit(i);
		}
		return res;
	}
	else {
		TBitField res(bf);
		for (int i = 0; i < MemLen; i++) {
			res.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return res;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = ~(res.pMem[i]);
	return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	char rab;
	for (int i = 0; i < bf.MemLen; i++) bf.pMem[i] = 0;
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> rab;
		if (rab == '1') bf.SetBit(i);
		else 
			if (rab == '0') bf.ClrBit(i);
			else break;
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
	}
	ostr << endl;
	return ostr;
}
