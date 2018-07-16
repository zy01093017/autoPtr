#pragma once

#include <iostream>
using namespace std;

//RAII:初始化时就获取到资源，构造时就把资源给他，结束后就将其析构
//像指针一样，重载了* ->


//智能指针是管理这个指针，并不是拥有

//autorPtr:管理权的转移

/*auto_ptr存在以下几个缺陷：
1>不要使用auto_ptr保存一个非动态开辟空间的指针，因为在作用域结束的时候，会执行智能指针的析构函数，释放这块空间，但非动态的空间又无法释放；
2>不要使用两个auto_ptr指针指向同一个指针
3>不要使用auto_ptr指向一个指针数组，因为auto_ptr的析构函数所用的是delete而不是delete[]，不匹配；
4>不要将auto_ptr储存在容器中，因为赋值和拷贝构造后原指针无法使用。
还有最重要的一点就是，什么情况下也别使用auto_ptr智能指针。*/

template<class T>
class AutorPtr
{
public:
	AutorPtr(T* ap)
	  :_Ptr(ap)
	{}

	AutorPtr(AutorPtr<T>& ap)//管理权的转移
	{
		_Ptr = ap._Ptr;
		ap._Ptr = NULL;
	}

	AutorPtr& operator= ( AutorPtr<T>& ap)
	{
		if (this != &ap)
		{
			_Ptr = ap._Ptr;//管理权进行转移，自己的指针置为空
			ap._Ptr = NULL;
		}
		return *this;
	}

	~AutorPtr()
	{
		printf("%p\n", _Ptr);
		delete _Ptr;
	}

	T& operator*()
	{
		return *_Ptr;
	}

	T* operator->()
	{
		return _Ptr;
	}
protected:

	T* _Ptr;
};

void TestAutorptr()
{
	AutorPtr<int> ap1(new int(10));
	AutorPtr<int> ap2 = ap1;
	//*ap1 = 100;//管理权已经转移，ap1管理的空间已经被ap2管理，所以导致空指针解引用
	*ap2 = 200;

	AutorPtr<int> ap3(new int(11));
	ap2 = ap3;
}

