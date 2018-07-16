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



//boost的引用
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>


#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/weak_ptr.hpp>


//侵入式指针，引用计数是自己管理
#include <boost/intrusive_ptr.hpp>