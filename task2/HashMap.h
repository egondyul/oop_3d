#pragma once
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>
#include <stdexcept>
#include <memory>
#include <optional>
#include <shared_mutex>

template<class Key, class T, class Hash=std::hash<Key>, class TAllocator=std::allocator<std::list<const Key, T>>>
class HashMap
{
	using node_type = std::pair<const Key, T>;
public:
	using iterator = typename std::list<node_type>::iterator;
	using const_iterator = typename std::list<node_type>::const_iterator;

	HashMap()
	{
		hasher = Hash();
		table.resize(1, iterator());
		size_ = 0;
	}

	HashMap(size_t new_size, Hash& hasher_):hasher(hasher_)
	{
		hasher = Hash();
		table.resize(new_size, iterator());
		size_ = new_size;
	}


	HashMap(std::initializer_list<std::pair<const Key, T>> list, const Hash& hash = Hash())
	{
		size_++;
		table.resize(2 * size_, iterator());
		for (auto it : list)
		{
			insert(it);
		}
	}

	HashMap(const HashMap<Key, T>& other):hasher(other.hasher)
	{
		std::unique_lock<std::shared_mutex> lock(mutex);
		/*table.resize(1, elements.end());
		while (other.elements.begin() != other.elements.end())
		{
  			insert(*(other.elements.begin())++);
		}*/
		elements = other.elements;
		table = other.table;
		hasher = other.hasher;
		size_ = other.size_;
	}

	/*HashMap(HashMap&& other) :
		hasher(std::move(other.hasher)),
		table(std::move(other.table)),
		elements(std::move(other.elements)),
		size_(other.size_)
	{}*/

	HashMap(HashMap&& other)
	{
		hasher = std::move(other.hasher);
		table = std::move(other.table);
		elements = std::move(other.elements);
		size_ = other.size_;
	}

	virtual ~HashMap() {}

	HashMap& operator=(const HashMap<Key, T, Hash, TAllocator>& other)
	{
		std::unique_lock<std::shared_mutex>lock(mutex);
		this->hasher = other.hasher;
		this->table = other.table;
		this->elements = other.elements;
		this->size_ = other.size_;
		return *this;
	}

	HashMap& operator=(HashMap<Key, T, Hash, TAllocator>&& other)
	{
		std::unique_lock<std::shared_mutex>lock(mutex);
		this->hasher = std::move(other.hasher);
		this->table = std::move(other.table);
		this->elements = std::move(other.elements);
		this->size_ = other.size_;
		return *this;
	}

	/*HashMap& operator=(const HashMap<Key, T>& other)
	{
		std::unique_lock<std::shared_mutex> lock(mutex);
		if (this == &other)
		{
			return *this;
		}

		hasher = other.hasher;
		table.resize(1, elements.end());
		size_ = other.size_;
		elements = other.elements;
		//while (other.elements.begin() != other.elements.end())
		//{
		//	insert(*(other.elements.begin())++);
		//}
		return *this;
	}

	HashMap& operator=(HashMap<Key, T>&& other)
	{
		std::unique_lock<std::shared_mutex> lock(mutex);
		if (this == &other)
		{
			return *this;
		}

		hasher = std::move(other.hasher);
		table = std::move(other.table);
		elements = std::move(other.elements);
		size_ = other.size_;
		return *this;
	}*/

	void insert(const std::pair<const Key, T>& elem)
	{
		//std::unique_lock<std::shared_mutex> lock(mutex); //
		if (size_ / table.size() > 0.8)
		{
			rehash(table.size());
		}
		auto idx = hasher(elem.first) % table.size();
		elements.push_back(elem);
		size_ = elements.size();
		auto last = elements.end();
		--last;
		table[idx] = last;
		if (size_ * 2 > table.size())
		{
			rehash(table.size() * 2);
		}
	}

	void clear()
	{
		std::unique_lock<std::shared_mutex>lock(mutex);
		elements.clear();
		table.clear();
		size_ = 0;
		table.resize(1, iterator());
	}

	void rehash(size_t new_size)
	{
		std::unique_lock<std::shared_mutex> lock(mutex);
		HashMap<Key, T> new_map(new_size, hasher);
		for (auto i : elements)
		{
			new_map.insert(i);
		}

		std::swap(table, new_map.table);
		std::swap(elements, new_map.elements);
		std::swap(size_, new_map.size_);
		lock.unlock();
	}

