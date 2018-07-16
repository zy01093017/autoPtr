#define _CRT_SECURE_NO_WARNINGS 1


#pragma once

//shared_ptr需要进行加锁，由于跨平台，每个平台加锁的方式都不一样，所以提供了shared_counted_base,提供基类，子类可继承，课件

#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <windows.h>
#include <mutex>
using namespace std;

mutex mtx;//全局变量
struct UnLock
{
	void operator()(mutex* ptr)
	{
		cout << "解锁" << endl;
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
		cout << "加锁" << endl;
		_mtx.lock();
	}

	~MutexGuard()
	{
		// 
		cout << "解锁" << endl;
		_mtx.unlock();
	}

protected:
	mutex& _mtx;//此时相当于对一个锁进行初始化，多个线程共用同一个锁
};				//类里面用引用的场景，防拷贝，不能拷贝，如果每一个线程都来拷贝构造一个锁，那么在访问临界资源时每个线程对应的锁不是同一个锁，不能互斥的访问资源，还是会造成死锁

void func(vector<int>* v)
{
	for (size_t i = 0; i < 10; ++i)
	{
		try
		{
			::Sleep(200);
			/*		mtx.lock();
			shared_ptr<mutex> sp(&mtx, UnLock());*/
			MutexGuard mg(mtx);//构造函数加锁

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
		cout << "未知异常" << endl; // log
	}

	return 0;
}