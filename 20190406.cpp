// 20190403.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>

#include <stack> // 用模板实现的栈
#include <queue> // 用模板实现的队列结构
#include <string>
using namespace std;

/*
C++ STL六大组件
容器 vector
`
迭代器 ： 
你觉得迭代器是干什么用得？泛型算法为什么都要接收迭代器作为参数？
迭代器 =》 迭代 =》 容器的

数组  链表  哈希表  树
p++   p = p->next  

迭代器遍历所有容器的方式都是一模一样的！！！！
*/



template < typename T > 
struct myallocator
{
	// 内存开辟
	T* allocate(size_t size)
	{
		return (T*)malloc(size * sizeof(T));
	}

	// 内存释放
	void deallocate(T *ptr)
	{
		free(ptr);
	}

	// 对象构造 1.new 2.new const 3.定位new
	void construct(T *ptr, const T &obj)
	{
		new (ptr) T(obj); // 定位new
	}

	// 对象析构
	void destroy(T *ptr)
	{
		ptr->~T();
	}
};

// 类模板 vector 默认构造 size:0-1-2-4-8-16-32-64....
template<typename T = int,
	typename _Alloc = myallocator<T>>
	class Vector // 类的模板名字
{
public:
	Vector() :mcur(-1)
		, msize(0)
		, mpvec(nullptr)
	{

	}
	~Vector()
	{
		for (int i = 0; i <= mcur; ++i)
		{
			// 析构容器中有效的对象
			malloctor.destroy(mpvec + i);
		}
		// 把容器内存释放掉
		malloctor.deallocate(mpvec);
		mpvec = nullptr;
	}
	Vector(const Vector<T> &vec)
	{
		msize = vec.msize;//空间大小
		mcur = vec.mcur;//现在存的元素个数
		mpvec = malloctor.allocate(msize);
		for (int i = 0; i <= mcur; i++)
		{
			malloctor.construct(mpvec + i, vec.mpvec[i]);
		}
	}
	Vector(Vector<T> &&vec)
	{
		mpvec = vec.mpvec;
		vec.mpvec = nullptr;
		mcur = vec.mcur;
		msize = vec.msize;
	}
	void operator=(const Vector<T> &vec)
	{
		if (this == &vec)
		{
			return;
		}
		for (int i = 0; i <= mcur; i++)
		{
			malloctor.destory(mpvec + i);
		}
		malloctor.deallocate(mpvec);

		msize = vec.msize;//空间大小
		mcur = vec.mcur;//现在存的元素个数

		mpvec = malloctor.allocate(msize);
		for (int i = 0; i <= mcur; i++)
		{
			malloctor.construt(mpvec + i, vec.mpvec[i]);
		}
	}
	void operator=(Vector<T> &&vec)
	{
		if (this == &vec)
		{
			return;
		}
		for (int i = 0; i <= mcur; i++)
		{
			malloctor.destory(mpvec + i);
		}
		malloc.deallocate(mpvec);

		msize = vec.msize;
		mcur = vec.mcur;
		mpvec = vec.mpvec;
		vec.mpvec = nullptr;
	}

	void reserve(int size) // 预留函数
	{
		if (size <= msize)
			return;
		T* ptmp = malloctor.allocate(size);
		for (int i = 0; i <= mcur; ++i)
		{
			malloctor.construct(ptmp + i, mpvec[i]);
		}
		for (int i = 0; i <= mcur; i++)
		{
			malloctor.destroy(mpvec + i);
		}
		malloctor.deallocate(mpvec);
		mpvec = ptmp;
		msize = size;
	}

	void push_back(const T &val) // 末尾添加元素
	{
		if (full())
		{
			resize();
		}
		mcur++;
		malloctor.construct(mpvec + mcur, val);
	}
	void pop_back() // 末尾删除元素
	{
		if (empty())
		{
			return;
		}
		malloctor.destroy(mpvec + mcur);
		mcur--;
	}

	bool empty()const // 判空
	{
		return mcur == -1;
	}
	bool full()const // 判满
	{
		return mcur == msize - 1;
	}
	int size()const // 返回vector容器元素的个数
	{
		return mcur + 1;
	}

	void show()const // 打印vector容器的所有元素
	{
		for (int i = 0; i <= mcur; i++)
		{
			cout << mpvec[i] << " ";
		}
		cout << endl;
	}
	
