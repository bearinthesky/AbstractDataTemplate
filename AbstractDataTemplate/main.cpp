#include <iostream>
using namespace std;
#include "Vector.h"

int main() {
	int a[5] = { 1,2,3,4,5 };
	Vector<int> test(a, 0, 5);
	for (int i = 0; i < test.size(); i++)
		cout << test[i] << endl;
	return 0;
}