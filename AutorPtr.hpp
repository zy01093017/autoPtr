#pragma once

#include <iostream>
using namespace std;

//RAII:��ʼ��ʱ�ͻ�ȡ����Դ������ʱ�Ͱ���Դ������������ͽ�������
//��ָ��һ����������* ->


//����ָ���ǹ������ָ�룬������ӵ��

//autorPtr:����Ȩ��ת��

/*auto_ptr�������¼���ȱ�ݣ�
1>��Ҫʹ��auto_ptr����һ���Ƕ�̬���ٿռ��ָ�룬��Ϊ�������������ʱ�򣬻�ִ������ָ��������������ͷ����ռ䣬���Ƕ�̬�Ŀռ����޷��ͷţ�
2>��Ҫʹ������auto_ptrָ��ָ��ͬһ��ָ��
3>��Ҫʹ��auto_ptrָ��һ��ָ�����飬��Ϊauto_ptr�������������õ���delete������delete[]����ƥ�䣻
4>��Ҫ��auto_ptr�����������У���Ϊ��ֵ�Ϳ��������ԭָ���޷�ʹ�á�
��������Ҫ��һ����ǣ�ʲô�����Ҳ��ʹ��auto_ptr����ָ�롣*/

template<class T>
class AutorPtr
{
public:
	AutorPtr(T* ap)
	  :_Ptr(ap)
	{}

	AutorPtr(AutorPtr<T>& ap)//����Ȩ��ת��
	{
		_Ptr = ap._Ptr;
		ap._Ptr = NULL;
	}

	AutorPtr& operator= ( AutorPtr<T>& ap)
	{
		if (this != &ap)
		{
			_Ptr = ap._Ptr;//����Ȩ����ת�ƣ��Լ���ָ����Ϊ��
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
	//*ap1 = 100;//����Ȩ�Ѿ�ת�ƣ�ap1����Ŀռ��Ѿ���ap2�������Ե��¿�ָ�������
	*ap2 = 200;

	AutorPtr<int> ap3(new int(11));
	ap2 = ap3;
}

