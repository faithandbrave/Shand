#ifndef	INCLUDE_SWITCH_VALUE_
#define INCLUDE_SWITCH_VALUE_

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define switch_ex(value) switch(int switch_value = (value))

#endif	// INCLUDE_SWITCH_VALUE_

//------------------------------------------
// Sample
//------------------------------------------
// int main()
// {
//    int value = 3;
//
//    switch_ex (value) {
//    case 3:
//      cout << switch_value << endl;
//      break;
//    default:
//      break;
//    }
//    return 0;
// }
//
//-----------------------------------------
// 3
//
//
