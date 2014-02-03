#ifndef SHAND_FUNCTION_INCLUDE
#define SHAND_FUNCTION_INCLUDE

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//----------------------------------------------------------//
// Name : function<R (T0, T1...T9)>							//
// Desc : 汎用関数オブジェクト								//
//		  関数のようなものならなんでも処理するクラス		//
//															//
// Version : 0.90 2007/10/30 作成							//
//			 1.00 2007/10/31 メンバ関数ポインタに対応		//
//															//
//----------------------------------------------------------//

#include <functional> // mem_fun

#define SHAND_TEMPLATE_PARAMS_1	class T0
#define SHAND_TEMPLATE_PARAMS_2	class T0, class T1
#define SHAND_TEMPLATE_PARAMS_3	class T0, class T1, class T2
#define SHAND_TEMPLATE_PARAMS_4	class T0, class T1, class T2, class T3
#define SHAND_TEMPLATE_PARAMS_5	class T0, class T1, class T2, class T3, class T4
#define SHAND_TEMPLATE_PARAMS_6	class T0, class T1, class T2, class T3, class T4, class T5
#define SHAND_TEMPLATE_PARAMS_7	class T0, class T1, class T2, class T3, class T4, class T5, class T6
#define SHAND_TEMPLATE_PARAMS_8	class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7
#define SHAND_TEMPLATE_PARAMS_9	class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8
#define SHAND_TEMPLATE_PARAMS_10 class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9

#define SHAND_TEMPLATE_ARGS_1	T0
#define SHAND_TEMPLATE_ARGS_2	T0, T1
#define SHAND_TEMPLATE_ARGS_3	T0, T1, T2
#define SHAND_TEMPLATE_ARGS_4	T0, T1, T2, T3
#define SHAND_TEMPLATE_ARGS_5	T0, T1, T2, T3, T4
#define SHAND_TEMPLATE_ARGS_6	T0, T1, T2, T3, T4, T5
#define SHAND_TEMPLATE_ARGS_7	T0, T1, T2, T3, T4, T5, T6
#define SHAND_TEMPLATE_ARGS_8	T0, T1, T2, T3, T4, T5, T6, T7
#define SHAND_TEMPLATE_ARGS_9	T0, T1, T2, T3, T4, T5, T6, T7, T8
#define SHAND_TEMPLATE_ARGS_10	T0, T1, T2, T3, T4, T5, T6, T7, T8, T9

#define SHAND_FUNCTION_PARAMS_1	T0 t0
#define SHAND_FUNCTION_PARAMS_2	T0 t0, T1 t1
#define SHAND_FUNCTION_PARAMS_3	T0 t0, T1 t1, T2 t2
#define SHAND_FUNCTION_PARAMS_4	T0 t0, T1 t1, T2 t2, T3 t3
#define SHAND_FUNCTION_PARAMS_5	T0 t0, T1 t1, T2 t2, T3 t3, T4 t4
#define SHAND_FUNCTION_PARAMS_6	T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5
#define SHAND_FUNCTION_PARAMS_7	T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6
#define SHAND_FUNCTION_PARAMS_8	T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7
#define SHAND_FUNCTION_PARAMS_9	T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8
#define SHAND_FUNCTION_PARAMS_10 T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9

#define SHAND_FUNCTION_ARGS_1	t0
#define SHAND_FUNCTION_ARGS_2	t0, t1
#define SHAND_FUNCTION_ARGS_3	t0, t1, t2
#define SHAND_FUNCTION_ARGS_4	t0, t1, t2, t3
#define SHAND_FUNCTION_ARGS_5	t0, t1, t2, t3, t4
#define SHAND_FUNCTION_ARGS_6	t0, t1, t2, t3, t4, t5
#define SHAND_FUNCTION_ARGS_7	t0, t1, t2, t3, t4, t5, t6
#define SHAND_FUNCTION_ARGS_8	t0, t1, t2, t3, t4, t5, t6, t7
#define SHAND_FUNCTION_ARGS_9	t0, t1, t2, t3, t4, t5, t6, t7, t8
#define SHAND_FUNCTION_ARGS_10	t0, t1, t2, t3, t4, t5, t6, t7, t8, t9


#define SHAND_FUNCTION_MANAGER_N(Count) \
template <class FunctionPtr, class R, SHAND_TEMPLATE_PARAMS_##Count##>					\
struct function_ptr_manager##Count## {													\
	static R invoke(any_pointer function_ptr, SHAND_FUNCTION_PARAMS_##Count##)			\
	{																					\
		FunctionPtr func = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);		\
		return func(SHAND_FUNCTION_ARGS_##Count##);										\
	}																					\
																						\
	static void destroy(any_pointer)													\
	{																					\
	}																					\
};																						\
																						\
