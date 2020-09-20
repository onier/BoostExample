
#include <boost/intrusive/list.hpp>
#include <string>
#include <utility>
#include <iostream>
#include "glog/logging.h"

using namespace boost::intrusive;

struct animal : public list_base_hook<> {
    std::string name;
    int legs;

    animal(std::string n, int l) : name{std::move(n)}, legs{l} {}

    animal(const animal &animal1) {
        this->name = animal1.name;
        this->legs = animal1.legs;
        LOG(INFO) << " print animal ";
    }
};

int main() {
    animal a1{"cat", 4};
    animal a2{"shark", 0};
    animal a3{"spider", 8};
    std::vector<animal> animal_vector;
    animal_vector.push_back(a1);
    typedef list<animal> animal_list;
    animal_list animals;

    animals.push_back(a1);
    animals.push_back(a2);
    animals.push_back(a3);

    a1.name = "dog";

    for (const animal &a : animals)
        std::cout << a.name << '\n';
}