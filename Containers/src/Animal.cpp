#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/member.hpp>
#include <string>
#include <vector>
#include <iostream>

struct animal {
    std::string name;
    int legs;
    bool has_tail;
};
using namespace boost::multi_index;
typedef multi_index_container<
        animal,
        indexed_by<
                sequenced<>,
                ordered_non_unique<member<animal, int, &animal::legs>>,
                hashed_non_unique<boost::multi_index::member<animal, std::string, &animal::name> >,
                ordered_non_unique<member<animal, bool, &animal::has_tail>>
        >
> animal_multi;

class animals_container {
public:
    animal_multi _container;

    void add(animal a) {
        _container.push_back(a);
    }

    const animal *find_by_name(const std::string &name) const {
        auto item = _container.get<2>().find(name);
        return item.operator->();
    }

    std::vector<animal> find_by_legs(int from, int to) const {
        auto &index = _container.get<1>();
        auto it = index.lower_bound(from);
        auto end = index.upper_bound(to);
        std::vector<animal> result;
        for (; it != end; ++it)
            result.push_back(*it.operator->());
        return result;
    }

    std::vector<animal> find_by_tail(bool has_tail) const {
        auto &index = _container.get<3>();
        int n = index.count(has_tail);
        std::vector<animal> result;
        auto it = index.find(has_tail);
        if (n > 0) {
            for (int i = 0; i < n; ++i) {
                result.push_back(*it.operator->());
                it++;
            }
        }
        return result;
    }
};

int main() {
    animals_container animals;
    animals.add({"cat", 4, true});
    animals.add({"ant", 6, false});
    animals.add({"spider", 8, false});
    animals.add({"shark", 0, false});

    const animal *a = animals.find_by_name("cat");
    if (a)
        std::cout << "cat has " << a->legs << " legs\n";

    auto animals_with_6_to_8_legs = animals.find_by_legs(6, 9);
    for (auto a : animals_with_6_to_8_legs)
        std::cout << a.name << " has " << a.legs << " legs\n";

    auto animals_without_tail = animals.find_by_tail(false);
    for (auto a : animals_without_tail)
        std::cout << a.name << " has  tail\n";
}