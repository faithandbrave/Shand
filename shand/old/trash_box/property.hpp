#ifndef SHAND_PROPERTY_INCLUDE
#define SHAND_PROPERTY_INCLUDE

//----------------------------------------------------------------------//
// Name   : property, rproperty, wproperty, reproperty					//
// Desc   : プロパティ													//
// 元ネタ : N1615 C++ Properties -- a Library Solution					//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1615.pdf	//
//																		//
// Version : 1.00 2007/09/20 作成										//
//																		//
//				Programmed By Akira.T									//
//		Copyright(C) 2007 Akira.T All rights reserved					//
//																		//
//----------------------------------------------------------------------//


namespace shand {

template <class Type>
class property {
	Type data_;
public:
	property() : data_() {}

	Type operator()() const
	{
		return data_;
	}

	property operator() (const Type& value)
	{
		data_ = value;
		return *this;
	}

	Type& get() const
	{
		return data_;
	}

	property set(const Type& value)
	{
		data_ = value;
		return data_;
	}

	operator Type() const
	{
		return data_;
	}

	property operator=(const Type& value)
	{
		data_ = value;
		return *this;
	}

	typedef Type value_type;
};


// rproperty - read_only(get)
template <class Type, class Object, typename Type (Object::*Getter)() const>
class rproperty {
	Object *object_;
public:
	void operator()(Object* object)
	{
		object_ = object;
	}

	Type operator()() const
	{
		return get();
	}

	Type get() const
	{
		return (object_->*Getter)();
	}

	operator Type() const
	{
		return get();
	}

	typedef Type value_type;
};


// wproperty : write_only(set)
template <class Type, class Object, typename void (Object::*Setter) (const Type&)>
class wproperty {
	Object *object_;
public:
	void operator()(Object *object)
	{
		object_ = object;
	}

	void operator()(const Type& value)
	{
		return set(value);
	}

	void set(const Type& value)
	{
		(object_->*Setter)(value);
	}

	wproperty operator=(const Type& value)
	{
		set(value);
		return *this;
	}

	typedef Type value_type;
};


// rwproperty : read/write(get/set)
template <class Type, class Object,
		  typename Type (Object::*Getter)() const,
		  typename void (Object::*Setter)(const Type&)
		 >
class rwproperty {
	Object *object_;
public:
	void operator()(Object *object)
	{
		object_ = object;
	}

	Type operator()() const
	{
		return get();
	}

	void operator()(const Type& value)
	{
		set(value);
	}

	Type get() const
	{
		return (object_->*Getter)();
	}

	void set(const Type& value)
	{
		(object_->*Setter)(value);
	}

	operator Type() const
	{
		return get();
	}

	rwproperty operator=(const Type& value)
	{
		set(value);
		return *this;
	}

	typedef Type value_type;
};


} // namespace shand

#endif // SHAND_PROPERTY_INCLUDE

