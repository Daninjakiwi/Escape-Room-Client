#pragma once

template <class T>
class UniquePtr {
private:
	T* _ptr;
public:
	UniquePtr() : _ptr(nullptr) {};
	UniquePtr(T* ptr) : _ptr(ptr) {};
	~UniquePtr() { if (_ptr) { delete _ptr; } };

	void Init(T* ptr) { _ptr = ptr; };

	operator T* () const { return _ptr; };
};