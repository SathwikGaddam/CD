#include <iostream> 
#include <string> 
using namespace std;
int main()
{
string message;
 int count;
 cout << "Character Count Framing\n";
 cout << "------------------------\n";
 cout << "Enter a message: ";
//  cin >> message;
 getline(cin,message);
 count = message.size();
 cout << "\nSender Side\n";
 cout << "Data Entered : " << message << endl;
 cout << "Character Count : " << count << endl;
 string frame = to_string(count) + message;
 cout << "Frame Created : " << frame << endl;
 cout << "\nReceiver Side\n";
 cout << "Received Frame : " << frame << endl;
 cout << "Count Extracted : " << count << endl;
 cout << "Recovered Data : " << message << endl;
 return 0;
}