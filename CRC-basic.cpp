#include<bits/stdc++.h>
using namespace std;

string xordiv(string data, string generator)
{
    string temp = data;

    for(int i = 0; i <= data.size() - generator.size(); i++)
    {
        if(temp[i] == '1')
        {
            for(int j = 0; j < generator.size(); j++)
            {
                if(temp[i+j] == generator[j])
                    temp[i+j] = '0';
                else
                    temp[i+j] = '1';
            }
        }
    }

    return temp.substr(data.size() - generator.size() + 1);
}

string wordtobinary(string data)
{
    string res = "";

    for(char ch : data)
    {
        unsigned char c = ch;

        for(int j = 7; j >= 0; j--)
        {
            if(c & (1 << j))
                res += '1';
            else
                res += '0';
        }
    }

    return res;
}

int main()
{
    string data;

    cin >> data;

    // Basic CRC generator
    string generator = "10011";

    string binary = wordtobinary(data);

    cout << "Binary Data : " << binary << endl;

    string padded = binary;

    // Append generator length - 1 zeros
    for(int i = 0; i < generator.size() - 1; i++)
    {
        padded += '0';
    }

    string remainder = xordiv(padded, generator);

    cout << "CRC Remainder : " << remainder << endl;

    cout << "Transmitted Data : "
         << binary + remainder << endl;

    return 0;
}
