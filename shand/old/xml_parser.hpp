#ifndef SHAND_XML_PARSER_INCLUDE
#define SHAND_XML_PARSER_INCLUDE

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//------------------------------------------------------//
// Name : xml_parser									//
// Desc : 簡易XMLパーサー								//
// Note : ツリー構造やDTD等を無視しているので			//
//		  簡単なことしかできません						//
//		  iniファイルやCSVの代わり程度に使います		//
//														//
// Version : 0.80 2007/05/30 作成						//
//														//
//------------------------------------------------------//

#include <fstream>
#include <string>
#include <queue>
#include <map>

namespace shand {

namespace detail {
template<class FwdIter, class Type>
inline int chain_count_work(FwdIter first, FwdIter last, const Type& value)
{
	int count = 0;
	for (; first != last; ++first) {
		if (*first == value)
			count++;
		else {
			if (count != 0)
				break;
		}
	}

	return count;
}
} // namesapace detail

//------------------------------//
// XML要素						//
//------------------------------//
struct xml_element {
	typedef std::pair<std::string, std::string> element_type;
	typedef std::map<std::string, std::string>	attribute_type;

	element_type	element;	// 要素
	attribute_type	attribute;	// 属性
};


//------------------------------//
// XML書き込み					//
//------------------------------//
class xml_writer {
	std::ofstream	file_;		// 出力ファイル
	std::string		root_;		// Root要素名
	int				indent_;	// インデント数

public:
	xml_writer() : file_(), root_(""), indent_(2) {}

	xml_writer(const std::string& path, const std::string& root)
		: file_(), root_(root), indent_(2)
	{
		open(path, root);
	}

	~xml_writer()
	{
		close();
	}

	//----------------------------------//
	// 名称 : open()					//
	// 用途 : ファイル開く				//
	// 引数 : file_name : ファイル名	//
	//		  root		: Root要素名	//
	// 戻値 : true:正常 false:失敗		//
	//----------------------------------//
	bool open(const std::string& path, const std::string& root)
	{
		file_.open(path.c_str());

		// オープン失敗
		if (!file_.is_open())
			return false;

		root_ = root;

		// XML宣言出力
		file_ << "<?xml version=\"1.0\" encoding=\"shift_jis\"?>" << std::endl;

		// Root要素出力
		file_ << "<" << root_ << ">" << std::endl;

		return true;
	}

	//----------------------------------//
	// 名称 : close()					//
	// 用途 : ファイル閉じる			//
	// 引数 : なし						//
	// 戻値 : なし						//
	//----------------------------------//
	void close()
	{
		if (file_.is_open()) {
			file_ << "</" << root_ << ">" << std::endl;
			file_.close();
		}
	}


	//----------------------------------//
	// 名称 : is_open()					//
	// 用途 : ファイルが開かれているか	//
	// 引数 : なし						//
	// 戻値 : true  : 開いている		//
	//		  false : 閉じている		//
	//----------------------------------//
	bool is_open() const
	{
		return file_.is_open();
	}


	//----------------------------------//
	// 名称 : head()					//
	// 用途 : 開始タグ出力				//
	// 引数 : 開始タグ(要素名)			//
	// 戻値 : 自分への参照				//
	//----------------------------------//
	void head(const std::string& element)
	{
		file_ << indent() << "<" << element << ">" << std::endl;

		indent_ += 2;
	}


	//----------------------------------//
	// 名称 : tail()					//
	// 用途 : 終了タグ出力				//
	// 引数 : 終了タグ(要素名)			//
	// 戻値 : 自分への参照				//
	//----------------------------------//
	void tail(const std::string& element)
	{
		indent_ -= 2;
		if (indent_ < 2)
			indent_ = 2;

		file_ << indent() << "</" << element << ">" << std::endl;
	}

