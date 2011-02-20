#ifndef	SHAND_FUNCTIONAL_INCLUDE
#define SHAND_FUNCTIONAL_INCLUDE

//==========================================================//
//	�\���̂̎w�胁���o�ł̔�r���Z���s���֐��I�u�W�F�N�g	//
//	mem_less, mem_greater, mem_equal, mem_not_equal			//
//==========================================================//

#include <functional>

namespace shand {
	// less
	template<class ClassName, class Type>
	class CMemLessFunctor : public std::binary_function<ClassName, ClassName, bool>
	{
	public:
		explicit CMemLessFunctor(Type ClassName::* pMember)
			: m_pMember(pMember)
		{
		}

		bool operator() (const ClassName &lhs, const ClassName &rhs) const
		{
			return lhs.*m_pMember < rhs.*m_pMember;
		}
	private:
		Type ClassName::* m_pMember;
	};

	template<class ClassName, class Type>
	inline CMemLessFunctor<ClassName, Type> mem_less(Type ClassName::* pMember)
	{
		return CMemLessFunctor<ClassName, Type>(pMember);
	}

	// greater
	template<class ClassName, class Type>
	class CMemGreaterFunctor : public std::binary_function<ClassName, ClassName, bool>
	{
	public:
		explicit CMemGreaterFunctor(Type ClassName::* pMember)
			: m_pMember(pMember)
		{
		}

		bool operator() (const ClassName &lhs, const ClassName &rhs) const
		{
			return lhs.*m_pMember > rhs.*m_pMember;
		}
	private:
		Type ClassName::* m_pMember;
	};

	template<class ClassName, class Type>
	inline CMemGreaterFunctor<ClassName, Type> mem_greater(Type ClassName::* pMember)
	{
		return CMemGreaterFunctor<ClassName, Type>(pMember);
	}

	// equal
	template<class ClassName, class Type>
	class CMemEqualFunctor : public std::binary_function<ClassName, ClassName, bool>
	{
	public:
		explicit CMemEqualFunctor(Type ClassName::* pMember)
			: m_pMember(pMember)
		{
		}

		bool operator() (const ClassName &lhs, const ClassName &rhs) const
		{
			return lhs.*m_pMember == rhs.*m_pMember;
		}
	private:
		Type ClassName::* m_pMember;
	};

	template<class ClassName, class Type>
	inline CMemEqualFunctor<ClassName, Type> mem_equal(Type ClassName::* pMember)
	{
		return CMemEqualFunctor<ClassName, Type>(pMember);
	}

	// not_equal
	template<class ClassName, class Type>
	class CMemNotEqualFunctor : public std::binary_function<ClassName, ClassName, bool>
	{
	public:
		explicit CMemNotEqualFunctor(Type ClassName::* pMember)
			: m_pMember(pMember)
		{
		}

		bool operator() (const ClassName &lhs, const ClassName &rhs) const
		{
			return lhs.*m_pMember != rhs.*m_pMember;
		}
	private:
		Type ClassName::* m_pMember;
	};

	template<class ClassName, class Type>
	inline CMemNotEqualFunctor<ClassName, Type> mem_not_equal(Type ClassName::* pMember)
	{
		return CMemNotEqualFunctor<ClassName, Type>(pMember);
	}

}	// namespace shand


//------------------------------------------------------//
//						How to use						//
//======================================================//
// Sort struct array, for member.						//
//														//
// struct person {										//
//	 int	age;	// �N��								//
//	 string	name;	// ���O								//
// };													//
//														//
// age(�N��)�ŕ��ёւ� - �~��							//
// void sort_age(vector<person> &v)						//
// {													//
//   sort(v.begin(), v.end(), mem_less(&person::age));	//
// }													//
//														//
// name(���O)�ŕ��ёւ� - �~��							//
// void sort_name(vector<person> &v)					//
// {													//
//   sort(v.begin(), v.end(), mem_less(&person::name));	//
// }													//
//														//
//	�����ł̕��ёւ��ɂ�mem_greater���g�p				//
//------------------------------------------------------//

#endif	// SHAND_FUNCTIONAL_INCLUDE