	void swap(HashMap<Key, T, Hash, TAllocator>& other)
	{
		std::unique_lock<std::shared_mutex> lock(mutex);
		this->table.swap(other.table);
		this->elements.swap(other.elements);
		size_t tmp = size_;
		size_ = other.size_;
		other.size_ = tmp;
		Hash tmp2 = hasher;
		hasher = other.hasher;
		other.hasher = tmp2;
	}

	size_t size() const noexcept
	{
		std::shared_lock<std::shared_mutex> lock(mutex);
		return size_;
	}

	bool empty() const noexcept
	{
		std::shared_lock<std::shared_mutex> lock(mutex);
		return size_ == 0;
	}

	Hash hash_function() const 
	{
		return hasher;
	}

	iterator begin()
	{
		return elements.begin();
	}
	iterator end()
	{
		return elements.end();
	}
	const_iterator begin() const
	{
		return elements.cbegin();
	}
	const_iterator end() const
	{
		return elements.cend();
	}

	iterator find_(const Key& key) 
	{
		//std::unique_lock<std::shared_mutex> lock(mutex);
		auto idx = hasher(key) % table.size();
		while (elements.begin() != elements.end())
		{
			iterator it = table[idx];
			Key id = (*it).first;
			if (id == key)
			{
				return table[idx];
			}
		}
		return elements.end();
	}

	iterator find(const Key& key)
	{
		//std::unique_lock<std::shared_mutex> lock(mutex);
		auto idx = find_(key);
		return idx;
	}

	const_iterator find(const Key& key) const
	{
		//std::unique_lock<std::shared_mutex> lock(mutex);
		auto idx = find_(key);
		return static_cast<const_iterator>(idx);
	}

	T& operator[](const Key& key)
	{
		std::unique_lock<std::shared_mutex> lock(mutex);
		auto idx = find(key);
		if (idx != end())
		{
			return idx->second;
		}
		insert(std::make_pair(key, T{}));
		auto last = elements.end();
		--last;
		return (*last).second;
	}

	T& operator[](Key&& key)
	{
		std::unique_lock<std::shared_mutex> lock(mutex);
		auto idx = find(key);
		if (idx != end())
		{
			return idx->second;
		}
		insert(std::make_pair(key, T{}));
		auto last = elements.end();
		--last;
		return (*last).second;
	}

	node_type extract(const_iterator& it) const
	{
		std::shared_lock<std::shared_mutex> lock(mutex);
		if (end() != it)
		{
			return *it;
		}
	}

	node_type extract(const Key& key)
	{
		std::shared_lock<std::shared_mutex> lock(mutex);
		auto idx = find(key);
		if (idx != end())
		{
			return *idx;
		}
	}

	/*std::optional<T> get(const Key& key)
	{
		std::unique_lock<std::shared_mutex> lock(mutex);
		auto idx = find(key);
		if (idx != end())
		{
			return idx->second;
		}
		return {};
	}*/

private:
	Hash hasher;
	std::vector<typename std::list<node_type>::iterator> table;
	std::list<node_type> elements;
	size_t size_;

	mutable std::shared_mutex mutex;
};


/*#pragma once
#include <list>
#include <vector>
#include <algorithm>
#include<initializer_list>

template<typename Key, typename T, typename Hash = std::hash<Key>>// , typename TAllocator = std::allocator<std::list<const Key, T>> >
class HashMap
{
public:
	using node_type = typename std::pair<const Key, T>;
	using iterator = typename std::list<const Key, T>::iterator;
	using const_iterator = typename std::list<const Key, T>::const_iterator;

	HashMap(Hash hasher_ = Hash()) :hasher(hasher_)
	{
		size = 1;
		count_elements = 0;
		table.resize(size, data.end());
	}

	HashMap(const std::initializer_list<node_type>& list, Hash hasher_ = Hash()) :hasher(hasher_)
	{
		for (auto const &it : list)
		{
			insert(it);
		}
	}

	iterator begin()
	{
		return data.begin();
	}
	iterator end()
	{
		return data.end();
	}
	const_iterator begin() const
	{
		return data.cbegin();
	}
	const_iterator end() const
	{
		return data.cend();
	}

	void insert(const node_type& elem)
	{
		size_t idx = hasher(elem.first) % size;
		data.push_back(elem);
		table[idx].push_back(std::prev(data.end()));
		count_elements++;
		if (count_elements == size)
		{
			rebuild();
		}
	}

	void rebuild()
	{
		size *= 2;
		table.clear();
		table.resize(size);
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			size_t idx = hasher(it->first) % size;
			table[idx].push_back(it);
		}
	}

private:
	size_t size;
	size_t count_elements;
	std::list<node_type> data;
	std::vector<std::list<iterator>> table;
	Hash hasher;
};*/


