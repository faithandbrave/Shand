#ifndef SHAND_SHARED_POINTER_INCLUDE
#define SHAND_SHARED_POINTER_INCLUDE

//------------------------------------------------------------------//
//																	//
//	�N���X�� : shared_ptr<Type>										//
//	�p    �r : �Q�ƃJ�E���g�t���X�}�[�g�|�C���^						//
//																	//
// Version : 1.00 2007/06/22 �쐬									//
//			 1.10 2007/07/12 �J�X�^���폜�q���w��ł���悤�ɂ���	//
//			 1.11 2007/07/18 �J�X�^���폜�q�쐬���̗�O�����ǉ�		//
//							 shared_ptr<void>���쐬�ł���悤�ɂ���	//
//			 1.12 2007/10/25 �J�X�^���폜�q�̃|�C���^�̎������ύX	//
//			 1.13 2007/10/29 reset�ǉ�								//
//																	//
//				Programmed By Akira.T								//
//		Copyright(C) 2007 Akira.T All rights reserved				//
//------------------------------------------------------------------//

#include <functional> // less

namespace shand {

namespace detail {

// shared_ptr<void>���쐬���邽�߂ɎQ�ƌ^�쐬
template<class T> struct shared_ptr_traits
{
    typedef T& reference;
};

template<> struct shared_ptr_traits<void>
{
    typedef void reference;
};

#if !defined(_MSC_VER) || (_MSC_VER > 1300)  // 1300 == VC++ 7.0

template<> struct shared_ptr_traits<void const>
{
    typedef void reference;
};

template<> struct shared_ptr_traits<void volatile>
{
    typedef void reference;
};

template<> struct shared_ptr_traits<void const volatile>
{
    typedef void reference;
};

#endif

// �J�X�^���폜�q
template <typename Type>
class shared_deleter_base {
public:
	shared_deleter_base() {}
	virtual ~shared_deleter_base() {}
	virtual void destroy() = 0;
};

template <typename Type, typename Deleter>
class shared_deleter : public shared_deleter_base<Type> {
	Type*	object_;
	Deleter deleter_;
public:
	shared_deleter(Type *object, Deleter deleter)
		: object_(object), deleter_(deleter) {}

	virtual ~shared_deleter() {}

	virtual void destroy()
	{
		deleter_(object_);
	}
};

} // namespace detail


template <class Type>
class shared_ptr {
	Type*								object_;	// �|�C���^
	int*								counter_;	// �Q�ƃJ�E���^
	detail::shared_deleter_base<Type>*	deleter_;	// �J�X�^���폜�q

public:
	typedef Type element_type;
	typedef Type value_type;
	typedef Type* pointer;
	typedef typename detail::shared_ptr_traits<Type>::reference reference;

	shared_ptr()
		: object_(0), counter_(new int(1)), deleter_(0) {}

	shared_ptr(const shared_ptr& src)
		: object_(0), counter_(0), deleter_(0) { set(src); }

	explicit shared_ptr(Type* object)
		: object_(object), counter_(new int(1)), deleter_(0) {}

	// �폜�q�w��̃R���X�g���N�^
	template <class Deleter>
	shared_ptr(Type* object, Deleter deleter)
		: object_(object), counter_(new int(1)), deleter_(0)
	{
		try {
			deleter_ = new detail::shared_deleter<Type, Deleter>(object_, deleter);
		}
		catch(...) {
			deleter(object_);
			delete counter_;
			throw;
		}
	}

	~shared_ptr() { release(); }

	void reset()
	{
		release();
	}

	template <class Object>
	void reset(Object *object)
	{
		release();
		object_		= object;
		counter_	= new int(1);
		deleter_	= 0;
	}

	template <class Object, class Deleter>
	void reset(Object *object, Deleter deleter)
	{
		reset(object);

		try {
			deleter_ = new detail::shared_deleter<Type, Deleter>(object_, deleter);
		}
		catch(...) {
			deleter(object_);
			delete counter_;
			throw;
		}
	}

	// �|�C���^�̎擾
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

	shared_ptr& operator=(const shared_ptr& rhs) { set(rhs); return *this; }

	Type*     operator->() const { return get(); }
	reference operator*()  const { return *get(); }
	bool      operator!()  const { return object_ == 0; }

	operator bool() const { return object_ != 0; }

private:
	void set(const shared_ptr& src)
	{
		if (this != &src) {
			// ������ĐV�����X�}�[�g�|�C���^���쐬
			release();
			object_  = src.object_;
			counter_ = src.counter_;
			deleter_ = src.deleter_;

			// �Q�ƃJ�E���g�𑝂₷
			if (counter_ != 0)
				++*counter_;
		}
	}

	void release()
	{
		if (counter_ != 0 && --*counter_ == 0) {
			if (deleter_) {
				deleter_->destroy();
				delete deleter_;
			}
			else {
				delete object_;
			}
			delete counter_;
		}
		object_ = 0;
		counter_ = 0;
		deleter_ = 0;
	}

};

template<class Type>
inline bool operator==(shared_ptr<Type> const & lhs, shared_ptr<Type> const & rhs)
{
    return lhs.get() == rhs.get();
}

template<class Type>
inline bool operator!=(shared_ptr<Type> const & lhs, shared_ptr<Type> const & rhs)
{
    return lhs.get() != rhs.get();
}

// map�i�[�p
template<class Type>
inline bool operator<(shared_ptr<Type> const & lhs, shared_ptr<Type> const & rhs)
{
    return std::less<Type*>()(lhs.get(), rhs.get());
}


} // namespace shand

#endif // SHAND_SHARED_POINTER_INCLUDE

