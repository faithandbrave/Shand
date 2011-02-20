#ifndef SHAND_XML_PARSER_INCLUDE
#define SHAND_XML_PARSER_INCLUDE


//------------------------------------------------------//
// Name : xml_parser									//
// Desc : �Ȉ�XML�p�[�T�[								//
// Note : �c���[�\����DTD���𖳎����Ă���̂�			//
//		  �ȒP�Ȃ��Ƃ����ł��܂���						//
//		  ini�t�@�C����CSV�̑�����x�Ɏg���܂�		//
//														//
// Version : 0.80 2007/05/30 �쐬						//
//														//
//				Programmed By Akira.T					//
//		Copyright(C) 2007 Akira.T All rights reserved	//
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
// XML�v�f						//
//------------------------------//
struct xml_element {
	typedef std::pair<std::string, std::string> element_type;
	typedef std::map<std::string, std::string>	attribute_type;

	element_type	element;	// �v�f
	attribute_type	attribute;	// ����
};


//------------------------------//
// XML��������					//
//------------------------------//
class xml_writer {
	std::ofstream	file_;		// �o�̓t�@�C��
	std::string		root_;		// Root�v�f��
	int				indent_;	// �C���f���g��

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
	// ���� : open()					//
	// �p�r : �t�@�C���J��				//
	// ���� : file_name : �t�@�C����	//
	//		  root		: Root�v�f��	//
	// �ߒl : true:���� false:���s		//
	//----------------------------------//
	bool open(const std::string& path, const std::string& root)
	{
		file_.open(path.c_str());

		// �I�[�v�����s
		if (!file_.is_open())
			return false;

		root_ = root;

		// XML�錾�o��
		file_ << "<?xml version=\"1.0\" encoding=\"shift_jis\"?>" << std::endl;

		// Root�v�f�o��
		file_ << "<" << root_ << ">" << std::endl;

		return true;
	}

	//----------------------------------//
	// ���� : close()					//
	// �p�r : �t�@�C������			//
	// ���� : �Ȃ�						//
	// �ߒl : �Ȃ�						//
	//----------------------------------//
	void close()
	{
		if (file_.is_open()) {
			file_ << "</" << root_ << ">" << std::endl;
			file_.close();
		}
	}


	//----------------------------------//
	// ���� : is_open()					//
	// �p�r : �t�@�C�����J����Ă��邩	//
	// ���� : �Ȃ�						//
	// �ߒl : true  : �J���Ă���		//
	//		  false : ���Ă���		//
	//----------------------------------//
	bool is_open() const
	{
		return file_.is_open();
	}


	//----------------------------------//
	// ���� : head()					//
	// �p�r : �J�n�^�O�o��				//
	// ���� : �J�n�^�O(�v�f��)			//
	// �ߒl : �����ւ̎Q��				//
	//----------------------------------//
	void head(const std::string& element)
	{
		file_ << indent() << "<" << element << ">" << std::endl;

		indent_ += 2;
	}


	//----------------------------------//
	// ���� : tail()					//
	// �p�r : �I���^�O�o��				//
	// ���� : �I���^�O(�v�f��)			//
	// �ߒl : �����ւ̎Q��				//
	//----------------------------------//
	void tail(const std::string& element)
	{
		indent_ -= 2;
		if (indent_ < 2)
			indent_ = 2;

		file_ << indent() << "</" << element << ">" << std::endl;
	}

