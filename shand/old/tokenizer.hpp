#ifndef	SHAND_TOKENIZER_INCLUDE
#define SHAND_TOKENIZER_INCLUDE

#include <tchar.h>

#pragma warning(disable : 4786)
#pragma warning(disable : 4530)
#include <string>
#include <vector>

//------------------------------------------------------//
//														//
//	�N���X�� : ctokenizer<String>						//
//				String�ɂ́A�ȉ��̂ǂ��炩���w��		//
//					std::string							//
//					std::wstring						//
//	�p    �r : �g�[�N�������N���X						//
//														//
//------------------------------------------------------//

namespace shand {
template <class String>
class ctokenizer {};



//======================================================//
//														//
// std::string��										//
// char													//
//														//
//======================================================//
template <>
class ctokenizer<std::string> {
public:
	typedef std::vector<std::string>::iterator							iterator;
	typedef std::vector<std::string>::const_iterator					const_iterator;
	typedef std::pair<std::string::size_type, std::string::size_type>	range_type;
	typedef std::string&												reference;
	typedef std::string													difference_type;
	typedef std::string													value_type;

#if defined(_MSC_VER) && _MSC_VER <= 1201
	typedef std::reverse_iterator<iterator, value_type>					reverse_iterator;
	typedef std::reverse_iterator<const_iterator, value_type>			const_reverse_iterator;
#else
	typedef std::reverse_iterator<iterator>								reverse_iterator;
	typedef std::reverse_iterator<const_iterator>						const_reverse_iterator;
#endif

private:
	std::string::size_type		cur_;
	std::string					token_;		// �g�[�N�������ΏۂƂȂ镶����
	std::string					delim_;		// �g�[�N������؂镶���̏W��
	bool						ret_;		// ��؂蕶�����g�[�N���Ƃ��Ĉ����Ȃ�true
	std::vector<std::string>	vtoken_;	// �������ꂽ�S������

private:
	void skip()
	{
		if (cur_ == token_.length())
			cur_ = std::string::npos;

		if (!ret_ && cur_ != std::string::npos) {
				std::string::size_type tmp = token_.find_first_not_of(delim_, cur_);

			if (tmp != std::string::npos)
				cur_ = tmp;
		}
	}

	//--------------------------------------------------//
	// ���� : create_array()							//
	// �p�r : ����������z��쐬						//
	// ���� : �Ȃ�										//
	// �ߒl : �Ȃ�										//
	//--------------------------------------------------//
	void create_array()
	{
		vtoken_.clear();
		while(!is_create()) {
			vtoken_.push_back(next());
		}
	}

	//--------------------------------------------------//
	// ���� : is_create()								//
	// �p�r : �g�[�N���쐬����H						//
	// ���� : �Ȃ�										//
	// �ߒl : true :�g�[�N������						//
	//		  false:�g�[�N������						//
	//--------------------------------------------------//
	bool is_create()
	{
		skip();
		return cur_ == std::string::npos;
	}

	//--------------------------------------------------//
	// ���� : next()									//
	// �p�r : �؂�o���ꂽ�g�[�N���擾					//
	// ���� : �Ȃ�										//
	// �ߒl : �؂�o���ꂽ�g�[�N��						//
	//--------------------------------------------------//
	std::string next()
	{
		range_type range = next_range();
		return token_.substr(range.first, range.second);
	}

	//--------------------------------------------------//
	// ���� : next_range()								//
	// �p�r : �g�[�N����؂�o���A���̈ʒu�ƒ������擾	//
	// ���� : �Ȃ�										//
	// �ߒl : range.first	: �g�[�N���̊J�n�ʒu		//
	//		  range.second	: �g�[�N���̒���			//
	//--------------------------------------------------//
	range_type next_range()
	{
		skip();

		typedef std::string String;
		String::size_type start	= cur_;

		if (cur_ != String::npos) {
			cur_ = token_.find_first_of(delim_, cur_);
		}

		if (cur_ == String::npos)
			return range_type(start, token_.length() - start);

		if (ret_			&&
			start == cur_	&&
			delim_.find(token_[cur_]) != String::npos)
			cur_++;

		return range_type(start, cur_ - start);
	}

	//--------------------------------------------------//
	// ���� : replace()									//
	// �p�r : ������u��								//
	// ���� : token  : �u�����镶����					//
	//		  oldstr : �u���Ώ�							//
	//		  newstr : �u��������						//
	// �ߒl : �u���㕶����								//
	//--------------------------------------------------//
	std::string replace(const std::string &token, const std::string &oldstr, const std::string &newstr)
	{
		typedef std::string String;

		String result(token);
		for (String::size_type pos = 0; String::npos != (pos = result.find(oldstr, pos)); pos += newstr.size()) {
			if (pos >= result.size() - oldstr.size())
				result.replace(pos, oldstr.size(), "");
			else
				result.replace(pos, oldstr.size(), newstr);
		}
		return result;
	}

