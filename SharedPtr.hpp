#pragma once


#include <iostream>
using namespace std;


//shared_ptr�����϶��ߵ�������������ά����һ�����ü�����
//���ڼ�⵱ǰ�����������ָ���Ƿ񻹱���������ָ��ʹ�ã�������shared_ptr���������ָ�룩��
//����������ʱ�������ü�����һ���ж��Ƿ�Ϊ0����Ϊ0�����ͷ����ָ���������ü����Ŀռ䡣
//��ʵ�����ԭ��ͺ�string���ǳ������һ���ġ�
//������͵�����ָ����һ���̶��������ǵĹ���õ��˺ܴ�ı�ݺ�ʡ�ġ�
//���Ժ�������ͬ�������ռ������ָ��һ���޸����ռ䴢���ֵ���ﵽ�����ܡ���Ч����
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

// ר�Ž��SharedPtr��ѭ������
// ��ָ����ָ��ָ��ָ��ԭ���ռ�ʱ�����ü������ڽ��м�1���ͷ�ʱ���ڵȴ����ʴ˽����ѭ�����õ�����
// ���ǹ�����ͷŵ�ǰ��ָ�룬���Ǳ�����һ�����ü���
template<class T>
class WeakPtr
{
public:
	WeakPtr(SharedPtr<T>& sp)//���Խ�sharedptr�Ķ��񴫸�������������
		:_ptr(sp._ptr)		 //���ｫsharedptr�Ķ����weakptr(��ָ��)���г�ʼ������ʱ��ָ��ָ�����sharedptr�Ķ���
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



// 1.ʲô��ѭ�����ã�
// 2.��ν����
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
	SharedPtr<ListNode> cur = new ListNode;//ʹ����ָ��
	SharedPtr<ListNode> next = new ListNode;
	cur->_next = next;//weakptr���յ���sharedptr�Ķ���
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




