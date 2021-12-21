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
	size_t ss = map.size();
	std::cout << "size of first map is " << map.size() << std::endl;
	HashMap<int, char> map2{ make_pair(1,'a'), make_pair(3,'a') };
	map2.insert(make_pair(2, 'c'));
	for (auto& it : map2) {
		std::cout << it.first << " " << it.second << std::endl;
	}
	map[1] = 'b';
	for (auto& it : map) {
		std::cout << it.first << " " << it.second << std::endl;
	}
	
	HashMap<int, char> map_;
	map_ = map;

	map.swap(map2);



	/*HashMap map3(map); // equal to HashMap map3 = map;
	HashMap<int, char> map_{ make_pair(1,'c') };
	map_ = map3;



	std::cout << "map3 for your eyes: " << std::endl;
	for (auto& it : map3) {
		std::cout << it.first << " " << it.second << std::endl;
	}*/


	HashMap<int, std::string> map4;

	auto begin = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 10; i++) {
		map4.insert(make_pair(i, "AAAA "));
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;

	auto beginT = std::chrono::high_resolution_clock::now();

	std::thread thread1([&]() {
		for (int i = 0; i < 10; i++) {
			map4.insert(make_pair(i, "BBBB"));
		}
	});

	std::thread thread11([&]() {
		std::cout << "size = "<< map4.size() << std::endl;
	});

	std::thread thread2([&]() {
		for (int i = 0; i < 10; i++) {
			map4.insert(make_pair(i, "CCCC"));
		}
	});

	std::thread thread21([&]() {
		std::cout << "size = " << map4.size() << std::endl;
	});

	std::thread thread3([&]() {
		for (int i = 0; i < 10; i++) {
			map4.insert(make_pair(i, "DDDD"));
		}
	});

	std::thread thread31([&]() {
		std::cout << "size = " << map4.size() << std::endl;
	});

	std::thread thread4([&]() {
		for (int i = 0; i < 10; i++) {
			map4.insert(make_pair(i, "EEEE"));
		}
	});

	std::thread thread41([&]() {
		std::cout << "size = " << map4.size() << std::endl;
	});

	std::thread thread5([&]() {
		for (int i = 0; i < 10; i++) {
			map4.insert(make_pair(i, "FFFF"));
		}
	});

	std::thread thread51([&]() {
		std::cout << "size = " << map4.size() << std::endl;
	});


	auto endT = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endT - beginT).count() <<std::endl;


	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	thread5.join();

	thread11.join();
	thread21.join();
	thread31.join();
	thread41.join();
	thread51.join();

	for (auto& it : map4) {
		std::cout << it.first << " " << it.second << std::endl;
	}

	std::cout << "size of all map4 is " << map4.size() << std::endl;

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
