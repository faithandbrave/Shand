#ifndef SHAND_SHARED_ARRAY_INCLUDE
#define SHAND_SHARED_ARRAY_INCLUDE

//----------------------------------------------------------//
//															//
//	�N���X�� : shared_array<Type>							//
//	�p    �r : �Q�ƃJ�E���g�t���X�}�[�g�|�C���^�̔z���		//
//															//
// Version : 1.00 2007/06/22 �쐬							//
//															//
//				Programmed By Akira.T						//
//		Copyright(C) 2007 Akira.T All rights reserved		//
//----------------------------------------------------------//


#include <functional> // less

namespace shand {

template <class Type>
class shared_array {
	Type*	object_;	// ���̃|�C���^
	int*	counter_;	// �Q�ƃJ�E���^

public:
	typedef Type element_type;
	typedef Type value_type;
	typedef Type* pointer;

	shared_array()
		: object_(0), counter_(0) {}

	shared_array(const shared_array& src)
		: object_(0), counter_(0) { set(src); }

	explicit shared_array(Type* object)
		: object_(object), counter_(new int(1)) {}

	~shared_array() { release(); }

	// �|�C���^�擾
	Type* get() const { return object_; }

	// �Q�ƃJ�E���g�擾
	long use_count() const
	{
		if (!counter_)
			return 0;
		return *counter_;
	}

	// �Q�Ɛ悪1�����f
	bool unique() const { return use_count() == 1; }

	shared_array& operator=(const shared_array& rhs) { set(rhs); return *this; }

	Type& operator[](int index) const
	{
		return object_[index];
	}

	bool operator!() const { return object_ == 0; }

	operator bool() const { return object_ != 0; }

private:
	void set(const shared_array& src)
	{
		if (this != &src) {
			release();
			object_  = src.object_;
			counter_ = src.counter_;

			if (counter_ != 0)
				++*counter_;
		}
	}

	void release()
	{
		// �Q�ƃJ�E���^�����炷
		if (counter_ != 0 && --*counter_ == 0) {
			delete[] object_;
			delete   counter_;
		}
		object_  = 0;
		counter_ = 0;
	}
};

template<class Type>
inline bool operator==(shared_array<Type> const & lhs, shared_array<Type> const & rhs)
{
    return lhs.get() == rhs.get();
}

template<class Type>
inline bool operator!=(shared_array<Type> const & lhs, shared_array<Type> const & rhs)
{
    return lhs.get() != rhs.get();
}

template<class Type>
inline bool operator<(shared_array<Type> const & lhs, shared_array<Type> const & rhs)
{
    return std::less<Type*>()(lhs.get(), rhs.get());
}


} // namespace shand

#endif // SHAND_SHARED_ARRAY_INCLUDE

