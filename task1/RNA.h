#pragma once
#include <iostream>
#include <cstdint>
#include <bitset>
#include <unordered_map>

using namespace std;
using Int = uint16_t;

//nucleotides
enum Nucl :char
{
	A, //00
	G, //01
	C, //10
	T  //11
};

class RNA
{
private:
	Int* data; //8 bytes - 8 nucleoutide
	size_t size;
public:
	RNA(){}
	RNA(Nucl nucl, size_t rna_len);
	~RNA() { delete[] data; }

	class nuclref
	{
	private:
		size_t nucl_idx;
		RNA* This;
		//Nucl nucl;//BAD
	public:
		~nuclref(){}
		nuclref() :This(nullptr), nucl_idx(0) {}
		nuclref(size_t idx,RNA* rna):nucl_idx(idx),This(rna){}
		nuclref& operator=(const Nucl& other)
		{
			Nucl nucl = This->getNuclFromArray(This->data, nucl_idx);
			if (nucl == other)
			{
				return *this;
			}
			This->Set(other, nucl_idx);
			return *this;
		}

		nuclref& operator=(const nuclref& other)
		{
			Nucl nucl_1 = This->getNuclFromArray(This->data, nucl_idx);
			Nucl nucl_2 = This->getNuclFromArray(other.This->data, other.nucl_idx);
			if (nucl_1 == nucl_2)
			{
				return *this;
			}
			This->Set(nucl_2, nucl_idx);
			return *this;
		}

		bool operator==(const nuclref& other) const
		{
			Nucl nucl_1 = This->getNuclFromArray(This->data, nucl_idx);
			Nucl nucl_2 = This->getNuclFromArray(other.This->data, other.nucl_idx);
			if (nucl_1 == nucl_2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool operator!=(const nuclref& other) const
		{
			return !(operator==(other));
		}

		Nucl GetNuclFromRef()
		{
			return This->getNuclFromArray(This->data, nucl_idx);
		}

		friend class RNA;
	};

	RNA(const RNA& rna);
	RNA operator+(const RNA& r) const;
	RNA& operator=(const RNA& rna);
	bool operator==(const RNA& rna) const;
	bool operator!=(const RNA& rna) const;
	RNA operator!() const;

	RNA& operator+(Nucl nucl);
	RNA& operator+=(Nucl nucl);

	nuclref operator[](size_t idx)
	{
		return nuclref(idx,this);
	}
	//нужна ссылка внутрь байта
	/*Nucl& operator[](size_t idx)
	{
		if (idx >= size)
		{
			exit(0);
		}
		Nucl nucl = getNuclFromArray(data, idx);
		return nucl;
		//return nuclref(idx, *this);
	}*/

	/*Nucl& operator=(const Nucl& other)
	{
		Nucl nucl = other;
		return nucl;
	}*/

	const size_t capacity() const;
	size_t cardinality(Nucl nucl);
	void trim(size_t lastIdx);
	size_t length();
	bool isComplimentary(const RNA& rna) const;
	std::unordered_map< Nucl, size_t, std::hash<Int> > cardinality();
	friend ostream& operator<<(ostream&os, RNA& rna);

private:
	void Set(Nucl nucl, size_t idx) const;
	void SetNucl(Int& elem, Nucl nucl, size_t idx) const;
	Nucl getNuclFromArray(Int* array, size_t idx) const;
	Nucl getNucl(Int elem, size_t idx) const;
};
