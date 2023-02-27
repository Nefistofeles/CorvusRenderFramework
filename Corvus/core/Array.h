#pragma once
#include "Core.h"
namespace Corvus
{
	template<class T>
	class Array
	{
	private:
		T* _datas = nullptr;
		uint32 _index = 0;
		uint32 _size = 0;
	public:
		Array();
		Array(uint32 size);
		~Array();
		//resize total data
		void Resize(uint32 size);
		T& operator [](uint32 index)
		{
			if (index >= _size && index < 0)
			{
				DEBUG("array index bound of exception ", index, " ", _size);
			}
			return _datas[index];
		}
		//get total data size
		uint32 Size();
		//get avaliable size
		uint32 AvaliableSize();
		//emplace data and increase avaliable size
		void Emplace(const T& data);
		void Pop();
		bool IsAvaliable(uint32 index);
		//delete data
		void Delete(uint32 index);
		//reset avaliable size
		void Reset();
	};

	template<class T>
	inline Array<T>::Array()
	{
	}

	template<class T>
	inline Array<T>::Array(uint32 size)
	{
		Resize(size);
	}

	template<class T>
	inline Array<T>::~Array()
	{
		delete[] _datas;
	}

	template<class T>
	inline void Array<T>::Resize(uint32 size)
	{
		if (size < _size)
			return;
		if (_datas != nullptr)
		{
			T* temp = new T[size];
			for (int32 i = 0; i < _size; i++)
			{
				temp[i] = _datas[i];
			}
			delete[] _datas;
			_datas = temp;
			_size = size;
		}
		else
		{
			_datas = new T[size];
			_size = size;
		}
	}

	template<class T>
	inline uint32 Array<T>::Size()
	{
		return _size;
	}

	template<class T>
	inline uint32 Array<T>::AvaliableSize()
	{
		return _index;
	}

	template<class T>
	inline void Array<T>::Emplace(const T& data)
	{
		if (_index >= _size)
		{
			Resize(_size == 0 ? 1 : _size * 2.0f);
		}
		_datas[_index] = data;
		_index++;
	}

	template<class T>
	inline void Array<T>::Pop()
	{
		_index--;
	}

	template<class T>
	inline bool Array<T>::IsAvaliable(uint32 index)
	{
		if (index <= _index - 1)
		{
			return true;
		}
		return false;
	}

	template<class T>
	inline void Array<T>::Delete(uint32 index)
	{
		if (IsAvaliable(index))
		{
			auto& temp = _datas[_index - 1];
			_datas[index] = temp;
			_index--;
		}
	}

	template<class T>
	inline void Array<T>::Reset()
	{
		_index = 0;
	}

}