template <class FunctionObj, class R, SHAND_TEMPLATE_PARAMS_##Count##>					\
struct function_obj_manager##Count## {													\
	static R invoke(any_pointer function_obj_ptr, SHAND_FUNCTION_PARAMS_##Count##)		\
	{																					\
		FunctionObj* func = reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);	\
		return (*func)(SHAND_FUNCTION_ARGS_##Count##);									\
	}																					\
																						\
	static void destroy(any_pointer function_obj_ptr)									\
	{																					\
		FunctionObj* func = reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);	\
		delete func;																	\
	}																					\
};


#define SHAND_FUNCTION_CLASS_N(Count)	\
template <class R, SHAND_TEMPLATE_PARAMS_##Count##>									\
class function<R (SHAND_TEMPLATE_ARGS_##Count##)>									\
	: public function_detail::function_base<R (SHAND_TEMPLATE_ARGS_##Count##)> {	\
public:																				\
	typedef R result_type;															\
																					\
	result_type (*invoke_)(any_pointer, SHAND_TEMPLATE_ARGS_##Count##);				\
																					\
	function()																		\
		: function_base()															\
	{																				\
		invoke_ = 0;																\
	}																				\
																					\
	function(const function& func)													\
	{																				\
		assign_to_own(func);														\
	}																				\
																					\
	template <class FuncType>														\
	function(FuncType func)															\
	{																				\
		assign_to(func);															\
	}																				\
																					\
	function& operator=(const function& func)										\
	{																				\
		if (&func == this)															\
			return *this;															\
																					\
		assign_to_own(func);														\
		return *this;																\
	}																				\
																					\
	template <class FuncType>														\
	function& operator=(FuncType func)												\
	{																				\
		clear();																	\
		assign_to(func);															\
		return *this;																\
	}																				\
																					\
	result_type operator()(SHAND_FUNCTION_PARAMS_##Count##) const					\
	{																				\
		return invoke_(functor_, SHAND_FUNCTION_ARGS_##Count##);					\
	}																				\
																					\
	void clear()																	\
	{																				\
		if (!empty()) {																\
			destroy_(functor_);														\
																					\
			invoke_		= 0;														\
			destroy_	= 0;														\
		}																			\
	}																				\
																					\
	bool empty() const																\
	{																				\
		return !(invoke_ && destroy_);												\
	}																				\
																					\
	operator bool()																	\
	{																				\
		return !empty();															\
	}																				\
																					\
	bool operator!()																\
	{																				\
		return empty();																\
	}																				\
																					\
private:																			\
	template <class FuncType>														\
	void assign_to(FuncType func)													\
	{																				\
		typedef typename function_detail::get_function_tag<FuncType>::type tag;		\
		assign_to(func, tag());														\
	}																				\
																					\
	template <class FunctionPtr>													\
	void assign_to(FunctionPtr func, function_ptr_tag)								\
	{																				\
		typedef																		\
			function_detail::function_ptr_manager##Count##<FunctionPtr, R, SHAND_TEMPLATE_ARGS_##Count##>	\
		actual_manager;																\
																					\
		invoke_ = &actual_manager::invoke;											\
		destroy_ = &actual_manager::destroy;										\
																					\
		functor_.func_ptr = reinterpret_cast<void (*)()>(func);						\
	}																				\
																					\
	template <class FunctionObj>													\
	void assign_to(FunctionObj func, function_obj_tag)								\
	{																				\
		typedef																		\
			function_detail::function_obj_manager##Count##<FunctionObj, R, SHAND_TEMPLATE_ARGS_##Count##>	\
		actual_manager;																\
																					\
		invoke_ = &actual_manager::invoke;											\
		destroy_ = &actual_manager::destroy;										\
																					\
		FunctionObj* new_func = new FunctionObj(func);								\
		functor_.obj_ptr = static_cast<void*>(new_func);							\
	}																				\
																					\
	template <class MemberPtr>														\
	void assign_to(MemberPtr func, member_ptr_tag)									\
	{																				\
		assign_to(mem_fun(func));													\
	}																				\
																					\
	void assign_to_own(const function& func)										\
	{																				\
		clear();																	\
		invoke_		= func.invoke_;													\
		destroy_	= func.destroy_;												\
		functor_	= func.functor_;												\
	}																				\
};



namespace shand {

namespace function_detail {

namespace shand_work {
	// if_c
	template <bool Cond, class Then, class Else>
	struct if_c;

	template <class Then, class Else>
	struct if_c<true, Then, Else> {
		typedef Then type;
	};

	template <class Then, class Else>
	struct if_c<false, Then, Else> {
		typedef Else type;
	};


	// if_
	template <class Cond, class Then, class Else>
	struct if_ {
		typedef typename if_c<Cond::value, Then, Else>::type type;
	};

	// is_pointer
	template <class Type>
	struct is_pointer {
		static const bool value = false;
	};

	template <class Type>
	struct is_pointer<Type*> {
		static const bool value = true;
	};

	// is_member_pointer
	template <class Type>
	struct is_member_pointer {
		static const bool value = false;
	};

	template <class Type, class ClassName>
	struct is_member_pointer<Type ClassName::*> {
		static const bool value = true;
	};

	template <class Type, class ClassName>
	struct is_member_pointer<Type ClassName::* const> {
		static const bool value = true;
	};

	template <class Type, class ClassName>
	struct is_member_pointer<Type ClassName::* volatile> {
		static const bool value = true;
	};

	template <class Type, class ClassName>
	struct is_member_pointer<Type ClassName::* const volatile> {
		static const bool value = true;
	};

	// is_same
	template <class, class>
	struct is_same {
		static const bool value = false;
	};

	template <class Type>
	struct is_same<Type, Type> {
		static const bool value = true;
	};

} // namespace shand_work

	union any_pointer
	{
		void* obj_ptr;
		void (*func_ptr)(); // 関数ポインタとvoid*間のキャストは許されないので必要
	};

	// 関数判別タグ
	struct function_ptr_tag {};	// 関数ポインタ
	struct function_obj_tag {};	// 関数オブジェクト
	struct member_ptr_tag {};	// メンバ関数ポインタ

	template <class FuncType>
	struct get_function_tag {
	private:
		typedef
			typename shand_work::if_<shand_work::is_pointer<FuncType>, function_ptr_tag, FuncType>::type
		func_ptr_tag;

		typedef
			typename shand_work::if_<shand_work::is_member_pointer<func_ptr_tag>, member_ptr_tag, func_ptr_tag>::type
		function_or_member_ptr_tag;

		typedef
			typename shand_work::if_<shand_work::is_same<FuncType, function_or_member_ptr_tag>,
				function_obj_tag, function_or_member_ptr_tag>::type
		ret_type;
	public:
		typedef ret_type type;
	};

	template <class FunctionPtr, class R>
	struct function_ptr_manager0 {
		static R invoke(any_pointer function_ptr)
		{
			FunctionPtr func = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);
			return func();
		}

		static void destroy(any_pointer)
		{
		}
	};

	template <class FunctionObj, class R>
	struct function_obj_manager0 {
		static R invoke(any_pointer function_obj_ptr)
		{
			FunctionObj* func = reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
			return (*func)();
		}

		static void destroy(any_pointer function_obj_ptr)
		{
			FunctionObj* func = reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
			delete func;
			func = 0;
		}
	};

	SHAND_FUNCTION_MANAGER_N(1);
	SHAND_FUNCTION_MANAGER_N(2);
	SHAND_FUNCTION_MANAGER_N(3);
	SHAND_FUNCTION_MANAGER_N(4);
	SHAND_FUNCTION_MANAGER_N(5);
	SHAND_FUNCTION_MANAGER_N(6);
	SHAND_FUNCTION_MANAGER_N(7);
	SHAND_FUNCTION_MANAGER_N(8);
	SHAND_FUNCTION_MANAGER_N(9);
	SHAND_FUNCTION_MANAGER_N(10);


	template <class Signature>
	class function_base {
	protected:
		typedef function_detail::any_pointer		any_pointer;
		typedef function_detail::function_ptr_tag	function_ptr_tag;
		typedef function_detail::function_obj_tag	function_obj_tag;
		typedef function_detail::member_ptr_tag		member_ptr_tag;

	public:
		void (*destroy_)(any_pointer);
		any_pointer functor_;

		function_base()
		{
			destroy_ = 0;
		}

		virtual ~function_base()
		{
			destroy_(functor_);
		}
	};

} // namespace shand::function_detail



template <class Signature>
class function;

template <class R>
class function<R (void)>
	: public function_detail::function_base<R (void)> {
public:
	typedef R result_type;

	result_type (*invoke_)(any_pointer);

	function()
		: function_base()
	{
		invoke_ = 0;
	}

	function(const function& func)
	{
		assign_to_own(func);
	}

	template <class FuncType>
	function(FuncType func)
	{
		assign_to(func);
	}

	function& operator=(const function& func)
	{
		if (&func == this)
			return *this;

		assign_to_own(func);
		return *this;
	}

	template <class FuncType>
	function& operator=(FuncType func)
	{
		clear();
		assign_to(func);

		return *this;
	}

	result_type operator()() const
	{
		return invoke_(functor_);
	}

	void clear()
	{
		if (!empty()) {
			destroy_(functor_);

			invoke_		= 0;
			destroy_	= 0;
		}
	}

	bool empty() const
	{
		return !(invoke_ && destroy_);
	}

	operator bool()
	{
		return !empty();
	}

	bool operator!()
	{
		return empty();
	}

private:
	template <class FuncType>
	void assign_to(FuncType func)
	{
		typedef typename function_detail::get_function_tag<FuncType>::type tag;
		assign_to(func, tag());
	}

	template <class FunctionPtr>
	void assign_to(FunctionPtr func, function_ptr_tag)
	{
		typedef function_detail::function_ptr_manager0<FunctionPtr, R> actual_manager;

		invoke_ = &actual_manager::invoke;
		destroy_ = &actual_manager::destroy;

		functor_.func_ptr = reinterpret_cast<void (*)()>(func);
	}

	template <class FunctionObj>
	void assign_to(FunctionObj func, function_obj_tag)
	{
		typedef function_detail::function_obj_manager0<FunctionObj, R> actual_manager;

		invoke_ = &actual_manager::invoke;
		destroy_ = &actual_manager::destroy;

		FunctionObj* new_func = new FunctionObj(func);
		functor_.obj_ptr = static_cast<void*>(new_func);
	}

	void assign_to_own(const function& func)
	{
		clear();
		invoke_		= func.invoke_;
		destroy_	= func.destroy_;
		functor_	= func.functor_;
	}
};


SHAND_FUNCTION_CLASS_N(1)
SHAND_FUNCTION_CLASS_N(2)
SHAND_FUNCTION_CLASS_N(3)
SHAND_FUNCTION_CLASS_N(4)
SHAND_FUNCTION_CLASS_N(5)
SHAND_FUNCTION_CLASS_N(6)
SHAND_FUNCTION_CLASS_N(7)
SHAND_FUNCTION_CLASS_N(8)
SHAND_FUNCTION_CLASS_N(9)
SHAND_FUNCTION_CLASS_N(10)

} // namespace shand


// delete macro
#undef SHAND_TEMPLATE_PARAMS_1
#undef SHAND_TEMPLATE_PARAMS_2
#undef SHAND_TEMPLATE_PARAMS_3
#undef SHAND_TEMPLATE_PARAMS_4
#undef SHAND_TEMPLATE_PARAMS_5
#undef SHAND_TEMPLATE_PARAMS_6
#undef SHAND_TEMPLATE_PARAMS_7
#undef SHAND_TEMPLATE_PARAMS_8
#undef SHAND_TEMPLATE_PARAMS_9
#undef SHAND_TEMPLATE_PARAMS_10

#undef SHAND_TEMPLATE_ARGS_1
#undef SHAND_TEMPLATE_ARGS_2
#undef SHAND_TEMPLATE_ARGS_3
#undef SHAND_TEMPLATE_ARGS_4
#undef SHAND_TEMPLATE_ARGS_5
#undef SHAND_TEMPLATE_ARGS_6
#undef SHAND_TEMPLATE_ARGS_7
#undef SHAND_TEMPLATE_ARGS_8
#undef SHAND_TEMPLATE_ARGS_9
#undef SHAND_TEMPLATE_ARGS_10

#undef SHAND_FUNCTION_PARAMS_1
#undef SHAND_FUNCTION_PARAMS_2
#undef SHAND_FUNCTION_PARAMS_3
#undef SHAND_FUNCTION_PARAMS_4
#undef SHAND_FUNCTION_PARAMS_5
#undef SHAND_FUNCTION_PARAMS_6
#undef SHAND_FUNCTION_PARAMS_7
#undef SHAND_FUNCTION_PARAMS_8
#undef SHAND_FUNCTION_PARAMS_9
#undef SHAND_FUNCTION_PARAMS_10

#undef SHAND_FUNCTION_ARGS_1
#undef SHAND_FUNCTION_ARGS_2
#undef SHAND_FUNCTION_ARGS_3
#undef SHAND_FUNCTION_ARGS_4
#undef SHAND_FUNCTION_ARGS_5
#undef SHAND_FUNCTION_ARGS_6
#undef SHAND_FUNCTION_ARGS_7
#undef SHAND_FUNCTION_ARGS_8
#undef SHAND_FUNCTION_ARGS_9
#undef SHAND_FUNCTION_ARGS_10

#undef SHAND_FUNCTION_MANAGER_N
#undef SHAND_FUNCTION_CLASS_N


#endif // SHAND_FUNCTION_INCLUDE