	//--------------------------------------------------//
	// ���� : empty_replace()							//
	// �p�r : �󕶎���" "�ɒu��							//
	// ���� : �Ȃ�										//
	// �ߒl : �Ȃ�										//
	//--------------------------------------------------//
	void empty_replace()
	{
		if (token_.length() <= 0)
			return;

		// �ŏ��̕������Z�p���[�^
		if (token_.find(delim_, 0) == 0)
			token_ = " " + token_;

		std::string newtoken;

		// ",," �� ", ,"
		newtoken	= replace(token_, delim_ + delim_, delim_ + " " + delim_);
		token_		= "";
		token_		= newtoken;

		newtoken	= replace(token_, delim_ + delim_, delim_ + " " + delim_);
		token_		= "";
		token_		= newtoken;

		// ���s�����u��
		newtoken	= replace(token_, "\r", "");
		token_		= "";
		token_		= newtoken;

		newtoken	= "";
		newtoken	= delim_replace();
		token_		= "";
		token_		= newtoken;

		newtoken	= replace(token_, delim_ + delim_, delim_ + " " + delim_);
		token_		= "";
		token_		= newtoken;

		if (token_[token_.length() -1] == delim_[0])
			token_ += " ";
	}

	//--------------------------------------------------//
	// ���� : delim_replace()							//
	// �p�r : ���s�R�[�h�u��							//
	// ���� : �Ȃ�										//
	// �ߒl : ���s�R�[�h�u���ςݕ�����					//
	//--------------------------------------------------//
	std::string delim_replace()
	{
		typedef std::string String;

		String result(token_);
		String pattern("\n");
		for (String::size_type pos = 0; String::npos != (pos = result.find(pattern, pos)); pos += delim_.size()) {
			if (pos >= result.size() - pattern.size())
				result.replace(pos, pattern.size(), "");
			else
				result.replace(pos, pattern.size(), delim_);
		}
		return result;
	}
public:
	//--------------------------------------------------//
	// �R�s�[�R���X�g���N�^								//
	// token	: �g�[�N��������						//
	// delim	: ��؂蕶���̏W��(�Z�p���[�^)			//
	//--------------------------------------------------//
	ctokenizer(const std::string& token, const std::string& delim, bool ret=false)
		: cur_(0), token_(token), delim_(delim), ret_(ret)
	{
		// �󕶎��u��
		empty_replace();

		// �g�[�N������
		create_array();

		cur_ = 0;
	}

	~ctokenizer() {}

	// operator
	std::string operator[](unsigned int index) const
	{
		if (index < 0 ||
			index >= vtoken_.size())
			return "";

		if (vtoken_[index] == " ")
			return "";

		return vtoken_[index];
	}

	// vector�ɕϊ�
	const std::vector<std::string>& c_vector() const
	{
		return vtoken_;
	}

	std::vector<std::string>& ref_vector()
	{
		return vtoken_;
	}

	// �g�[�N���ύX
	void token(const std::string& token)
	{
		*this	= ctokenizer(token, delim_);
		cur_	= 0;
	}

	// �f���~�^�ύX
	void delimiter(const std::string& delim, bool ret=false)
	{
		*this = ctokenizer(token_, delim, ret);
		cur_ = 0;
	}

	// �������擾
	size_t size() const { return vtoken_.size(); }

	// �g�[�N�����󂩔��f
	bool is_empty() const { return size() <= 0; }

	// �擪�C�e���[�^�擾
	iterator				begin()			{ return vtoken_.begin(); }
	const_iterator			begin() const	{ return vtoken_.begin(); }

	// �Ō���C�e���[�^�擾
	iterator				end()			{ return vtoken_.end(); }
	const_iterator			end() const		{ return vtoken_.end(); }

	reverse_iterator		rbegin()		{ return vtoken_.rbegin(); }

#if !(defined(_MSC_VER) && _MSC_VER <= 1201)
	const_reverse_iterator	rbegin() const	{ return vtoken_.rbegin(); }
#endif

