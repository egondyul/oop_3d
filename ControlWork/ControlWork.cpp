// ControlWork.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <thread>
#include <atomic>
#include <mutex>
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

//task2
class Car
{
public:
	void set_false()
	{
		is_painted =false;
	}
	void set_true()
	{
		is_painted = true;
	}
	bool get_flag()
	{
		return is_painted;
	}

private:
	bool is_painted = false;
};
 //нужно исключить повторное взятие ранее полученных блокировок
class Painter
{
public:

private:
	std::thread th_painter;
};

class Dryer
{
public:

private:
	std::thread th_dryer;
};

//task 3
class Singleton1
{
	Singleton1() {};
	static std::atomic<Singleton1*> instance;
	static std::mutex m;
public:
	static Singleton1 * getInstance()
	{
		if (nullptr == instance)
		{
			std::lock_guard<std::mutex> lock(m);
			if (nullptr == instance)
			{
				instance = new Singleton1;
			}
		}

		return instance.load();
	}
};
std::atomic<Singleton1*> Singleton1::instance = nullptr;
std::mutex Singleton1::m;

class Singleton2
{
	Singleton2() {};
	static std::atomic<Singleton2*> instance;
	static std::mutex m;
public:
	
	static Singleton2 * getInstance()
	{
		auto tmp = instance.load(std::memory_order_relaxed);
		std::_Atomic_thread_fence(std::memory_order_acquire);
		if (nullptr == tmp)
		{
			std::lock_guard<std::mutex> lock(m);
			tmp = instance.load(std::memory_order_relaxed);
			if (nullptr == tmp)
			{
				tmp = new Singleton2;
				std::atomic_thread_fence(std::memory_order_release);
				instance.store(tmp, std::memory_order_relaxed);
			}
		}
		return instance.load();
	}
};
std::atomic<Singleton2*> Singleton2::instance = nullptr;
std::mutex Singleton2::m;

//task4
/*class SpinLock
{
public:

	void unlock()
	{
		while (flag.test_and_set(std::memory_order_acquire));
	}
	inline void unlock()
	{
		flag.clear(std::memory_order_release);
	}
private:
	std::atomic_flag flag;
};*/

class SpinLock
{
public:
	SpinLock() : fFlag{ false }
	{
	}

	SpinLock(SpinLock const &) = delete;
	SpinLock &operator=(SpinLock const &) = delete;
	inline void lock()
	{
		while (fFlag.test_and_set(std::memory_order_acquire))
		{
			// nothing to do => spin
		};
	}
	inline void unlock()
	{
		fFlag.clear(std::memory_order_release);
	}
private:
	std::atomic_flag fFlag;
};


int main()
{
	//task 1
	ThreadRAII th_raii(std::thread());
	
	//task 3
	Singleton1* ptr1 = Singleton1::getInstance();
	Singleton2* ptr2 = Singleton2::getInstance();

	




	return 0;
}
