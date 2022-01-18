#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <exception>
#include <initializer_list>
#include <functional>
#include <memory>
#include <type_traits>

template<class Type>
class BasicStream
{
	auto get()
	{
		return std::move(static_cast<Type*>(this)->get());
	}
};