	//----------------------------------//
	// 名称 : operator<< ()				//
	// 用途 : XML要素出力(属性含む)		//
	// 引数 : XML要素					//
	// 戻値 : 自分への参照				//
	//----------------------------------//
	xml_writer& operator<<(const xml_element& element)
	{
		// 要素名出力
		file_ << indent() << "<" << element.element.first;

		// 属性出力
		typedef std::map<std::string, std::string>::const_iterator Iterator;
		for (Iterator first = element.attribute.begin(), last = element.attribute.end(); first != last; ++first) {
			file_ << " " << first->first << "=\"" << first->second << "\"";
		}

		// 要素終了タグ出力
		if (element.element.second.empty())
			file_ << "/>" << std::endl;
		else
			file_ << ">" << element.element.second << "</" << element.element.first << ">" << std::endl;

		return *this;
	}

private:
	std::string indent()
	{
		return std::string(indent_, ' ');
	}
};

//----------------------------------------------------------------------------------//
// Sample																			//
//==================================================================================//
// xml_element create_element(const string& name, const string& age)				//
// {																				//
//     xml_element elem;															//
//     elem.element          = pair<string, string>("Person", name); // 要素作成	//
//     elem.attribute["Age"] = age;                                  // 属性作成	//
//																					//
//     return elem;																	//
// }																				//
//																					//
// int main()																		//
// {																				//
//     xml_writer xs("c:\\test.xml", "Root");										//
//																					//
//     xs << create_element("Akira",  "22")											//
//        << create_element("Millia", "20");										//
//																					//
//     return 0;																	//
// }																				//
//																					//
//----------------------------------------------------------------------------------//
// test.xml																			//
//==================================================================================//
// <?xml version="1.0" encoding="shift_jis"?>										//
// <Root>																			//
//   <Person Age="22">Akira</Person>												//
//   <Person Age="20">Millia</Person>												//
// </Root>																			//
//																					//
//----------------------------------------------------------------------------------//


//------------------------------//
// XML読み込み					//
//------------------------------//
class xml_reader {
	std::ifstream			file_;		// XMLファイル
	std::queue<xml_element>	element_;	// 全要素
	std::string				xmldoc_;	// XML文書

public:
	xml_reader() {}

	xml_reader(const std::string& path)
	{
		open(path);
	}

	~xml_reader()
	{
		close();
	}


	//----------------------------------//
	// 名称 : open()					//
	// 用途 : ファイル開く				//
	// 引数 : ファイル名				//
	// 戻値 : true:正常 false:失敗		//
	//----------------------------------//
	bool open(const std::string& path)
	{
		file_.open(path.c_str());

		if (!file_.is_open())
			return false;

		// XML文書読込
		std::string xmldoc = read();
		xmldoc_ = xmldoc;

		// 改行とタブ文字をスペースに置換
		xmldoc = replace(xmldoc, "\r", " ");
		xmldoc = replace(xmldoc, "\n", " ");
		xmldoc = replace(xmldoc, "\t", " ");

		// 不要なスペース削除
		xmldoc = remove_trash_space(xmldoc);

		// 要素解析
		element_analysis(xmldoc);

		return true;
	}


	//----------------------------------//
	// 名称 : close()					//
	// 用途 : ファイル閉じる			//
	// 引数 : なし						//
	// 戻値 : なし						//
	//----------------------------------//
	void close()
	{
		if (file_.is_open())
			file_.close();
	}


	//----------------------------------//
	// 名称 : is_open()					//
	// 用途 : ファイルが開かれているか	//
	// 引数 : なし						//
	// 戻値 : true  : 開いている		//
	//		  false : 閉じている		//
	//----------------------------------//
	bool is_open() const
	{
		return file_.is_open();
	}


	//----------------------------------//
	// 名称 : operator>>()				//
	// 用途 : XML要素取り出し			//
	// 引数 : 抽出先XML要素				//
	// 戻値 : true  : 取得成功			//
	//		  false : 取得失敗			//
	//----------------------------------//
	bool operator>>(xml_element& element)
	{
		if (!element_.empty()) {
			element = element_.front();
			element_.pop();
			return true;
		}
		return false;
	}


	//----------------------------------//
	// 名称 : document()				//
	// 用途 : XML文書取得				//
	// 引数 : なし						//
	// 戻値 : XML文書					//
	//----------------------------------//
	std::string document() const
	{
		return xmldoc_;
	}

private:

