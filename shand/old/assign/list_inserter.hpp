#ifndef SHAND_ASSIGN_LIST_INSERTER_INCLUDE
#define SHAND_ASSIGN_LIST_INSERTER_INCLUDE

namespace shand {

namespace assign_detail {

// push_backメンバ呼び出し用ファンクタ
template <class Container>
class call_push_back {
	Container& container_;
public:
	typedef Container container_type;

	call_push_back(Container& container)
		: container_(container) {}

	template <class Type>
	void operator()(Type value)
	{
		container_.push_back(value);
	}
};

// pushメンバ呼び出し用ファンクタ
template <class Container>
class call_push {
	Container& container_;
public:
	typedef Container container_type;

	call_push(Container& container)
		: container_(container) {}

	template <class Type>
	void operator()(Type value)
	{
		container_.push(value);
	}
};

// insertメンバ呼び出し用ファンクタ
template <class Container>
class call_insert {
	Container& container_;
public:
	typedef Container container_type;

	call_insert(Container& container)
		: container_(container) {}

	template <class Type>
	void operator()(Type value)
	{
		container_.insert(value);
	}
};

} // namespace shand::assign_detail


namespace assign {

template <class Inserter>
class list_inserter {
	Inserter inserter_;
public:
	list_inserter(typename Inserter::container_type& container)
		: inserter_(container) {}

	template <class Type>
	list_inserter& operator,(Type value)
	{
		inserter_(value);
		return *this;
	}

	template <class Type>
	list_inserter& operator()(Type value)
	{
		inserter_(value);
		return *this;
	}
};


template <class Container>
inline list_inserter<assign_detail::call_push_back<Container> >
push_back(Container& container)
{
	return list_inserter<assign_detail::call_push_back<Container> >(container);
}

template <class Container>
inline list_inserter<assign_detail::call_push<Container> >
push(Container& container)
{
	return list_inserter<assign_detail::call_push<Container> >(container);
}

template <class Container>
inline list_inserter<assign_detail::call_insert<Container> >
insert(Container& container)
{
	return list_inserter<assign_detail::call_insert<Container> >(container);
}

} // namespace shand::assign

} // namespace shand

#endif // SHAND_ASSIGN_LIST_INSERTER_INCLUDE

