
#include "boost/optional.hpp"
#include <boost/tuple/tuple_io.hpp>
#include "glog/logging.h"
#include "boost/tuple/tuple.hpp"
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include "iostream"

void testTuple() {
    typedef boost::tuple<std::string, int, std::string> People;
    People people("john", 33, "USA");
    People people1("Kate", 33, "UK");
    LOG(INFO) << people;
    LOG(INFO) << people.get<0>() << "   " << people.get<1>() << "   " << people.get<2>() << "   ";
}

boost::optional<int> getNumber(int n) {
    if (n > 1) {
        return boost::optional<int>(n);
    } else {
        return boost::optional<int>();
    }
}

void testAny() {
    try {
        boost::any a = 1.1;
        std::cout << boost::any_cast<int>(a) << '\n';
    }
    catch (boost::bad_any_cast &e) {
        LOG(ERROR) << e.what() << '\n';
    }
}

void testVariant() {
    boost::variant<double, char, std::string> v;
    v = 3.14;
    LOG(INFO) << boost::get<double>(v) << '\n';
    v = 'A';
    LOG(INFO) << boost::get<char>(v) << '\n';
    v = "Boost";
    LOG(INFO) << boost::get<std::string>(v) << '\n';
}


int main() {

    testAny();
    testTuple();
    auto i = getNumber(2);
    if (i) {
        LOG(INFO) << " valid value";
    }

    i = getNumber(0);
    if (!i) {
        LOG(INFO) << " invalid value";
    }

}