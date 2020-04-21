#pragma once

template<class T>
class Singleton {
public:
		static T* getInstance() {
				if (_instance == nullptr) {
						_instance = new T();
				}
				return _instance;
		}
		virtual void init() = 0;
		virtual void dispose() = 0;
protected:
		//new的时候派生类会调用基类的构造函数
		Singleton() {};
		virtual ~Singleton() {};
private:
		static T* _instance;
		Singleton(const Singleton&) {};
		void operator=(const Singleton&) {};
};


//普通类的静态变量必须要放在cpp文件中，模板类所有东西都写在.h中
template<class T>
T* Singleton<T>::_instance = nullptr;