	//----------------------------------//
	// 名称 : read()					//
	// 用途 : XML文書読込				//
	// 引数 : なし						//
	// 戻値 : XML文書					//
	//----------------------------------//
	std::string read()
	{
		std::string xmldoc;

		char c = 0;
		while(file_.read(&c, 1)) {
			xmldoc += c;
		}
		return xmldoc;
	}


	//----------------------------------//
	// 名称 : replace()					//
	// 用途 : 文字列置換				//
	// 引数 : target : 対象文字列		//
	//		  before : 置換元文字列		//
	//		  after  : 置換後文字列		//
	// 戻値 : 置換済み文字列			//
	//----------------------------------//
	static std::string replace(const std::string &target, const std::string& before, const std::string& after)
	{
		typedef std::string String;

		String result(target);
		for (String::size_type pos = 0; String::npos != (pos = result.find(before, pos)); pos += after.size()) {
			if (pos >= result.size() - before.size())
				result.replace(pos, before.size(), "");
			else
				result.replace(pos, before.size(), after);
		}
		return result;
	}


	//----------------------------------//
	// 名称 : remove_trash_space()		//
	// 用途 : 不要なスペース削除		//
	// 引数 : 対象文字列				//
	// 戻値 : 処理後文字列				//
	//----------------------------------//
	static std::string remove_trash_space(const std::string& target)
	{
		std::string result(target);

		for (std::string::size_type index = 0; index < result.length(); ++index) {
			bool is_remove = false;

			 std::string::size_type find_index = result.find_first_of(" ", index);

			 if (find_index == std::string::npos)
				 continue;

			 // "< " と "> "のスペース削除
			 if (find_index > 0) {
				if (result[find_index -1] == '<' || result[find_index -1] == '>')
					is_remove = true;
			 }

			 // " <" と " >"のスペース削除
			 if (result.length() > find_index + 1) {
				 if (result[find_index +1] == '<' || result[find_index +1] == '>' || result[find_index +1] == ' ')
					is_remove = true;
			 }

			 if (is_remove)
				 result.erase(find_index, 1);
		}

		return result;
	}


	//----------------------------------//
	// 名称 : element_analysis()		//
	// 用途 : 要素解析					//
	// 引数 : 解析用XML文書				//
	// 戻値 : なし						//
	//----------------------------------//
	void element_analysis(const std::string& xmldoc)
	{
		typedef std::string::size_type size_type;
		#define not_found std::string::npos

		for (size_type index = 0; index < xmldoc.length(); ++index) {
			// 要素名検索
			size_type start	= xmldoc.find_first_of('<', index);
			if (start == not_found)
				break;

			size_type end = xmldoc.find_first_of('>', start);
			if (end == not_found)
				break;

			// 要素名抽出
			std::string	element_name = xmldoc.substr(start, end - start + 1);

			// 要素検索
			size_type start_elem = end + 1;
			if (start_elem >= xmldoc.length())
				break;

			size_type end_elem = xmldoc.find_first_of('<', start_elem);
			if (end_elem == not_found)
				break;

			std::string elem;
			// 空要素
			if (element_name.find("/>") != not_found)
				elem = "";
			// 要素抽出
			else
				elem = xmldoc.substr(start_elem, end_elem - start_elem);

			index = end;
			if (!is_element_name(element_name))
				continue;

			attribute_analysis(element_name, elem);
		}
	}


