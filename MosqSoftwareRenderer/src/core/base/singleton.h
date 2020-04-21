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
		//new��ʱ�����������û���Ĺ��캯��
		Singleton() {};
		virtual ~Singleton() {};
private:
		static T* _instance;
		Singleton(const Singleton&) {};
		void operator=(const Singleton&) {};
};


//��ͨ��ľ�̬��������Ҫ����cpp�ļ��У�ģ�������ж�����д��.h��
template<class T>
T* Singleton<T>::_instance = nullptr;

