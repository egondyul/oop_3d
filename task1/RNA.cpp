#include "RNA.h"

RNA::RNA(Nucl nucl, size_t rna_len)
{
	size = rna_len;

	size_t rna_bytes = this->capacity();

	data = new Int[rna_bytes];

	for (size_t i = 0; i < rna_bytes; i++)
	{
		data[i] = 0;
	}

	for (size_t idx = 0; idx < size; idx++)
	{
		Set(nucl, idx);
	}
}

void RNA::Set(Nucl nucl, size_t idx)
{
	size_t t = idx / 8;
	size_t i = 0;
	if (t > 0)
	{
		i = idx - t * 8;
	}
	else
	{
		i = idx;
	}

	SetNucl(data[t], nucl, i);
}

void RNA::SetNucl(Int& elem, Nucl nucl, size_t idx)
{
	Int nucl_ch = Int(nucl);
	Int tmp = 0x03;
	if (idx < 7)
	{
		nucl_ch = nucl_ch << (7 - idx) * 2;
		tmp = tmp << (7 - idx) * 2;
	}
	tmp = ~tmp;
	elem = elem & tmp;
	elem = elem | nucl_ch;

	/*Int nucl_ch = Int(nucl);

	std::bitset<16> x(elem);
	std::cout << x<< std::endl;
	std::cout << " OR " << std::endl;
	if (idx >= 0)
	{
		nucl_ch = nucl_ch << (7 - idx) * 2;
		std::bitset<16> xx(nucl_ch);
		std::cout << xx << std::endl;
	}
	elem = elem | nucl_ch;
	std::cout << " = " << std::endl;
	std::bitset<16> y(elem);
	std::cout << y << std::endl;*/
}

size_t RNA::capacity()
{
	return (size-1) / 8 + 1;
}

Nucl RNA::getNuclFromArray(Int* array, size_t idx)
{
	size_t t = idx / 8;
	size_t i;
	if (t > 0)
	{
		i = idx - t * 8;
	}
	else
	{
		i = idx;
	}
	Nucl res = getNucl(array[t], i);
	return res;
}

Nucl RNA::getNucl(Int elem, size_t idx)
{
	if (idx < 7)
	{
		elem = elem >> (7 - idx) * 2;
	}
	Int opt = 0x03;
	Int result = elem & opt;

	Nucl element = Nucl(result);
	return element;
}

RNA& RNA::operator+(RNA& rna)
{
	size_t s = size + rna.size;
	RNA tmp(A, s);
	size_t t= (s - 1) / 8 + 1;

	for (size_t i = 0; i < s - rna.size; i++)
	{
		tmp[i] = (*this)[i];
	}

	for (size_t i = s - rna.size; i < s; i++)
	{
		tmp[i] = rna[i - (s - rna.size)];
	}

	if ((*this).data != nullptr)
	{
		delete[](*this).data;
		(*this).data = nullptr;
	}
	(*this) = tmp;
	return *this;
}

RNA::RNA(const RNA& rna) :size(rna.size)
{
	size_t t = this->capacity();
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
	data = new Int[t];
	for (int i = 0; i < t; i++)
	{
		data[i] = rna.data[i];
	}
}

RNA& RNA::operator=(const RNA& rna)
{
	if (this == &rna)
	{
		return *this;
	}
	
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
	size = rna.size;
	size_t t = this->capacity();
	data = new Int[t];
	for (int i = 0; i < t; i++)
	{
		data[i] = rna.data[i];
	}
	return *this;
}

bool RNA::operator==(const RNA& rna)
{
	std::cout << *this << std::endl;
	std::cout << rna.data[0] << std::endl;
	RNA tmp = rna;

	bool res = true;
	if (this->size == rna.size)
	{
		for (size_t i = 0; i < size; i++)
		{
			if ((*this)[i] != tmp[i]) //&& (*this).data[i] != rna.data[size - i - 1])
			{
				res = false;
				break;
			}
		}
	}
	else
	{
		res = false;
	}
	return res;
}

bool RNA::operator!=(const RNA&rna)
{
	/*bool res = true;
	if (this->size == rna.size)
	{
		res = false;
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			if ((*this).data[i] == rna.data[i])
			{
				res = false;
				break;
			}
		}
	}
	return res;*/
	return !(operator==(rna));
}

RNA &RNA::operator!()
{
	std::cout << *this << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		Nucl nucl = getNuclFromArray(data, i);
		switch (nucl)
		{
		case A:
			Set(T, i);
			break;
		case G:
			Set(C, i);
			break;
		case C:
			Set(G, i);
			break;
		case T:
			Set(A, i);
			break;
		}

	}
	std::cout << *this << std::endl;
	return *this;
}

size_t RNA::cardinality(Nucl nucl)
{
	size_t count = 0;
	for (size_t i = 0; i < size; i++)
	{
		Nucl tmp = getNuclFromArray(data, i);
		if (tmp == nucl)
		{
			count += 1;
		}
	}
	return count;
}

void RNA::trim(size_t lastIdx)
{
	size_t new_size = lastIdx + 1;
	if (new_size < size)
	{
		Int* new_data;
		new_data = new Int[new_size];
		for (size_t i = 0; i < new_size; i++)
		{
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		size = new_size;
	}
	else
	{
		std::cout << "sorry, but we are exiting the array" << std::endl;
	}
}

bool RNA::isComplimentary(RNA& rna)
{
	!rna;
	std::cout << *this << std::endl;
	if (rna == *this)
	{
		!rna;
		return true;
	}
}

size_t RNA::length()
{
	return size;
}

std::unordered_map< Nucl, int, std::hash<int> > cardinality()
{

}

ostream & operator<<(ostream & os, RNA & rna)
{
	for (size_t i = 0; i < rna.size; i++)
	{
		os << int(rna.getNuclFromArray(rna.data, i)) << " | ";
	}
	return os;
}
