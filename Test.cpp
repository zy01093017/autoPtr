#include "AutorPtr.hpp"
#include "Scoped.hpp"
#include "SharedPtr.hpp"
#include "test_smartptr.hpp"


void test_auto_ptr()
{
	auto_ptr<AA> ap1(new AA);
	auto_ptr<AA> ap2(ap1);
	//ap2->_a1 = 10;
	//ap1->_a1  = 20;管理权地转移，空指针
}

void Test_scoped_ptr()
{
	boost::scoped_ptr<AA> sp1(new AA);
	//boost::scoped_ptr<AA> sp2(sp1);//防拷贝
	boost::scoped_array<AA> sp3(new AA[10]);
	sp3[3]._a1 = 10;


}


struct Node
{
	boost::weak_ptr<Node> _next;
	boost::weak_ptr<Node> _prev;

	~Node()
	{
		cout << "~Node()" << endl;
	}
};


void test_shared_ptr()
{
	boost::shared_ptr<AA> sp1(new AA);
	boost::shared_ptr<AA> sp2(sp1);
	cout << sp1.use_count() << endl;//查看引用计数

	boost::shared_ptr<Node> node1(new Node);//循环引用的问题
	boost::shared_ptr<Node> node2(new Node);
	node1->_next = node2;
	node2->_prev = node1;


}


//int main()
//{
//	//TestAutorptr();
//	//TestScopedPtr();
//	//TestScopedArry();
//	//TestSharePtrCycle();
//	//test_auto_ptr();
//	//Test_scoped_ptr();
//	test_shared_ptr();
//	system("pause");
//	return  0;
//}