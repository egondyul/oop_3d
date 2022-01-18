#include "Steam.h"
#include <iostream>
#include <string>
#include <memory>


int main(int argc, char** argv) {


	auto stream = makeStream({ 1,2 });
	auto result = stream | sum();


	//auto result = stream | map([](auto a) -> auto {return a; }) | to_vector();
	//std::cout << "IMHERE " << result.size() << std::endl;
	//auto& vec = result.at(0);
//std::cout << vec.size() << std::endl;
//for (int i = 0; i < 2; i++){
//	std::cout << vec.at(i);
//}

//std::vector<A> v(4);
//auto stream = makeStream(v);
//stream | map([](auto a) {return a;}) | print_to(std::cout, " ");

//for (auto i = result.begin(); i != result.end(); i++){
//	std::cout << *i << std::endl;
//}


	return 0;
}

