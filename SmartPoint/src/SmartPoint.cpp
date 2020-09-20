#include <boost/scoped_ptr.hpp>
#include <iostream>
#include <boost/exception/detail/shared_ptr.hpp>
#include "boost/make_shared.hpp"
#include "boost/weak_ptr.hpp"

struct Node {
    boost::weak_ptr<Node> next;
//    boost::shared_ptr<Node> next;
};

void test_scoped_ptr() {
    boost::scoped_ptr<int> p{new int{1}};
    std::cout << *p << '\n';
    p.reset(new int{2});
    std::cout << *p.get() << '\n';
    p.reset();
    std::cout << std::boolalpha << static_cast<bool>(p) << '\n';
}

boost::shared_ptr<int> test_shared_ptr() {
    boost::shared_ptr<int> p{new int{1}};
    std::cout << *p << '\n';
    p.reset(new int{2});
    std::cout << *p.get() << '\n';
//    p.reset();
    std::cout << std::boolalpha << static_cast<bool>(p) << '\n';
    return p;
}

int main() {
//    int * a = new int{1};
//    test_scoped_ptr();
//    auto ret = test_scoped_ptr();
//    auto ret = test_shared_ptr();
    boost::shared_ptr<Node> node1 = boost::make_shared<Node>();
    boost::shared_ptr<Node> node2 = boost::make_shared<Node>();
    node1->next = node2;
    node2->next = node1;
}