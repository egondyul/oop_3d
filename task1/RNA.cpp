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

void RNA::Set(Nucl nucl, size_t idx) const
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

void RNA::SetNucl(Int& elem, Nucl nucl, size_t idx) const
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

const size_t RNA::capacity() const
{
	return (size-1) / 8 + 1;
}

Nucl RNA::getNuclFromArray(Int* array, size_t idx) const
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

Nucl RNA::getNucl(Int elem, size_t idx) const
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

RNA RNA::operator+(const RNA& rna) const
{
	size_t s = size + rna.size;
	RNA tmp(A, s);
	size_t t= (s - 1) / 8 + 1;

	for (size_t i = 0; i < s - rna.size; i++)
	{
		tmp[i] = this->getNuclFromArray(this->data, i);//(*this)[i];
	}

	for (size_t i = s - rna.size; i < s; i++)
	{
		tmp[i] = rna.getNuclFromArray(rna.data, i - (s - rna.size)); //rna[i - (s - rna.size)];
	}

	/*if ((*this).data != nullptr)
	{
		delete[](*this).data;
		(*this).data = nullptr;
	}
	(*this) = tmp;*/
	return tmp;
}

RNA::RNA(const RNA& rna) :size(rna.size)
{
	size_t t = rna.capacity();
	data = new Int[t];
	for (int i = 0; i < t; i++)
	{
		data[i] = rna.data[i];
	}
	/*size_t t = this->capacity();
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
	data = new Int[t];
	for (int i = 0; i < t; i++)
	{
		data[i] = rna.data[i];
	}*/
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

bool RNA::operator==(const RNA& rna) const
{
	RNA tmp = rna;
	bool res = true;
	if (this->size == rna.size)
	{
		for (size_t i = 0; i < size; i++)
		{
			//if ((*this)[i] != tmp[i]) //&& (*this).data[i] != rna.data[size - i - 1])
			if (this->getNuclFromArray(this->data, i) != rna.getNuclFromArray(rna.data, i))
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

bool RNA::operator!=(const RNA&rna) const
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

RNA RNA::operator!() const
{
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

bool RNA::isComplimentary(const RNA& rna) const
{
	!rna;
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

std::unordered_map< Nucl, size_t, std::hash<Int> > RNA::cardinality()
{
	std::unordered_map< Nucl, size_t, std::hash<Int> > card;
	for (size_t i = 0; i < size; i++)
	{
		if (card.count(getNuclFromArray((*this).data, i)) == 0) {
			card.insert(std::unordered_map< Nucl, size_t, std::hash<Int> >::value_type(getNuclFromArray((*this).data, i), 1));
		}
		else
		{
			++card.at(getNuclFromArray((*this).data, i));
		}
	}
	return card;
}

void RNA::reserve()
{
	if (size == 0)
	{
		data = new Int[1];
		data[0] = 0;
		++size;
	}
	else
	{
		size_t t = this->capacity();
		Int *tmp = new Int[t * 2];
		for (size_t i = 0; i < t; i++)
		{
			tmp[i] = data[i];
		}
		for (size_t i = t; i < 2 * t; i++)
		{
			tmp[i] = 0;
		}
		delete[]data;
		data = tmp;
	}
}

RNA& RNA::operator+(Nucl nucl)
{
	++size;
	reserve();
	(*this)[size - 1] = nucl;
	return *this;
	/*size_t s = size + 1;
	RNA tmp(A, s);
	for (size_t i = 0; i < s - 1; i++)
	{
		tmp[i] = this->getNuclFromArray(this->data, i);
		//tmp[i] = (*this)[i];
	}
	tmp[s - 1] = nucl;
	if ((*this).data != nullptr)
	{
		delete[](*this).data;
		(*this).data = nullptr;
	}
	(*this) = tmp;
	return *this;*/
}

RNA& RNA::operator+=(Nucl nucl)
{
	*this = *this + nucl;
	return *this;
}

Nucl RNA::operator=(const nuclref& nref) const
{
	Nucl nucl = nref.This->getNuclFromArray(nref.This->data, nref.nucl_idx);
	return nucl;
}

ostream & operator<<(ostream & os, RNA & rna)
{
	for (size_t i = 0; i < rna.size; i++)
	{
		os << int(rna.getNuclFromArray(rna.data, i)) << " | ";
	}
	return os;
}
