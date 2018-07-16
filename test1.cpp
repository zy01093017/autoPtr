#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

#include"setdelete.hpp"


//c++11������ָ��
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


//��������shared_ptr���԰����Լ��������ռ��һ��չ���ͻ���ֳ�ͻ����֪����˭�ģ����Բ��ܹ���;
//���Ҫ�ã��Ͳ�Ҫ�������ռ�չ������ʹ��ʱ���������ռ伴��ʹ�ã��Ͳ��ڳ�ͻ
//
//void test_std_ptr()
//{
//	std::unique_ptr<AA> up1(new AA);//�൱��boost�е�scoped_ptr
//	//std::unique_ptr<AA> up2(up1);//������
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



//��ʱɾ����
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
	//std::unique_ptr<AA> up1(new AA);//�൱��boost�е�scoped_ptr
	////std::unique_ptr<AA> up2(up1);//������

	//std::shared_ptr<AA> sp1(new AA);
	//std::shared_ptr<AA> sp2(sp1);
	//cout << sp1.use_count() << endl;

	//if (sp1)
	//{
	//	cout << "�ǿ�ָ��" << endl;
	//}
	//else
	//{
	//	cout << "��ָ��" << endl;
	//}


	std::shared_ptr<AA> sp1(new AA[10],DeleteArray<AA>());//ʹ�÷º��������
	std::shared_ptr<AA> sp2((AA*)malloc(sizeof(AA)* 10),Free());//����һ����������
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
	Less<int> less;//ͨ�����������ú���
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