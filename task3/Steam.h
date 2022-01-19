#pragma once
#include <vector>
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <functional>
#include <memory>
#include <type_traits>

template<class Iterator>
class Stream
{
public:
	Stream(Iterator& begin, Iterator& end)
	{
		begin_ = begin;
		end_ = end;
		iter_ = begin;
	}

	Stream(Iterator&& begin, Iterator&& end)
	{
		begin_ = std::move(begin);
		end_ = std::move(end);
		iter_ = begin;
	}

	auto get() {
		if (iter_ == end_) {
			return std::shared_ptr<std::remove_const_t<std::remove_reference_t<decltype(*begin_)>>>();
		}
		auto value = std::make_shared<std::remove_const_t<std::remove_reference_t<decltype(*begin_)>>>(std::move(*iter_));

		iter_++;
		return (value);
	};

private:
	Iterator begin_;
	Iterator end_;
	Iterator iter_;
};

template<class Iterator>
auto makeStream(Iterator&& begin, Iterator&& end)
{
	return Stream<Iterator>(begin, end);
}

template<class Container>
auto makeStream(const Container& cont)
{
	return makeStream(cont.begin(), cont.end());
}

template<class T>
auto makeStream(std::initializer_list<T> init)
{
	return makeStream(init.begin(), init.end());
}

template<class Function>
class Operator
{
public:
	Operator(Function&& f) :func(std::move(f)) {};
	
	template<class Stream_>
	auto operator()(Stream_&&stream)->std::result_of_t < Function ( Stream_&&) >
	{
		return func(std::forward<Stream_>(stream));
	}
private:
	Function func;
};

template<class Function>
auto makeOperator(Function&& f)
{
	return Operator<Function>(std::forward<Function>(f));
}

template<class Stream_, class Function>
auto operator |(Stream_&& stream, Operator<Function>&&op)->std::result_of_t<decltype(op)(Stream_&&)>
{
	return op(std::forward<Stream_>(stream));
}

auto sum() {
	return makeOperator([](auto&& stream) -> auto {

		auto res_ref = stream.get();
		using R = std::remove_const_t<std::remove_reference_t<decltype(*stream.get())>>;
		R res=0;
		if (res_ref.get() == nullptr) return res;
		res = *(res_ref);
		while (true) {
			auto tmp_ref = stream.get();
			if (tmp_ref.get() == nullptr) return res;
			res += *(tmp_ref);
		}
	});
}
