#pragma once


//���Կ������Ĳ�ͬ����scoped_ptrû�и�����������͸�ֵ�����������������Ķ��壬
//ֻ����private�µ�������������scoped_ptr����ָ���޷�ʹ��һ�����󴴽���һ������
//Ҳ�޷����ø�ֵ����ʽ������������������ָ��İ�ȫ�ԣ������ִ����޷���++�������C����Щ������
//��ȻҲ���ˡ�*������->�������ֲ���������������ʽҲ�������������ġ�����������shared_ptr��
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

	void reset(T *p = 0)//����
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
	ScopedPtr &operator=(const ScopedPtr& rhs);//��������ֻ������ʵ��
	T *mp;
};


void TestScopedPtr()
{
	ScopedPtr<int> sp1(new int(3));
	//ScopedPtr<int> sp2(sp1);//�����������ܿ���
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
		delete[] _ptr;//�ͷ���delete[]
	}

	T& operator[](size_t index)//������һ��
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