	//----------------------------------//
	// ���� : operator<< ()				//
	// �p�r : XML�v�f�o��(�����܂�)		//
	// ���� : XML�v�f					//
	// �ߒl : �����ւ̎Q��				//
	//----------------------------------//
	xml_writer& operator<<(const xml_element& element)
	{
		// �v�f���o��
		file_ << indent() << "<" << element.element.first;

		// �����o��
		typedef std::map<std::string, std::string>::const_iterator Iterator;
		for (Iterator first = element.attribute.begin(), last = element.attribute.end(); first != last; ++first) {
			file_ << " " << first->first << "=\"" << first->second << "\"";
		}

		// �v�f�I���^�O�o��
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
//     elem.element          = pair<string, string>("Person", name); // �v�f�쐬	//
//     elem.attribute["Age"] = age;                                  // �����쐬	//
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
// XML�ǂݍ���					//
//------------------------------//
class xml_reader {
	std::ifstream			file_;		// XML�t�@�C��
	std::queue<xml_element>	element_;	// �S�v�f
	std::string				xmldoc_;	// XML����

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
	// ���� : open()					//
	// �p�r : �t�@�C���J��				//
	// ���� : �t�@�C����				//
	// �ߒl : true:���� false:���s		//
	//----------------------------------//
	bool open(const std::string& path)
	{
		file_.open(path.c_str());

		if (!file_.is_open())
			return false;

		// XML�����Ǎ�
		std::string xmldoc = read();
		xmldoc_ = xmldoc;

		// ���s�ƃ^�u�������X�y�[�X�ɒu��
		xmldoc = replace(xmldoc, "\r", " ");
		xmldoc = replace(xmldoc, "\n", " ");
		xmldoc = replace(xmldoc, "\t", " ");

		// �s�v�ȃX�y�[�X�폜
		xmldoc = remove_trash_space(xmldoc);

		// �v�f���
		element_analysis(xmldoc);

		return true;
	}


	//----------------------------------//
	// ���� : close()					//
	// �p�r : �t�@�C������			//
	// ���� : �Ȃ�						//
	// �ߒl : �Ȃ�						//
	//----------------------------------//
	void close()
	{
		if (file_.is_open())
			file_.close();
	}


	//----------------------------------//
	// ���� : is_open()					//
	// �p�r : �t�@�C�����J����Ă��邩	//
	// ���� : �Ȃ�						//
	// �ߒl : true  : �J���Ă���		//
	//		  false : ���Ă���		//
	//----------------------------------//
	bool is_open() const
	{
		return file_.is_open();
	}


	//----------------------------------//
	// ���� : operator>>()				//
	// �p�r : XML�v�f���o��			//
	// ���� : ���o��XML�v�f				//
	// �ߒl : true  : �擾����			//
	//		  false : �擾���s			//
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
	// ���� : document()				//
	// �p�r : XML�����擾				//
	// ���� : �Ȃ�						//
	// �ߒl : XML����					//
	//----------------------------------//
	std::string document() const
	{
		return xmldoc_;
	}

private:

	//----------------------------------//
	// ���� : read()					//
	// �p�r : XML�����Ǎ�				//
	// ���� : �Ȃ�						//
	// �ߒl : XML����					//
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
	// ���� : replace()					//
	// �p�r : ������u��				//
	// ���� : target : �Ώە�����		//
	//		  before : �u����������		//
	//		  after  : �u���㕶����		//
	// �ߒl : �u���ςݕ�����			//
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
	// ���� : remove_trash_space()		//
	// �p�r : �s�v�ȃX�y�[�X�폜		//
	// ���� : �Ώە�����				//
	// �ߒl : �����㕶����				//
	//----------------------------------//
	static std::string remove_trash_space(const std::string& target)
	{
		std::string result(target);

		for (std::string::size_type index = 0; index < result.length(); ++index) {
			bool is_remove = false;

			 std::string::size_type find_index = result.find_first_of(" ", index);

			 if (find_index == std::string::npos)
				 continue;

			 // "< " �� "> "�̃X�y�[�X�폜
			 if (find_index > 0) {
				if (result[find_index -1] == '<' || result[find_index -1] == '>')
					is_remove = true;
			 }

			 // " <" �� " >"�̃X�y�[�X�폜
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
	// ���� : element_analysis()		//
	// �p�r : �v�f���					//
	// ���� : ��͗pXML����				//
	// �ߒl : �Ȃ�						//
	//----------------------------------//
	void element_analysis(const std::string& xmldoc)
	{
		typedef std::string::size_type size_type;
		#define not_found std::string::npos

		for (size_type index = 0; index < xmldoc.length(); ++index) {
			// �v�f������
			size_type start	= xmldoc.find_first_of('<', index);
			if (start == not_found)
				break;

			size_type end = xmldoc.find_first_of('>', start);
			if (end == not_found)
				break;

			// �v�f�����o
			std::string	element_name = xmldoc.substr(start, end - start + 1);

			// �v�f����
			size_type start_elem = end + 1;
			if (start_elem >= xmldoc.length())
				break;

			size_type end_elem = xmldoc.find_first_of('<', start_elem);
			if (end_elem == not_found)
				break;

			std::string elem;
			// ��v�f
			if (element_name.find("/>") != not_found)
				elem = "";
			// �v�f���o
			else
				elem = xmldoc.substr(start_elem, end_elem - start_elem);

			index = end;
			if (!is_element_name(element_name))
				continue;

			attribute_analysis(element_name, elem);
		}
	}


	//----------------------------------//
	// ���� : attribute_analysis()		//
	// �p�r : �������					//
	// ���� : element		: �v�f��	//
	//		  element_value : �v�f		//
	// �ߒl : �Ȃ�						//
	//----------------------------------//
	void attribute_analysis(const std::string& element, const std::string& element_value)
	{
		typedef std::string::size_type size_type;
		#define not_found std::string::npos

		xml_element xmlelem;
		bool		no_attribute = false;

		// �v�f������
		size_type	start_elem	= 1;
		size_type	end_elem	= element.find_first_of(' ', start_elem);
		if (end_elem == not_found) {
			no_attribute = true; // �����Ȃ�
			end_elem = element.find_first_of('>', start_elem);
		}

		// �v�f�����o
		std::string elem_name	= element.substr(start_elem, end_elem - start_elem);

		// �v�f�ݒ�
		xmlelem.element.first	= replace(elem_name, " ", "");
		xmlelem.element.second	= normalize(element_value);

		// �����Ȃ�
		if (no_attribute) {
			if(!element_value.empty())
				element_.push(xmlelem);
			return;
		}

		// ��������
		for (size_type index = 0; index < element.length(); ++index) {
			xml_element::attribute_type attribute;

			// ������
			size_type start_name = element.find_first_of(' ', index);
			if (start_name == not_found)
				break;

			++start_name;

			size_type end_name = element.find_first_of('=', start_name);
			if (end_name == not_found)
				break;

			// ���������o
			std::string attribute_name = element.substr(start_name, end_name - start_name);

			// �����l����
			size_type start_value = end_name + 2;
			size_type end_value   = element.find_first_of('\"', start_value);
			if (end_value == not_found)
				break;

			// �����l���o
			std::string attribute_value = element.substr(start_value, end_value - start_value);

			// �X�y�[�X�폜
			attribute_name  = replace(attribute_name, " ", "");
			attribute_value = normalize(attribute_value);

			xmlelem.attribute[attribute_name] = attribute_value;

			index = end_value;
		}

		// �v�f�ǉ�
		element_.push(xmlelem);
	}


	//----------------------------------//
	// ���� : is_element_name()			//
	// �p�r : �v�f�������f				//
	// ���� : �v�f��					//
	// �ߒl : true  : �v�f��			//
	//		  false : �v�f���ł͂Ȃ�	//
	//----------------------------------//
	static bool is_element_name(const std::string& element_name)
	{
		std::string::size_type length = element_name.length();

		// �R�����g
		if (length >= 3 && element_name.substr(0, 4) == "<!--")
			return false;

		// �I���^�O
		if (length >= 2 && element_name.substr(0, 2) == "</")
			return false;

		// XML�錾
		if (length >= 2 && element_name.substr(0, 2) == "<?")
			return false;

		return true;
	}


	//----------------------------------//
	// ���� : normalize()				//
	// �p�r : ���K��					//
	// ���� : ���K���Ώ�				//
	// �ߒl : ���K���㕶����			//
	//----------------------------------//
	static std::string normalize(const std::string& target)
	{
		std::string result = target;

		// �����́u���p�X�y�[�X�v�u�^�u�v�u���s�v��1���p�X�y�[�X�ɒu��
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
//     map<string, xml_element> addr_book; // �A�h���X��							//
//																					//
//     // �Ǎ�																		//
//     xml_reader  xi("c:\\test.xml");												//
//     xml_element person;															//
//																					//
//     while (xi >> person) {														//
//         addr_book[person.attribute.find("No")->second] = person;					//
//     }																			//
//																					//
//     // �ꗗ�\��																	//
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

