#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string a = "";
    stringstream ssr(a);
    string val;
    std::getline(ssr, val, ' ');
    cout << val << val.size() << endl;
}