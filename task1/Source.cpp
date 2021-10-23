#include <iostream>
#include <cstdint>
#include <bitset>
#include "RNA.h"
#include "DNA.h"

int main()
 {
	const RNA r(A, 10);
	Nucl n = r[0];

	/*size_t n = 100;
	RNA tmp(A, 1);
	for (size_t i = 0; i < n; i++)
	{
		tmp += Nucl(rand() & 3);
	}
	std::cout << n << std::endl;*/
	//std::cout << tmp << std::endl;

	RNA rna(A, 10);
	RNA rna2 = rna + rna;
	std::cout << rna << std::endl;
	std::cout << rna2 << std::endl;
	rna = rna;
	std::cout << rna << std::endl;
	//Nucl n = rna[1];

	std::unordered_map< Nucl, size_t, std::hash<Int> > card = rna.cardinality();
	for (auto& x : card) {
		std::cout << x.first << ": " << x.second << std::endl;
	}

	/*RNA rna(G,10);
	//std::cout << rna<<std::endl;
	rna[2] = T;
	rna[3] = rna[2];
	//std::cout << rna << std::endl;

	RNA rna2(G, 2);
	//std::cout << rna2 << std::endl;

	RNA rna3 = rna2;
	//std::cout << rna3 << std::endl;

	RNA rna4 = rna + rna2;
	//std::cout << rna4 << std::endl;

	!rna4;
	//std::cout << rna5 << std::endl;

	//std::cout << rna.cardinality(G) << std::endl;

	/*rna4.trim(5);
	//std::cout << rna4 << std::endl;
	
	RNA rna_smt(A, 5);
	RNA rna_com(T, 5);
	std::cout << (rna_smt == rna_com) << std::endl;
	bool prove = rna_smt.isComplimentary(rna_com);
	std::cout << prove << std::endl;


	DNA dna(rna_smt, rna_com);*/

	/*Nucl nucl;
	Int chr = 9;
	nucl = getNucl(chr, 7);
	std::cout << nucl << std::endl;

	Int elem = 0;
	chr = setNucl(elem, nucl, 3);
	std::bitset<16> x(chr);
	std::cout << x << std::endl;

	Int*array;
	array = new Int[2];
	array[0] = chr;
	nucl = getNuclFromArray(array, 3);
	std::cout << nucl << std::endl;*/
	return 0;
}

 