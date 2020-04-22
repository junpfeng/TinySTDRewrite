#ifndef __SHARED_PTR_
#define __SHARED_PTR_
#include<iostream>

template<typename T>
class shared_ptr {
	T * instance;
	int * ref;
public:
	shared_ptr() :instance(nullptr) {
		ref = new int;
		*ref = 0;
	}
	shared_ptr(T * inst) :instance(inst) {
		std::cout << "shared_ptr" << std::endl;
		ref = new int;
		*ref = 1;
	}
	// 复制构造,
	shared_ptr(const shared_ptr & sptr) {
		// 复制构造，不需要清空当前对象，因为只有空的时候才会调用复制构造
		std::cout << "cp_shared_ptr" << std::endl;
		this->ref = sptr.ref;
		this->instance = sptr.instance;
		sptr.ref++;
	}
	// 重载 = 
	const shared_ptr & operator=(const shared_ptr & sptr) {
		// 先判断是不是同一个
		if (sptr.instance == this->instance) {
			return *this;
		}
		// 再释放当前的对象，引用计数 - 1
		if (0 != *(this->ref)) {
			--(*ref);
			// 如果引用计数 == 0，就释放资源
			if (0 == *(this->ref)) {
				delete this->ref;
				this->ref = nullptr;
				delete this->instance;
				this->instance = nullptr;
			}
		}
		// 增加被赋值的对象的引用计数 + 1
		this->instance = sptr.instance;
		this->ref = sptr.ref;
		++(*(this->ref));
		return *this;
	}

	// 重载 ->，语义转换为指针
	T * operator->() {
		return this->instance;
	}

	// 重载 *，取内容
	T & operator *() {
		return *(this->instance);
	}

	// 析构构造
	// 如何区分 复杂类型 的析构呢？？？？
	virtual ~shared_ptr() {
		std::cout << "~shared_ptr" << std::endl;
		--*(this->ref);
		if (*(this->ref) != 0)
			return;
		else {
			if (nullptr != instance) {
				delete instance;
				instance = nullptr;
			}
			if (nullptr != ref) {
				delete ref;
				ref = nullptr;
			}
		}
	}
};

#endif