#include "iostream"
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    std::vector<int> v;
    std::cout << "vector size =" << v.size() << std::endl;

    for (size_t i = 0; i < 5; i++) {
        v.push_back(i);
    }

    std::cout << "Extended Vector size " << v.size() << std::endl;

    for (size_t i = 0; i < 5; i++) {
        std::cout << "Vector v[" << i << "] = "<< v[i] << std::endl;
    }

    vector<int>::iterator vi = v.begin();
    while (vi != v.end()) {
        std::cout << "Square = " << (*vi)*(*vi)  << std::endl;
        vi++;
    }

    return 0;
}
