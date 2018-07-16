#pragma once


#include <iostream>
using namespace std;


//shared_ptr和以上二者的最大区别就是他维护了一个引用计数，
//用于检测当前对象所管理的指针是否还被其他智能指针使用（必须是shared_ptr管理的智能指针），
//在析构函数时对其引用计数减一，判断是否为0，若为0，则释放这个指针和这个引用计数的空间。
//其实，这个原理就和string类的浅拷贝是一样的。
//这个类型的智能指针在一定程度上让我们的管理得到了很大的便捷和省心。
//可以和其他共同管理这块空间的智能指针一起修改这块空间储存的值，达到“智能”的效果。
//
//template<class T>
//class SharedPtr
//{
//public:
//	SharedPtr(SharedPtr<T>* sp,int* spcount)
//		:_ptr(sp)
//		, _pCount(spcount)
//	{}
//
//	SharedPtr(const SharedPtr<T>& sp)
//	{
//		_ptr = sp._ptr;
//		_pCount = sp._pCount;
//		++(*pCount);
//	}
//
//	SharedPtr& opertaor=(const SharedPtr<T>& sp)
//	{
//		if (this != &sp)
//		{
//			if (--(*_pCount) == 0)
//			{
//				delete _ptr;
//				delete _pCount;
//			}
//			_ptr = sp._ptr;
//			_pCount = sp._pCount;
//			++(*pCount);
//		}
//		return *this;
//	}
//
//	~SharedPtr()
//	{
//		if (--(*pCount) == 0)
//		{
//			delete _ptr;
//			delete _pCount;
//		}
//	}
//private:
//
//	
//	T* _ptr;
//	int* _pCount;
//};


//void TestSharedPtr()
//{
//	SharedPtr<int> sp1(new int(10));
//	SharedPtr<int> sp2(sp1);
//
//	SharedPtr<int> sp3(new int(11));
//	sp1 = sp3;
//}






template<class T>
class WeakPtr;

template<class T>
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
				delete _ptr;
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



// 1.什么是循环引用？
// 2.如何解决？
struct ListNode
{
	WeakPtr<ListNode> _next;
	WeakPtr<ListNode> _prev;

	//ListNode()
	//	:_prev(NULL)
	//	,_next(NULL)
	//{}

	~ListNode()
	{
		cout << "delete ListNode" << endl;
	}
};

void TestSharePtrCycle()
{
	SharedPtr<ListNode> cur = new ListNode;//使用弱指针
	SharedPtr<ListNode> next = new ListNode;
	cur->_next = next;//weakptr接收的是sharedptr的对象
	next->_prev = cur;
}




//template<class T>
//class SharedArray
//{
//public:
//	~SharedArray()
//	{
//		delete[] _ptr;
//	}
//	operator[];
//};




