#pragma once
#include "Core.h"

namespace Corvus
{
	template<class T>
	class UniquePtr
	{
	private:
		T* _ptr;
	public:
		UniquePtr();
		UniquePtr(T* ptr);
		~UniquePtr();

		T* Get();
		T* operator -> () { return _ptr; }
		void operator=(T* ptr)
		{
			if (_ptr != nullptr)
			{
				delete _ptr;
				_ptr = nullptr;
			}
			_ptr = ptr;
		}

	};
	template<class T>
	inline bool operator==(UniquePtr<T> left, nullptr_t)
	{
		return left.Get() == nullptr;
	}
	template<class T>
	inline bool operator==(nullptr_t, UniquePtr<T> right)
	{
		return right.Get() == nullptr;
	}
	template<class T>
	inline bool operator==(UniquePtr<T> left, UniquePtr<T> right)
	{
		return left.Get() == right.Get();
	}
	template<class T>
	inline UniquePtr<T>::~UniquePtr()
	{
		if (_ptr != nullptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}
	template<class T>
	inline UniquePtr<T>::UniquePtr() : _ptr(nullptr) {}

	template<class T>
	inline UniquePtr<T>::UniquePtr(T* ptr) : _ptr(ptr) {}

	template<class T>
	inline T* UniquePtr<T>::Get() { return _ptr; }

}