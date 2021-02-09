//
//  bit_stream_helper.hpp
//  flac
//
//  Created by Uahh on 2021/2/2.
//

#ifndef bit_stream_helper_hpp
#define bit_stream_helper_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

class C_BIT_HELPER
{
public:
    C_BIT_HELPER() = default;
    int char2Int(char c);
    void debugCoutHexStream(string hex_stream);
    void debugCoutHexStream(char* hex_stream);
    string decInt2HexStr(long long num);
    int bitStream2Int(string num_str);
    int charArray2Int(char* num);
    int charArray2Int(char* num, int x);
    int charArray2Int(string num);
    
};


#endif /* bit_stream_helper_hpp */
