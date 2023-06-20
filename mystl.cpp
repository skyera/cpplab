// 6/10/2023
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"
#include "fakeit.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <set>

int fact(int n) {
    return n <= 1 ? n : fact(n - 1) * n;
}

struct SomeInterface {
    virtual int foo(int) = 0;
    virtual int bar(std::string) = 0;
};

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
