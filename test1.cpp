#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

#include"setdelete.hpp"


//c++11的智能指针
#include <memory>

class AA
{
public:
	~AA()
	{
		cout << "~AA()" << endl;
	}

	int _a1;
	int _a2;
};


//由于两个shared_ptr各自包在自己的命名空间里，一旦展开就会出现冲突，不知道用谁的，所以不能共存;
//如果要用，就不要把命名空间展开，在使用时加上命名空间即可使用，就不在冲突
//
//void test_std_ptr()
//{
//	std::unique_ptr<AA> up1(new AA);//相当于boost中的scoped_ptr
//	//std::unique_ptr<AA> up2(up1);//防拷贝
//
//	std::shared_ptr<AA> sp1(new AA);
//	std::shared_ptr<AA> sp2(sp1);
//	cout << sp1.use_count() << endl;
//}
//
//#include<boost/shared_ptr.hpp>
//using namespace boost;
//void test_boost_prt()
//{
//	boost::shared_ptr<AA> sp1(new AA);
//	boost::shared_ptr<AA> sp2(sp1);
//	cout << sp1.use_count() << endl;
//}



//定时删除器
template<class T>
struct DeleteArray
{
	void operator()(T* ptr)
	{
		delete[] ptr;
	}
};

struct Free
{
	void operator()(void* ptr)
	{
		free(ptr);
	}
};

struct Fclose
{
	void operator()(FILE* ptr)
	{
		fclose(ptr);
	}
};


void test_std_ptr()
{
	//std::unique_ptr<AA> up1(new AA);//相当于boost中的scoped_ptr
	////std::unique_ptr<AA> up2(up1);//防拷贝

	//std::shared_ptr<AA> sp1(new AA);
	//std::shared_ptr<AA> sp2(sp1);
	//cout << sp1.use_count() << endl;

	//if (sp1)
	//{
	//	cout << "非空指针" << endl;
	//}
	//else
	//{
	//	cout << "空指针" << endl;
	//}


	std::shared_ptr<AA> sp1(new AA[10],DeleteArray<AA>());//使用仿函数来解决
	std::shared_ptr<AA> sp2((AA*)malloc(sizeof(AA)* 10),Free());//生成一个匿名对象
	std::shared_ptr<FILE> sp3(fopen("test.txt", "w"),Fclose());
}

#include<boost/shared_ptr.hpp>

void test_boost_prt()
{
	boost::shared_ptr<AA> sp1(new AA);
	boost::shared_ptr<AA> sp2(sp1);
	cout << sp1.use_count() << endl;
}



void TestLess()
{
	Less<int> less;//通过对象来调用函数
	cout << less(1, 2) << endl;
}

int main()
{
	/*test_std_ptr();
	test_boost_prt();*/

	//TestLess();
	
	system("pause");
	return 0;
}