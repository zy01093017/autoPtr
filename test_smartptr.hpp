#pragma once

#include <iostream>
using namespace std;
#include<memory>
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



//boost������
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>


#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/weak_ptr.hpp>


//����ʽָ�룬���ü������Լ�����
#include <boost/intrusive_ptr.hpp>