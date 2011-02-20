#ifndef	SHAND_TOKENIZER_INCLUDE
#define SHAND_TOKENIZER_INCLUDE

#include <tchar.h>

#pragma warning(disable : 4786)
#pragma warning(disable : 4530)
#include <string>
#include <vector>

//------------------------------------------------------//
//														//
//	クラス名 : ctokenizer<String>						//
//				Stringには、以下のどちらかを指定		//
//					std::string							//
//					std::wstring						//
//	用    途 : トークン分割クラス						//
//														//
//------------------------------------------------------//

namespace shand {
template <class String>
class ctokenizer {};



//======================================================//
//														//
// std::string版										//
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
	std::string					token_;		// トークン分割対象となる文字列
	std::string					delim_;		// トークンを区切る文字の集合
	bool						ret_;		// 区切り文字をトークンとして扱うならtrue
	std::vector<std::string>	vtoken_;	// 分割された全文字列

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
	// 名称 : create_array()							//
	// 用途 : 分割文字列配列作成						//
	// 引数 : なし										//
	// 戻値 : なし										//
	//--------------------------------------------------//
	void create_array()
	{
		vtoken_.clear();
		while(!is_create()) {
			vtoken_.push_back(next());
		}
	}

	//--------------------------------------------------//
	// 名称 : is_create()								//
	// 用途 : トークン作成する？						//
	// 引数 : なし										//
	// 戻値 : true :トークンが空						//
	//		  false:トークンあり						//
	//--------------------------------------------------//
	bool is_create()
	{
		skip();
		return cur_ == std::string::npos;
	}

	//--------------------------------------------------//
	// 名称 : next()									//
	// 用途 : 切り出されたトークン取得					//
	// 引数 : なし										//
	// 戻値 : 切り出されたトークン						//
	//--------------------------------------------------//
	std::string next()
	{
		range_type range = next_range();
		return token_.substr(range.first, range.second);
	}

