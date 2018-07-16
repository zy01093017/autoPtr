
#pragma once

#include  <iostream>
using namespace std;

//定制删除器，与仿函数有关

//仿函数

// 仿函数--函数对象
//可以通过匿名对象去调函数，这个函数就是仿函数

//类中重载了()，我们可以通过对象去调函数
template<class T>
struct Less
{
	bool operator()(const T& a, const T& b)
	{
		return a < b;
	}
};

template<class T>
struct Del
{
	void operator()(T* ptr)
	{
		delete ptr;
	}
};
template<T>
struct DelArray
{
	operator()(T* ptr)
	{
		delete[] ptr;
	}
};



template<class T>
class WeakPtr;

template<class T, class D = Del<T>>//如果没有传就用缺省的
class SharedPtr
{
	friend class WeakPtr<T>;
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		, _pCount(new int(1))
	{}

	SharedPtr(const SharedPtr<T>& sp)
	{
		_ptr = sp._ptr;
		_pCount = sp._pCount;
		(*_pCount)++;
	}

	// sp1 = sp2;
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		if (this != &sp)
		{
			if (--(*_pCount) == 0)
			{
				delete _ptr;
				delete _pCount;
			}

			_pCount = sp._pCount;
			_ptr = sp._ptr;
			(*_pCount)++;
		}

		return *this;
	}

	~SharedPtr()
	{
		//cout<<"~SharedPtr()"<<endl;
		if (--(*_pCount) == 0)
		{
			if (_ptr)
			{
				printf("ptr:%p\n", _ptr);
				//delete _ptr;
				D del;//使用仿函数进行释放
				del(_ptr);
			}
			delete _pCount;
			

		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

protected:
	T* _ptr;
	int* _pCount;
};

// 专门解决SharedPtr的循环引用
// 弱指针是指当指针指向原来空间时，引用计数不在进行加1，释放时不在等待，故此解决了循环引用的问题
// 不是管理和释放当前的指针，而是避免了一次引用计数
template<class T>
class WeakPtr
{
public:
	WeakPtr(SharedPtr<T>& sp)//可以将sharedptr的对像传给他，匿名对象
		:_ptr(sp._ptr)		 //这里将sharedptr的对象给weakptr(弱指针)进行初始化，此时弱指针指向的是sharedptr的对象
	{}

	WeakPtr()
		:_ptr(NULL)
	{}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
protected:
	T* _ptr;
};