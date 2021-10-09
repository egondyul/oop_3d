#include "DNA.h"

DNA::DNA(RNA& rna1, RNA& rna2)
{
	if (rna1.isComplimentary(rna2) == true)
	{
		rna = new RNA(rna1);
	}
	else
	{
		std::cout << "sorry, rna arent complantary" << std::endl;
	}
}