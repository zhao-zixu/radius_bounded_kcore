#include <bits/stdc++.h>
namespace customized_iterators {
  template<long FROM, long TO>
  class Range {
    public:
    // member typedefs provided through inheriting from std::iterator
    class iterator : public std::iterator<std::forward_iterator_tag, // iterator_category
    long,                      // value_type
    long,                      // difference_type
    const long *,              // pointer
    const long &               // reference
      > {
      long num = FROM;

      public:
      iterator(long _num = 0)
        : num(_num) {}
      iterator &operator++() {
        num = TO >= FROM ? num + 1 : num - 1;
        return *this;
      }
      iterator operator++(int) {
        iterator ret_val = *this;
        ++(*this);
        return ret_val;
      }
      bool operator==(iterator other) const { return num == other.num; }
      bool operator!=(iterator other) const { return !(*this == other); }
      long operator*() { return num; }
    };
    iterator begin() { return FROM; }
    iterator end() { return TO >= FROM ? TO + 1 : TO - 1; }
  };

  void test_range() {
    Range<5, 13> r;
    for (auto v : r) std::cout << v << ',';
    std::cout << '\n';
  }
}
int main(){
    customized_iterators::test_range();
    return 0;
}
