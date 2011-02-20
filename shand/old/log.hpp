//------------------------------------------------------//
// Name : simple_log									//
// Desc : �ȈՃ��O�o��									//
// Note : �o�̓t�@�C������ log.txt						//
//														//
// Version : 1.00 2006/08/04 �쐬						//
//														//
//				Programmed By Akira.T					//
//		Copyright(C) 2006 Akira.T All rights reserved	//
//														//
//------------------------------------------------------//

#ifndef SHAND_SIMPLE_LOG_INCLUDE
#define SHAND_SIMPLE_LOG_INCLUDE

#include <fstream>

namespace shand {
	template <class Type>
	void simple_log(const Type& output)
	{
		std::fstream file("log.txt", std::ios::out | std::ios::app);

		file << output << std::endl;
	}
} // namespace shand

#endif // SHAND_SIMPLE_LOG_INCLUDE

//----------------------------------|
//			How to use				|
//----------------------------------|
//									|
//	simple_log(314);				|
//	simple_log(3.14);				|
//	simple_log("abc");				|
//									|
//----------------------------------|
