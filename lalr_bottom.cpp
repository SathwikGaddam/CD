
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ACTION function
int action(int state, char ch)
{
    switch(state)
    {
        case 0:
        case 1:
        case 3:
            if(ch == 'c')
                return 3;
            if(ch == 'd')
                return 4;
            break;

        case 2:
            if(ch == '$')
                return 100;
            break;

        case 4:
            if(ch == 'c' || ch == 'd' || ch == '$')
                return -3;
            break;

        case 5:
            if(ch == '$')
                return -1;
            break;

        case 6:
            if(ch == 'c' || ch == 'd' || ch == '$')
                return -2;
            break;
    }

    return 0;
}

// GOTO function
int goTo(int state, char ch)
{
    if(state == 0 && ch == 'C')
        return 1;

    if(state == 0 && ch == 'S')
        return 2;

    if(state == 1 && ch == 'C')
        return 5;

    if(state == 3 && ch == 'C')
        return 6;

    return -1;
}

// Parsing function
void parse(string input)
{
    input += '$';

    vector<int> st;
    st.push_back(0);

    int i = 0;

    cout << "\nParsing Steps:\n";

    while(i < input.length())
    {
        int s = st.back();
        char ch = input[i];

        int act = action(s, ch);

        cout << "State: " << s
             << " Input: " << input.substr(i);

        // Error condition
        if(act == 0)
        {
            cout << " Action: ERROR\n";
            cout << "\nString Rejected!\n";
            return;
        }

        // Accept condition
        if(act == 100)
        {
            cout << " Action: ACCEPT\n";
            cout << "\nString Accepted!\n";
            return;
        }

        // Shift operation
        if(act > 0)
        {
            cout << " Action: s" << act << "\n";

            st.push_back(act);
            i++;
        }

        // Reduce operation
        else
        {
            int p = -act;
            int len;

            if(p == 1)
            {
                cout << " Action: r1 (S -> CC)\n";
                len = 2;
            }
            else if(p == 2)
            {
                cout << " Action: r2 (C -> cC)\n";
                len = 2;
            }
            else
            {
                cout << " Action: r3 (C -> d)\n";
                len = 1;
            }

            // Pop states
            while(len--)
            {
                st.pop_back();
            }

            // Find next state using GOTO
            int ns = goTo(st.back(),
                          p == 1 ? 'S' : 'C');

            if(ns == -1)
            {
                cout << "\nString Rejected!\n";
                return;
            }

            st.push_back(ns);
        }
    }
}

// Main function
int main()
{
    string input;

    cout << "Grammar:\n";
    cout << "S -> CC\n";
    cout << "C -> cC\n";
    cout << "C -> d\n";

    cout << "\nEnter input string: ";
    cin >> input;

    parse(input);

    return 0;
}
