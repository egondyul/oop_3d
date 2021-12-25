// ControlWork.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <thread>
#include <iostream>

//task 1
class ThreadRAII
{
public:
	ThreadRAII(std::thread&& tmp) :t(std::move(tmp)) {};

	~ThreadRAII()
	{
		if (this->t.joinable())
		{
			this->t.join();
		}
	}

	bool is_join(std::thread t)
	{
		bool tmp;
		if (t.joinable())
		{
			tmp = true;
		}
		else
		{
			tmp = false;
		}
		return tmp;
	}

	ThreadRAII(const ThreadRAII&) = delete;
	ThreadRAII& operator=(const ThreadRAII&) = delete;

private:
	std::thread t;
};


int main()
{
	ThreadRAII th_raii(std::thread());
	

	return 0;
}