	//----------------------------------//
	// 名称 : attribute_analysis()		//
	// 用途 : 属性解析					//
	// 引数 : element		: 要素名	//
	//		  element_value : 要素		//
	// 戻値 : なし						//
	//----------------------------------//
	void attribute_analysis(const std::string& element, const std::string& element_value)
	{
		typedef std::string::size_type size_type;
		#define not_found std::string::npos

		xml_element xmlelem;
		bool		no_attribute = false;

		// 要素名検索
		size_type	start_elem	= 1;
		size_type	end_elem	= element.find_first_of(' ', start_elem);
		if (end_elem == not_found) {
			no_attribute = true; // 属性なし
			end_elem = element.find_first_of('>', start_elem);
		}

		// 要素名抽出
		std::string elem_name	= element.substr(start_elem, end_elem - start_elem);

		// 要素設定
		xmlelem.element.first	= replace(elem_name, " ", "");
		xmlelem.element.second	= normalize(element_value);

		// 属性なし
		if (no_attribute) {
			if(!element_value.empty())
				element_.push(xmlelem);
			return;
		}

		// 属性検索
		for (size_type index = 0; index < element.length(); ++index) {
			xml_element::attribute_type attribute;

			// 属性名
			size_type start_name = element.find_first_of(' ', index);
			if (start_name == not_found)
				break;

			++start_name;

			size_type end_name = element.find_first_of('=', start_name);
			if (end_name == not_found)
				break;

			// 属性名抽出
			std::string attribute_name = element.substr(start_name, end_name - start_name);

			// 属性値検索
			size_type start_value = end_name + 2;
			size_type end_value   = element.find_first_of('\"', start_value);
			if (end_value == not_found)
				break;

			// 属性値抽出
			std::string attribute_value = element.substr(start_value, end_value - start_value);

			// スペース削除
			attribute_name  = replace(attribute_name, " ", "");
			attribute_value = normalize(attribute_value);

			xmlelem.attribute[attribute_name] = attribute_value;

			index = end_value;
		}

		// 要素追加
		element_.push(xmlelem);
	}


	//----------------------------------//
	// 名称 : is_element_name()			//
	// 用途 : 要素名か判断				//
	// 引数 : 要素名					//
	// 戻値 : true  : 要素名			//
	//		  false : 要素名ではない	//
	//----------------------------------//
	static bool is_element_name(const std::string& element_name)
	{
		std::string::size_type length = element_name.length();

		// コメント
		if (length >= 3 && element_name.substr(0, 4) == "<!--")
			return false;

		// 終了タグ
		if (length >= 2 && element_name.substr(0, 2) == "</")
			return false;

		// XML宣言
		if (length >= 2 && element_name.substr(0, 2) == "<?")
			return false;

		return true;
	}


	//----------------------------------//
	// 名称 : normalize()				//
	// 用途 : 正規化					//
	// 引数 : 正規化対象				//
	// 戻値 : 正規化後文字列			//
	//----------------------------------//
	static std::string normalize(const std::string& target)
	{
		std::string result = target;

		// 複数の「半角スペース」「タブ」「改行」を1半角スペースに置換
		for (;;) {
			int count = detail::chain_count_work(result.begin(), result.end(), ' ');
			if (count < 2)
				break;

			result = replace(result, std::string(count, ' '), " ");
		}
		return result;
	}

};



//----------------------------------------------------------------------------------//
// Sample																			//
//==================================================================================//
// int main()																		//
// {																				//
//     map<string, xml_element> addr_book; // アドレス帳							//
//																					//
//     // 読込																		//
//     xml_reader  xi("c:\\test.xml");												//
//     xml_element person;															//
//																					//
//     while (xi >> person) {														//
//         addr_book[person.attribute.find("No")->second] = person;					//
//     }																			//
//																					//
//     // 一覧表示																	//
//     typedef map<string, xml_element>::iterator Iterator;							//
//     for (Iterator it = addr_book.begin(); it != addr_book.end(); ++it) {			//
//         cout << it->second.attribute.find("No")->second   << " "		// No		//
//              << it->second.attribute.find("Name")->second << " "		// Name		//
//              << it->second.attribute.find("Mail")->second << endl;	// Mail		//
//     }																			//
//																					//
//     return 0;																	//
// }																				//
//																					//
//----------------------------------------------------------------------------------//
// test.xml																			//
//==================================================================================//
// <?xml version="1.0" encoding="shift_jis"?>										//
// <Root>																			//
//   <Person Name="Akira" No="0063" Mail="xxx@aaa.jp"/>								//
//   <Person Name="Millia" No="0021" Mail="yyy@bbb.jp"/>							//
// </Root>																			//
//																					//
//----------------------------------------------------------------------------------//
// Excution																			//
//==================================================================================//
// 0021 Millia yyy@bbb.jp															//
// 0063 Akira xxx@aaa.jp															//
//																					//
//----------------------------------------------------------------------------------//


} // namespace shand


#endif // SHAND_XML_PARSER_INCLUDE

