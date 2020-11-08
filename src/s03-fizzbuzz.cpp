#include <iostream>
#include <string>
using namespace std;

auto main(int, char* argv[]) -> int
{
   auto n = stoi(argv[1]);
    for (auto i = 1; i <= n; ++i) {    
        auto a = i % 3;
        auto b = i % 5;
        cout << endl << i;
        if (a == 0 && b == 0) {cout << "FizzBuzz";}
            else {
            if (a == 0) {cout << "Fizz";}
            if (b == 0) {cout << "Buzz";}
            }
    }
cout << endl;
return 0;
}
