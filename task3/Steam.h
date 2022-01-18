#pragma once

#include "BasicStream.h"

template<class It>
class Stream : public BasicStream<Stream<It>>
{
	It begin_;
	It end_;
	It iter_;

public:
	Stream(It& begin, It& end)
	{
		begin_ = begin;
		end_ = end;
		iter_ = begin;
	}

	Stream(It&& begin, It&& end)
	{
		begin_ = std::move(begin);
		end_ = std::move(end);
		iter_ = std::move(begin);
	}

	auto get()
	{

	}

};


template<class Function>
class Operator
{
	Function func;
public:
	Operator(Function&& f)
	{
		func = std::move(f);
	}

	template<class Stream_>
	auto operator()(Stream_&& str)->std::result_of_t<Function(Stream_&&)>
	{
		return func(std::forward<Stream_>(str));
	}
};

template<class Stream_, class Function>
auto operator | (Stream_&& stream, Operator<Function>&& oper)->std::result_of_t<decltype(oper)(Stream_&&)>
{
	return oper(std::forward<Stream_>(stream));
}

template<class It>
auto makeStream(It begn, It end)
{
	return Stream<It>(begin, end);
}