	//--------------------------------------------------//
	// 名称 : next_range()								//
	// 用途 : トークンを切り出し、その位置と長さを取得	//
	// 引数 : なし										//
	// 戻値 : range.first	: トークンの開始位置		//
	//		  range.second	: トークンの長さ			//
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
	// 名称 : replace()									//
	// 用途 : 文字列置換								//
	// 引数 : token  : 置換する文字列					//
	//		  oldstr : 置換対象							//
	//		  newstr : 置換文字列						//
	// 戻値 : 置換後文字列								//
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
	// 名称 : empty_replace()							//
	// 用途 : 空文字を" "に置換							//
	// 引数 : なし										//
	// 戻値 : なし										//
	//--------------------------------------------------//
	void empty_replace()
	{
		if (token_.length() <= 0)
			return;

		// 最初の文字がセパレータ
		if (token_.find(delim_, 0) == 0)
			token_ = " " + token_;

		std::string newtoken;

		// ",," → ", ,"
		newtoken	= replace(token_, delim_ + delim_, delim_ + " " + delim_);
		token_		= "";
		token_		= newtoken;

		newtoken	= replace(token_, delim_ + delim_, delim_ + " " + delim_);
		token_		= "";
		token_		= newtoken;

		// 改行文字置換
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
	// 名称 : delim_replace()							//
	// 用途 : 改行コード置換							//
	// 引数 : なし										//
	// 戻値 : 改行コード置換済み文字列					//
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
	// コピーコンストラクタ								//
	// token	: トークン文字列						//
	// delim	: 区切り文字の集合(セパレータ)			//
	//--------------------------------------------------//
	ctokenizer(const std::string& token, const std::string& delim, bool ret=false)
		: cur_(0), token_(token), delim_(delim), ret_(ret)
	{
		// 空文字置換
		empty_replace();

		// トークン分割
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

	// vectorに変換
	const std::vector<std::string>& c_vector() const
	{
		return vtoken_;
	}

	std::vector<std::string>& ref_vector()
	{
		return vtoken_;
	}

	// トークン変更
	void token(const std::string& token)
	{
		*this	= ctokenizer(token, delim_);
		cur_	= 0;
	}

	// デリミタ変更
	void delimiter(const std::string& delim, bool ret=false)
	{
		*this = ctokenizer(token_, delim, ret);
		cur_ = 0;
	}

	// 分割数取得
	size_t size() const { return vtoken_.size(); }

	// トークンが空か判断
	bool is_empty() const { return size() <= 0; }

	// 先頭イテレータ取得
	iterator				begin()			{ return vtoken_.begin(); }
	const_iterator			begin() const	{ return vtoken_.begin(); }

	// 最後尾イテレータ取得
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
// std::wstring版										//
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
	std::wstring				token_;		// トークン分割対象となる文字列
	std::wstring				delim_;		// トークンを区切る文字の集合
	bool						ret_;		// 区切り文字をトークンとして扱うならtrue
	std::vector<std::wstring>	vtoken_;	// 分割された全文字列

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
	// 名称 : create_array()							//
	// 用途 : 分割文字列配列作成						//
	// 引数 : なし										//
	// 戻値 : なし										//
	//--------------------------------------------------//
	void create_array()
	{
		vtoken_.clear();
		while(!is_create()) {
			vtoken_.push_back(next());
		}
	}

	//--------------------------------------------------//
	// 名称 : is_create()								//
	// 用途 : トークン作成する？						//
	// 引数 : なし										//
	// 戻値 : true :トークンが空						//
	//		  false:トークンあり						//
	//--------------------------------------------------//
	bool is_create()
	{
		skip();
		return cur_ == std::wstring::npos;
	}

	//--------------------------------------------------//
	// 名称 : next()									//
	// 用途 : 切り出されたトークン取得					//
	// 引数 : なし										//
	// 戻値 : 切り出されたトークン						//
	//--------------------------------------------------//
	std::wstring next()
	{
		range_type range = next_range();
		return token_.substr(range.first, range.second);
	}

	//--------------------------------------------------//
	// 名称 : next_range()								//
	// 用途 : トークンを切り出し、その位置と長さを取得	//
	// 引数 : なし										//
	// 戻値 : range.first	: トークンの開始位置		//
	//		  range.second	: トークンの長さ			//
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
	// 名称 : replace()									//
	// 用途 : 文字列置換								//
	// 引数 : token  : 置換する文字列					//
	//		  oldstr : 置換対象							//
	//		  newstr : 置換文字列						//
	// 戻値 : 置換後文字列								//
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
	// 名称 : empty_replace()							//
	// 用途 : 空文字を" "に置換							//
	// 引数 : なし										//
	// 戻値 : なし										//
	//--------------------------------------------------//
	void empty_replace()
	{
		if (token_.length() <= 0)
			return;

		// 最初の文字がセパレータ
		if (token_.find(delim_, 0) == 0)
			token_ = L" " + token_;

		std::wstring newtoken;

		// ",," → ", ,"
		newtoken	= replace(token_, delim_ + delim_, delim_ + L" " + delim_);
		token_		= L"";
		token_		= newtoken;

		// 改行文字置換
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
	// 名称 : delim_replace()							//
	// 用途 : 改行コード置換							//
	// 引数 : なし										//
	// 戻値 : 改行コード置換済み文字列					//
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
	// コピーコンストラクタ								//
	// token	: トークン文字列						//
	// delim	: 区切り文字の集合(セパレータ)			//
	//--------------------------------------------------//
	ctokenizer(const std::wstring& token, const std::wstring& delim, bool ret=false)
		: cur_(0), token_(token), delim_(delim), ret_(ret)
	{
		// 空文字置換
		empty_replace();

		// トークン分割
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

	// vectorに変換
	const std::vector<std::wstring>& c_vector() const
	{
		return vtoken_;
	}

	std::vector<std::wstring>& ref_vector()
	{
		return vtoken_;
	}

	// トークン変更
	void token(const std::wstring& token)
	{
		*this	= ctokenizer(token, delim_);
		cur_	= 0;
	}

	// デリミタ変更
	void delimiter(const std::wstring& delim, bool ret=false)
	{
		*this = ctokenizer(token_, delim, ret);
		cur_ = 0;
	}

	// 分割数取得
	size_t size() const	{return vtoken_.size();	}

	// トークンが空か判断
	bool is_empty() const {	return size() <= 0;	}

	// 先頭イテレータ取得
	iterator				begin()			{ return vtoken_.begin(); }
	const_iterator			begin() const	{ return vtoken_.begin(); }

	// 最後尾イテレータ取得
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
// tokenizer token("123,456,789", ","); // トークンを「,」で分割        //
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
// int token_size = token.size();             // 分割数取得             //
//                                                                      //
// bool token_empty = token.is_empty();       // トークンが空か判断     //
//                                                                      //
// token.token("abc,def,ghi");                // トークン変更           //
//                                                                      //
// token.delimiter(".");                      // デリミタを「.」に変更  //
//                                                                      //
// tokenizer::iterator first = token.begin(); // 先頭イテレータ取得     //
//                                                                      //
// tokenizer::iterator last  = token.end();   // 最後尾イテレータ取得   //
//                                                                      //
//======================================================================//


}	// namespace shand

#pragma warning(default : 4786)
#pragma warning(default : 4530)


#endif	// SHAND_TOKENIZER_INCLUDE