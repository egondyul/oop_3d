#include "Steam.h"
#include <iostream>
#include <string>
#include <memory>


int main(int argc, char** argv) {


	auto stream = makeStream({ 1,3 });
	auto result = stream | sum();

	return 0;
}

