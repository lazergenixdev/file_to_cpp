#include <iostream>
#include <string>
using namespace std;

namespace test {
#include "test_data.inl"
}

int main() {
	cout << string((char*)test::data, test::size);
	return 0;
}
