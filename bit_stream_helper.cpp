//
//  bit_stream_helper.cpp
//  flac
//
//  Created by Uahh on 2021/2/2.
//

#include "bit_stream_helper.hpp"
    
int C_BIT_HELPER::char2Int(char c)
    {
        return (int)(unsigned char)c;
    }
    
void C_BIT_HELPER::debugCoutHexStream(string hex_stream)
{
    for(auto i : hex_stream)
    {
        cout << hex << char2Int(i) << ' ';
    }
    cout << endl;
}

void C_BIT_HELPER::debugCoutHexStream(char* hex_stream)
{
    string input_metadata_data = "";
    for(int i = 0; i < sizeof(hex_stream); i++)
     {
         input_metadata_data += hex_stream[i];
     }
    for(auto i : input_metadata_data)
    {
        cout << hex << char2Int(i) << ' ';
    }
    cout << endl;
}

string C_BIT_HELPER::decInt2HexStr(long long num)
{
    string str;
    if(num == 0)
        str += '0';
    long long Temp = num / 16;
    int left = num % 16;
    if (Temp > 0)
        str += decInt2HexStr(Temp);
    if (left < 10)
        str += (left + '0');
    else
        str += ('A' + left - 10);

    return str;
}

int C_BIT_HELPER::bitStream2Int(string num_str)
{
    int coe = 1;
    int ans = 0;
    for(auto i : num_str)
    {
        ans += (int)(i - '0') * coe;
        coe *= 2;
    }
    return ans;
}

int C_BIT_HELPER::charArray2Int(char* num)
{
    string num_str = "";
    for(int i = 0; i < sizeof(num)/2 - 1; i++)
    {
        int temp = char2Int(num[i]);
        string sub_str = decInt2HexStr(temp);
        if(sub_str.size() == 1)
            sub_str = "0" + sub_str;
        num_str += sub_str;
    }
    int coe = 1;
    int ans = 0;
    reverse(num_str.begin(), num_str.end());
    for(auto i : num_str)
    {
        if((int)i >= 'A')
            ans += ((int)(i - 'A') + 10) * coe;
        else
            ans += (int)(i - '0') * coe;
        coe *= 16;
    }
    return ans;
}

int C_BIT_HELPER::charArray2Int(char* num, int x)
{
    string num_str = "";
    for(int i = 0; i < x; i++)
    {
        int temp = char2Int(num[i]);
        string sub_str = decInt2HexStr(temp);
        if(sub_str.size() == 1)
            sub_str = "0" + sub_str;
        num_str += sub_str;
    }
    int coe = 1;
    int ans = 0;
    reverse(num_str.begin(), num_str.end());
    for(auto i : num_str)
    {
        if((int)i >= 'A')
            ans += ((int)(i - 'A') + 10) * coe;
        else
            ans += (int)(i - '0') * coe;
        coe *= 16;
    }
    return ans;
}

int C_BIT_HELPER::charArray2Int(string num)
{
    string num_str = "";
    for(int i = 0; i < num.size(); i++)
    {
        int temp = char2Int(num[i]);
        string sub_str = decInt2HexStr(temp);
        if(sub_str.size() == 1)
            sub_str = "0" + sub_str;
        num_str += sub_str;
    }
    int coe = 1;
    int ans = 0;
    reverse(num_str.begin(), num_str.end());
    for(auto i : num_str)
    {
        if((int)i >= 'A')
            ans += ((int)(i - 'A') + 10) * coe;
        else
            ans += (int)(i - '0') * coe;
        coe *= 16;
    }
    return ans;
}