	reverse_iterator		rend()			{ return vtoken_.rend(); }

#if !(defined(_MSC_VER) && _MSC_VER <= 1201)
	const_reverse_iterator	rend() const	{ return vtoken_.rend(); }
#endif

};



//======================================================//
//														//
// std::wstring��										//
// wchar_t												//
//														//
//======================================================//
template<>
class ctokenizer<std::wstring> {
public:
	typedef std::vector<std::wstring>::iterator							iterator;
	typedef std::vector<std::wstring>::const_iterator					const_iterator;
	typedef std::pair<std::wstring::size_type, std::wstring::size_type> range_type;
	typedef std::wstring&												reference;
	typedef std::wstring												difference_type;
	typedef std::wstring												value_type;

#if defined(_MSC_VER) && _MSC_VER <= 1201
	typedef std::reverse_iterator<iterator, value_type>					reverse_iterator;
	typedef std::reverse_iterator<const_iterator, value_type>			const_reverse_iterator;
#else
	typedef std::reverse_iterator<iterator>								reverse_iterator;
	typedef std::reverse_iterator<const_iterator>						const_reverse_iterator;
#endif


private:
	std::wstring::size_type		cur_;
	std::wstring				token_;		// �g�[�N�������ΏۂƂȂ镶����
	std::wstring				delim_;		// �g�[�N������؂镶���̏W��
	bool						ret_;		// ��؂蕶�����g�[�N���Ƃ��Ĉ����Ȃ�true
	std::vector<std::wstring>	vtoken_;	// �������ꂽ�S������

private:
	void skip()
	{
		if (cur_ == token_.length())
			cur_ = std::wstring::npos;

		if (!ret_ && cur_ != std::wstring::npos) {
				std::wstring::size_type tmp = token_.find_first_not_of(delim_, cur_);

			if (tmp != std::wstring::npos)
				cur_ = tmp;
		}
	}

	//--------------------------------------------------//
	// ���� : create_array()							//
	// �p�r : ����������z��쐬						//
	// ���� : �Ȃ�										//
	// �ߒl : �Ȃ�										//
	//--------------------------------------------------//
	void create_array()
	{
		vtoken_.clear();
		while(!is_create()) {
			vtoken_.push_back(next());
		}
	}

	//--------------------------------------------------//
	// ���� : is_create()								//
	// �p�r : �g�[�N���쐬����H						//
	// ���� : �Ȃ�										//
	// �ߒl : true :�g�[�N������						//
	//		  false:�g�[�N������						//
	//--------------------------------------------------//
	bool is_create()
	{
		skip();
		return cur_ == std::wstring::npos;
	}

	//--------------------------------------------------//
	// ���� : next()									//
	// �p�r : �؂�o���ꂽ�g�[�N���擾					//
	// ���� : �Ȃ�										//
	// �ߒl : �؂�o���ꂽ�g�[�N��						//
	//--------------------------------------------------//
	std::wstring next()
	{
		range_type range = next_range();
		return token_.substr(range.first, range.second);
	}

	//--------------------------------------------------//
	// ���� : next_range()								//
	// �p�r : �g�[�N����؂�o���A���̈ʒu�ƒ������擾	//
	// ���� : �Ȃ�										//
	// �ߒl : range.first	: �g�[�N���̊J�n�ʒu		//
	//		  range.second	: �g�[�N���̒���			//
	//--------------------------------------------------//
	range_type next_range()
	{
		skip();

		typedef std::wstring String;
		String::size_type start	= cur_;

		if (cur_ != String::npos) {
			cur_ = token_.find_first_of(delim_, cur_);
		}

		if (cur_ == String::npos)
			return range_type(start, token_.length() - start);

		if (ret_			&&
			start == cur_	&&
			delim_.find(token_[cur_]) != String::npos)
			cur_++;

		return range_type(start, cur_ - start);
	}

	//--------------------------------------------------//
	// ���� : replace()									//
	// �p�r : ������u��								//
	// ���� : token  : �u�����镶����					//
	//		  oldstr : �u���Ώ�							//
	//		  newstr : �u��������						//
	// �ߒl : �u���㕶����								//
	//--------------------------------------------------//
	std::wstring replace(const std::wstring &token, const std::wstring &oldstr, const std::wstring &newstr)
	{
		typedef std::wstring String;

		String result(token);
		for (String::size_type pos = 0; String::npos != (pos = result.find(oldstr, pos)); pos += newstr.size()) {
			if (pos >= result.size() - oldstr.size())
				result.replace(pos, oldstr.size(), L"");
			else
				result.replace(pos, oldstr.size(), newstr);
		}
		return result;
	}

	//--------------------------------------------------//
	// ���� : empty_replace()							//
	// �p�r : �󕶎���" "�ɒu��							//
	// ���� : �Ȃ�										//
	// �ߒl : �Ȃ�										//
	//--------------------------------------------------//
	void empty_replace()
	{
		if (token_.length() <= 0)
			return;

		// �ŏ��̕������Z�p���[�^
		if (token_.find(delim_, 0) == 0)
			token_ = L" " + token_;

		std::wstring newtoken;

		// ",," �� ", ,"
		newtoken	= replace(token_, delim_ + delim_, delim_ + L" " + delim_);
		token_		= L"";
		token_		= newtoken;

		// ���s�����u��
		newtoken	= replace(token_, L"\r", L"");
		token_		= L"";
		token_		= newtoken;

		newtoken	= L"";
		newtoken	= delim_replace();
		token_		= L"";
		token_		= newtoken;

		newtoken	= replace(token_, delim_ + delim_, delim_ + L" " + delim_);
		token_		= L"";
		token_		= newtoken;

		if (token_[token_.length() -1] == delim_[0])
			token_ += L" ";
	}

