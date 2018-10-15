#include <iostream>
#include "Vector.cpp"
#include <vector>
#include <string>
using namespace std;

int main()
{
	
	aisdi::Vector<double> collection = {1410, 753, 1789};

	aisdi::Vector<double> other{std::move(collection)};
	for(auto i: other)
		cout<<i<<endl;
	
	return 0;
}
