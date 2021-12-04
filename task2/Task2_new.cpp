// Task2_new.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include "HashMap.h"

using namespace std;

int main()
{
	HashMap<int, char> map;
	map.insert(make_pair(1, 'a'));
	HashMap<int, char> map2{ make_pair(1,'a'), make_pair(3,'a') };
	map2.insert(make_pair(2, 'c'));
	for (auto& it : map2) {
		std::cout << it.first << " " << it.second << std::endl;
	}
	map[1] = 'b';
	for (auto& it : map) {
		std::cout << it.first << " " << it.second << std::endl;
	}

	HashMap map3 = map;

	HashMap<int, std::string> map4;

	auto begin = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++) {
		map4.insert(make_pair(i, "AAAA "));
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;

	auto beginT = std::chrono::high_resolution_clock::now();
	std::thread thread1([&]() {
		for (int i = 0; i < 1000000; i++) {
			map4.insert(make_pair(i, "BBBB "));
		}
	});

	auto endT = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endT - beginT).count() <<std::endl;


	thread1.join();

	for (auto& it : map4) {
		std::cout << it.first << " " << it.second << std::endl;
	}

	/*for (int i = 0; i < 1000000; i++) {
		map.insert(make_pair(i, 'f'));
	}*/




	/*HashMap<int, std::string> map2;

	std::thread worker1([&]() {
		for (int i = 0; i < 10; i++) {
			map2.insert(make_pair(i, "TestString"));
		}
	});

	worker1.join();

	const HashMap<int, char> map3(std::move(map));*/


	/*std::threadsafe::stack<int> stack;
	stack.push(0);

	std::thread threads[NUM_WORKERS];

	for (int i = 0;i < NUM_WORKERS;i++)
		threads[i] = std::thread(increment,std::ref(stack));

	for (int i = 0;i < NUM_WORKERS;i++)
		threads[i].join();

	// It should print: NUM_WORKERS*INCR
	int n;
	stack.wait_pop(n);
	std::cout << n << std::endl;*/

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
 
// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
