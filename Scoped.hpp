#pragma once


//可以看见最大的不同就是scoped_ptr没有给出拷贝构造和赋值运算符的重载运算符的定义，
//只给了private下的声明，即表明scoped_ptr智能指针无法使用一个对象创建另一个对象，
//也无法采用赋值的形式。这无疑提升了智能指针的安全性，但是又存在无法“++”、“–”这些操作，
//当然也多了“*”、“->”这两种操作。所以这种形式也并不是最完美的。所以又有了shared_ptr。
template<typename T>
class ScopedPtr
{
public:
	explicit ScopedPtr(T *p = 0) 
		:mp(p)
	{}


	~ScopedPtr()
	{
		delete mp;
	}

	void reset(T *p = 0)//重置
	{
		if (mp != p)
		{
			delete mp;
			mp = p;
		}
	}

	T &operator*() const
	{
		if (mp != 0)
			return *mp;
		else
			throw std::runtime_error("the pointer is null");
	}

	T * operator->() const
	{
		if (mp != 0)
			return mp;
		else
			throw std::runtime_error("the pointer is null");
	}

	T *get() const
	{
		return mp;
	}
	void swap(ScopedPtr &rhs)
	{
		T *temp = mp;
		mp = rhs.mp;
		rhs.mp = temp;
	}
private:
	ScopedPtr(const ScopedPtr& rhs);
	ScopedPtr &operator=(const ScopedPtr& rhs);//防拷贝，只声明不实现
	T *mp;
};


void TestScopedPtr()
{
	ScopedPtr<int> sp1(new int(3));
	//ScopedPtr<int> sp2(sp1);//防拷贝，不能拷贝
}



template<class T>
class ScopedArray
{
public:
	ScopedArray(T* ptr)
		:_ptr(ptr)
	{}

	~ScopedArray()
	{
		printf("ptr:%p\n", _ptr);
		delete[] _ptr;//释放是delete[]
	}

	T& operator[](size_t index)//像数组一样
	{
		return _ptr[index];
	}

private:
	ScopedArray(const ScopedArray<T>&);
	ScopedArray<T>& operator=(const ScopedArray<T>&);

protected:
	T* _ptr;
};

void TestScopedArry()
{
	ScopedArray<int> sp1(new int[10]);
	sp1[5] = 10;
	//ScopedPtr<int> sp2(sp1);
}