	//--------------------------------------------------//
	// ���� : delim_replace()							//
	// �p�r : ���s�R�[�h�u��							//
	// ���� : �Ȃ�										//
	// �ߒl : ���s�R�[�h�u���ςݕ�����					//
	//--------------------------------------------------//
	std::wstring delim_replace()
	{
		typedef std::wstring String;

		String result(token_);
		String pattern(L"\n");
		for (String::size_type pos = 0; String::npos != (pos = result.find(pattern, pos)); pos += delim_.size()) {
			if (pos >= result.size() - pattern.size())
				result.replace(pos, pattern.size(), L"");
			else
				result.replace(pos, pattern.size(), delim_);
		}
		return result;
	}
public:
	//--------------------------------------------------//
	// �R�s�[�R���X�g���N�^								//
	// token	: �g�[�N��������						//
	// delim	: ��؂蕶���̏W��(�Z�p���[�^)			//
	//--------------------------------------------------//
	ctokenizer(const std::wstring& token, const std::wstring& delim, bool ret=false)
		: cur_(0), token_(token), delim_(delim), ret_(ret)
	{
		// �󕶎��u��
		empty_replace();

		// �g�[�N������
		create_array();

		cur_ = 0;
	}

	~ctokenizer() {}

	// operator
	std::wstring operator[](unsigned int index) const
	{
		if (index < 0 ||
			index >= vtoken_.size())
			return L"";

		if (vtoken_[index] == L" ")
			return L"";

		return vtoken_[index];
	}

	// vector�ɕϊ�
	const std::vector<std::wstring>& c_vector() const
	{
		return vtoken_;
	}

	std::vector<std::wstring>& ref_vector()
	{
		return vtoken_;
	}

	// �g�[�N���ύX
	void token(const std::wstring& token)
	{
		*this	= ctokenizer(token, delim_);
		cur_	= 0;
	}

	// �f���~�^�ύX
	void delimiter(const std::wstring& delim, bool ret=false)
	{
		*this = ctokenizer(token_, delim, ret);
		cur_ = 0;
	}

	// �������擾
	size_t size() const	{return vtoken_.size();	}

	// �g�[�N�����󂩔��f
	bool is_empty() const {	return size() <= 0;	}

	// �擪�C�e���[�^�擾
	iterator				begin()			{ return vtoken_.begin(); }
	const_iterator			begin() const	{ return vtoken_.begin(); }

	// �Ō���C�e���[�^�擾
	iterator				end()			{ return vtoken_.end(); }
	const_iterator			end() const		{ return vtoken_.end(); }

#if !(defined(_MSC_VER) && _MSC_VER <= 1201)
	const_reverse_iterator	rbegin() const	{ return vtoken_.rbegin(); }
#endif

	reverse_iterator		rend()			{ return vtoken_.rend(); }

#if !(defined(_MSC_VER) && _MSC_VER <= 1201)
	const_reverse_iterator	rend() const	{ return vtoken_.rend(); }
#endif
};


// tokenizer type
typedef ctokenizer<std::string>					atokenizer;
typedef ctokenizer<std::wstring>				wtokenizer;
typedef ctokenizer<std::basic_string<TCHAR> >	tokenizer;

//----------------------------------------------------------------------//
// Sample                                                               //
//======================================================================//
// tokenizer token("123,456,789", ","); // �g�[�N�����u,�v�ŕ���        //
//                                                                      //
// for (tokenizer::iterator it = token.begin(); it != token.end(); ++it)//
//   cout << *it << endl;                                               //
//                                                                      //
//----------------------------------------------------------------------//
// 123      |
// 456      |
// 789      |
//          |
//-----------

//----------------------------------------------------------------------//
// Reference                                                            //
//======================================================================//
// int token_size = token.size();             // �������擾             //
//                                                                      //
// bool token_empty = token.is_empty();       // �g�[�N�����󂩔��f     //
//                                                                      //
// token.token("abc,def,ghi");                // �g�[�N���ύX           //
//                                                                      //
// token.delimiter(".");                      // �f���~�^���u.�v�ɕύX  //
//                                                                      //
// tokenizer::iterator first = token.begin(); // �擪�C�e���[�^�擾     //
//                                                                      //
// tokenizer::iterator last  = token.end();   // �Ō���C�e���[�^�擾   //
//                                                                      //
//======================================================================//


}	// namespace shand

#pragma warning(default : 4786)
#pragma warning(default : 4530)


#endif	// SHAND_TOKENIZER_INCLUDE