
#pragma once

#include  <iostream>
using namespace std;

//����ɾ��������º����й�

//�º���

// �º���--��������
//����ͨ����������ȥ������������������Ƿº���

//����������()�����ǿ���ͨ������ȥ������
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

template<class T, class D = Del<T>>//���û�д�����ȱʡ��
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
				D del;//ʹ�÷º��������ͷ�
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