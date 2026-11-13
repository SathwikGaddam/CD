
#include <iostream>
#include <map>
#include <string>
#include <cctype>
using namespace std;

map<pair<char, char>, string> table;

int main()
{
    // Initialize predictive parsing table
    table[make_pair('E', 'i')] = "TR";
    table[make_pair('E', '(')] = "TR";

    table[make_pair('R', '+')] = "+TR";
    table[make_pair('R', ')')] = "#";
    table[make_pair('R', '$')] = "#";

    table[make_pair('T', 'i')] = "FY";
    table[make_pair('T', '(')] = "FY";

    table[make_pair('Y', '*')] = "*FY";
    table[make_pair('Y', '+')] = "#";
    table[make_pair('Y', ')')] = "#";
    table[make_pair('Y', '$')] = "#";

    table[make_pair('F', 'i')] = "i";
    table[make_pair('F', '(')] = "(E)";

    string input, st = "$E";
    int ip = 0;

    cout << "Enter the input string (use i for identifier): ";
    cin >> input;

    input += '$';

    cout << "\nStack\t\tInput\t\tAction\n";
    cout << "---------------------------------------------\n";

    while (!st.empty())
    {
        char X = st[st.length() - 1];
        char a = input[ip];

        cout << st << "\t\t" << input.substr(ip) << "\t\t";

        if (X == '$' && a == '$')
        {
            cout << "Accept\n";
            return 0;
        }

        if (X == a)
        {
            st.erase(st.length() - 1);
            ip++;

            cout << "Match " << a << "\n";
        }
        else if (isupper((unsigned char)X) && table.count(make_pair(X, a)))
        {
            string rhs = table[make_pair(X, a)];

            st.erase(st.length() - 1);

            cout << X << " -> ";

            if (rhs == "#")
                cout << "epsilon\n";
            else
                cout << rhs << "\n";

            if (rhs != "#")
            {
                for (int i = rhs.length() - 1; i >= 0; i--)
                {
                    st += rhs[i];
                }
            }
        }
        else
        {
            cout << "Error\n";
            return 0;
        }
    }

    cout << "Rejected\n";

    return 0;
}
