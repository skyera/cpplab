// 6/10/2023
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"
#include "fakeit.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <set>
#include <limits>
#include <thread>

int fact(int n) {
    return n <= 1 ? n : fact(n - 1) * n;
}

struct SomeInterface {
    virtual int foo(int) = 0;
    virtual int bar(std::string) = 0;
};

template<class T>
inline const T& max(const T& a, const T& b)
{
    return a < b ? b : a;
}

class Q {
public:
    typedef int SubType;
};

template <class T>
class MyClass {
private:
    T value;
public:
    // copy ctor with implicit type conversion
    template<class U>
    MyClass(const MyClass<U>& x) {
        value = x.getValue();
    }

    MyClass() {
    }

    template<class X>
    void assign(const MyClass<X>& x) {
        value = x.getValue();
    }

    T getValue() const {
        return value;
    }
};

enum struct Visible {True, False};

TEST_CASE("testing the factorial function") {
    CHECK(fact(0) == 1); // should fail
    CHECK(fact(1) == 1);
    CHECK(fact(2) == 2);
    CHECK(fact(3) == 6);
    CHECK(fact(10) == 3628800);
}

TEST_CASE("bench") {
    double d = 1.0;
    ankerl::nanobench::Bench().run("some double ops", [&] {
            d += 1.0 / d;
            if (d > 5.0) {
            d -= 5.0;
            }
            ankerl::nanobench::doNotOptimizeAway(d);
            });
}

TEST_CASE("fake") {
    fakeit::Mock<SomeInterface> mock;
    fakeit::When(Method(mock,foo)).Return(1); // Method mock.foo will return 1 once.
    SomeInterface &i = mock.get();
    std::cout << i.foo(0);
}

int transmogrify(int x) {
    return 2 * x;
}

TEST_CASE("item30") {
    std::vector<int> values{1,2,3};
    std::vector<int> results;
    results.reserve(3);

    std::transform(values.begin(), values.end(),
            std::back_inserter(results), transmogrify);
    std::vector<int> out{2,4,6};
    REQUIRE(results == out);
    std::cout << results.size() << "\n";
}

TEST_CASE("reserve") {
    std::vector<int> values{1,2,3};
    std::vector<int> results;

    SUBCASE("back_inserter") {
        results.reserve(3);
        std::transform(values.begin(), values.end(),
                std::back_inserter(results), transmogrify);
    }

    SUBCASE("resize") {
        results.resize(3);
        std::transform(values.begin(), values.end(),
                results.begin(), transmogrify);
    }

    std::cout << "size: " << results.size() << "\n";
    for (auto& item: results) {
        std::cout << item << "\n";
    }
}

inline bool doublegreater(double d1, double d2) {
    return d1 > d2;
}

TEST_CASE("sort") {
    std::vector<double> v{4.1,2.3, 5.8};

    SUBCASE("greater") {
        std::sort(v.begin(), v.end(), std::greater<double>());
    }

    SUBCASE("doublegreater") {
        std::sort(v.begin(), v.end(), doublegreater);
    }

    for (auto& item: v) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

struct StringSize:
    public std::unary_function<std::string, std::string::size_type>
{
    std::string::size_type operator()(const std::string& s) const
    {
        return s.size();
    }
};

template<typename FPType>
FPType average(FPType val1, FPType val2) {
    return (val1 + val2) / 2;
}


template<typename FPType>
struct Average:
    public std::binary_function<FPType, FPType, FPType> {
    FPType operator()(FPType val1, FPType val2) const
    {
        return average(val1, val2);
    }
};

template<typename InputIter1,
         typename InputIter2>
void writeaverages(InputIter1 begin1,
                   InputIter1 end1,
                   InputIter2 begin2,
                   std::ostream& s)
{
    /* std::transform(begin1, end1, begin2, */
    /*         std::ostream_iterator<typename iterator_traits<InputIter1>::value_type>(s, "\n"), */
    /*         average<typename iterator_traits<InputIter1>::value_type>); */
    /* std::transform(begin1, end1, begin2, */
    /*         std::ostream_iterator<typename iterator_traits<InputIter1>::value_type>(s, "\n"), */
    /*         Average<typename iterator_traits<InputIter1::value_type>()); */
}

TEST_CASE("mem_fun_ref") {
    std::set<std::string> s{"abc", "ef"};

    SUBCASE("mem_fun_ref") {
        std::transform(s.begin(), s.end(),
                std::ostream_iterator<std::string::size_type>(std::cout, "\n"),
                std::mem_fun_ref(&std::string::size));
    }

    SUBCASE("unary_function") {
        std::transform(s.begin(), s.end(),
                std::ostream_iterator<std::string::size_type>(std::cout, "\n"),
                StringSize());
    }
}

TEST_CASE("max") {
    int a = 3;
    int b = 4;
    int result = max(a, b);
    REQUIRE(result == 4);
}

void throw_logic_error()
{
    std::string err_msg("error");
    throw std::logic_error(err_msg);
}

TEST_CASE("logic_error") {
    REQUIRE_THROWS_AS(throw_logic_error(), std::logic_error);
}

TEST_CASE("MyClass") {
    MyClass<double> d;
    MyClass<int> i;

    d.assign(d);
    d.assign(i);

    MyClass<double> xd;
    MyClass<double> xd2(xd);
    MyClass<int> xi(xd);
}

TEST_CASE("explicit_init") {
    int i1;
    int i2 = int();
    CHECK(i1 != 0);
    CHECK(i2 == 0);
}

TEST_CASE("limits") {
    std::cout << std::boolalpha;

    std::cout << "max(short): " << std::numeric_limits<short>::max() <<
        std::endl;
    std::cout << "max(int): " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "max(long): " << std::numeric_limits<long>::max() << std::endl;
    std::cout << "max(float): " << std::numeric_limits<float>::max() <<
        std::endl;
    std::cout << "max(double): " << std::numeric_limits<double>::max()
        << std::endl;
    std::cout << "max(long double): " << std::numeric_limits<long double>::max()
        << std::endl;
    std::cout << "is_signed(char): " << std::numeric_limits<char>::is_signed <<
        std::endl;
    std::cout << "is_specialized(string): "
        << std::numeric_limits<std::string>::is_specialized << std::endl;
}

bool int_ptr_less(int* a, int* b)
{
    return *a < *b;
}

TEST_CASE("max") {
    int x = 17;
    int y = 42;
    int* px = &x;
    int* py = &y;
    int *pmax;

    pmax = std::max(px, py, int_ptr_less);
    REQUIRE(*pmax == y);
}

TEST_CASE("max2") {
    int x = 3;
    long y = 4;

    int result = std::max<long>(x, y);
    REQUIRE(result == y);
}

TEST_CASE("enum") {
    Visible v = Visible::True;

    std::cout << "v: " << (int)v << std::endl;
}

TEST_CASE("atomic") {
    int y = 0;
    std::atomic<int> x(0);
    ankerl::nanobench::Bench().run("compare_exchange_strong", [&] {
            x.compare_exchange_strong(y, 0);
            });
}

TEST_CASE("tutorial_fast_v2") {
    uint64_t x = 1;
    ankerl::nanobench::Bench().run("++x", [&]() {
        ankerl::nanobench::doNotOptimizeAway(x += 1);
    });
}

TEST_CASE("tutorial_slow_v1") {
    ankerl::nanobench::Bench().run("sleep 100ms, auto", [&] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });
}

TEST_CASE("tutorial_slow_v2") {
    ankerl::nanobench::Bench().epochs(3).run("sleep 100ms", [&] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });
}
