#pragma once
#include <iostream>
#include <cstdint>
#include <bitset>

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
	RNA()
	{
		size = 0;
		data = new Int[0];
	}
	RNA(Nucl nucl, size_t rna_len);
	~RNA() { delete[] data; }

	RNA& operator+(RNA& r);

	class nuclref
	{
	private:
		size_t nucl_idx;
		RNA* This;
		//Nucl nucl;//BAD
	public:
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

		bool operator==(const nuclref& other)
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

		bool operator!=(const nuclref& other)
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

	RNA& operator=(const RNA& rna);

	bool operator==(const RNA& rna);
	bool operator!=(const RNA& rna);

	RNA &operator!();


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

	void Set(Nucl nucl, size_t idx);
	void SetNucl(Int& elem, Nucl nucl, size_t idx);

	//void SetNuclsInArray(Nucl nucl, size_t idx);
	//Int setNucl(Int elem, Nucl nucl, size_t idx);

	size_t capacity();

	Nucl getNuclFromArray(Int* array, size_t idx);
	Nucl getNucl(Int elem, size_t idx);

	size_t cardinality(Nucl nucl);
	void trim(size_t lastIdx);
	size_t length();

	bool isComplimentary(RNA& rna);
	friend ostream& operator<<(ostream&os, RNA& rna);
};