	// 作业，给当前Vector容器提供下面的实现
	// 1。提供迭代器的实现
	class myiterator
	{
	public:
		// iterator()  operator!=   operator++() operator*
		myiterator(T *p = nullptr) :_ptr(p) {}
		bool operator!=(const myiterator &it)
		{
			return _ptr != it._ptr;
		}
		bool operator==(const myiterator &it)
		{
			return _ptr == it._ptr;
		}
		void operator++() { _ptr++; }
		void operator--() { _ptr--; }
		T& operator*() { return *_ptr; }
		// char a =
	private:
		T *_ptr;
	};
	// 容器的begin和end方法，分别返回
	myiterator begin() { return myiterator(mpvec); }
	myiterator where(int a) 
	{ 
		if (full())
		{
			resize();
		}

			return myiterator(mpvec+a-1);
	
	}
	myiterator end() { return myiterator(mpvec +mcur+1); }

	// 2.提供insert插入函数
	/*myiterator insert(myiterator &where, const T &val)
	{
			

			if (n == 0)return;

		malloctor.construct(mpvec+mcur+1,NULL);
		
	    int a = mcur+1;
		int b = mcur;
		myiterator it  = end();
		if (it == where)
		{
			mpvec[a] = val;
			mcur++;
			return it;
		}
		
		while (it !=where)
		{	
			mpvec[a] = mpvec[b];
			
			it--;
			a--;
			b--;
		}
		mpvec[a] = val;
		mcur++;
		return it;

	}*/
	myiterator insert(myiterator &where, const T &val)
	{


		malloctor.construct(mpvec + mcur + 1, NULL);

		myiterator it1 = end();
		it1--;
		myiterator it = end();
		if (it == where)
		{
			*it = val;
			mcur++;
			return it;
		}


		while (it != where)
		{
		
			copy(it1, it);
			it--;
			it1--;
			
		}
		*it = val;
		mcur++;
		return it;

	} 
	void copy(myiterator from_pos, myiterator from_end)
	{

		*from_end = *from_pos;
		
		
	}

	/*myiterator remove(myiterator &where)
	{
		int i =0;
		myiterator it = begin();
		while (it != where)
		{
		++i;
		++it;
		}
		while (it != end())
		{
			mpvec[i] = mpvec[i + 1];
			i++;
			it++;
		}
		mcur--;
		return it;
	}*/
	myiterator remove(myiterator &where)
	{
	
		myiterator it = begin();
		while (it != where)
		{
		
			++it;
		}
		
		myiterator  it1 =it;
		it1++;
		while (it != end())
		{
			copy(it1, it);
			it1++;
			it++;
		}
		mcur--;
		return it;
	}

 
	// 4.提供operator    vec[2];

 T operator [](const int a)
	{
		return mpvec[a];
	}

	friend istream & operator >>(istream& i, const Vector<T> &src);
	friend istream & operator >>(istream& i, const Vector<T> &src)
	{
		cin >> src.mpvec >> endl;

		return i;
	}
	friend ostream & operator<<(ostream& out, const Vector<T> &src);
	friend ostream & operator<<(ostream& out, const Vector<T> &src)
	{
		
		out << src.mpvec << endl;
		return out;
	}

private:
	T *mpvec;
	int mcur;
	int msize;
	_Alloc malloctor; // 定义空间配置器对象 

	void resize() // vector容器底层默认2倍扩容
	{
		if (msize > 0)
		{
			T *ptmp = malloctor.allocate(msize * 2);
			for (int i = 0; i < msize; i++)
			{
				malloctor.construct(ptmp + i, mpvec[i]);
				// 析构容器中有效的对象
				malloctor.destroy(mpvec + i);
			}
			// 把容器内存释放掉
			malloctor.deallocate(mpvec);
			mpvec = ptmp;
			msize *= 2;
		}
		else
		{
			mpvec = malloctor.allocate(1); // size * sizeof(T)
			msize = 1;
			mcur = -1;
		}
	}
	};


	int main()
	{
		Vector<int> vec;
		vec.push_back(10);
		vec.push_back(20);
		vec.push_back(30);
		vec.push_back(40);
		cout << vec[6] << endl;
		//vec.insert(vec.where(5),100);
		
		//vec.remove(vec.where(1));
		
		return 0;
	}