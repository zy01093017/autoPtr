#define _CRT_SECURE_NO_WARNINGS 1


#pragma once

//shared_ptr��Ҫ���м��������ڿ�ƽ̨��ÿ��ƽ̨�����ķ�ʽ����һ���������ṩ��shared_counted_base,�ṩ���࣬����ɼ̳У��μ�

#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <windows.h>
#include <mutex>
using namespace std;

mutex mtx;//ȫ�ֱ���
struct UnLock
{
	void operator()(mutex* ptr)
	{
		cout << "����" << endl;
		ptr->unlock();
	}
};

//void func(vector<int>* v)
//{
//	for (size_t i = 0; i < 10; ++i)
//	{
//		try
//		{
//			::Sleep(200);
//			mtx.lock();
//			shared_ptr<mutex> sp(&mtx, UnLock());
//
//			v->push_back(i);
//			cout << v->at(2) << endl;
//		}
//		catch (exception& e)
//		{
//			cout << e.what() << endl;
//		}
//	}
//}

class MutexGuard
{
public:
	MutexGuard(mutex& mtx)
		:_mtx(mtx)
	{
		cout << "����" << endl;
		_mtx.lock();
	}

	~MutexGuard()
	{
		// 
		cout << "����" << endl;
		_mtx.unlock();
	}

protected:
	mutex& _mtx;//��ʱ�൱�ڶ�һ�������г�ʼ��������̹߳���ͬһ����
};				//�����������õĳ����������������ܿ��������ÿһ���̶߳�����������һ��������ô�ڷ����ٽ���Դʱÿ���̶߳�Ӧ��������ͬһ���������ܻ���ķ�����Դ�����ǻ��������

void func(vector<int>* v)
{
	for (size_t i = 0; i < 10; ++i)
	{
		try
		{
			::Sleep(200);
			/*		mtx.lock();
			shared_ptr<mutex> sp(&mtx, UnLock());*/
			MutexGuard mg(mtx);//���캯������

			v->push_back(i);
			cout << v->at(2) << endl;
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
	}
}

void testRAII()
{
	vector<int> v;
	thread t1(func, &v);
	thread t2(func, &v);

	t1.join();
	t2.join();

	for (size_t i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

int main()
{
	try
	{
		testRAII();
	}
	catch (exception & e)
	{
		cout << e.what() << endl; // log
	}
	catch (...)
	{
		cout << "δ֪�쳣" << endl; // log
	}

	return 0;
}