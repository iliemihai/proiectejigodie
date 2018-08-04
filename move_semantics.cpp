#include <iostream>     // std::cout
#include <algorithm>    // std::move (ranges)
#include <utility>      // std::move (objects)
#include <vector>       // std::vector
#include <string>       // std::string

class A{
public:
  int x_;
  static int count;
  A() {};
  //A(const A&&) = delete;
  A(int x): x_(x) {}
  A(const A& o): x_(o.x_) {std::cout << "copy cons\n";};
  A(A&& o): x_(std::move(o.x_)) {count++;std::cout << "move cons\n";};

  A& operator=(const A& o)
  {
    std::cout << "assign op\n";
    count++;
    x_ = o.x_;
    return *this;
  }

  A& operator=(A&& o)
  {
    std::cout << "move op\n";
    count++;
    x_ = std::move(o.x_);
    return *this;
  }
};

int A::count = 0;

int main () {
  A a;
  std::vector<A> foo;//{"air","water","fire","earth"};
  foo.push_back(a);
  foo.push_back(a);foo.push_back(a);foo.push_back(a);foo.push_back(a);
  std::vector<A> bar (1);

  // moving ranges:
  std::cout << "Moving ranges...\n";
  std::move ( foo.begin(), foo.end(), bar.begin() );
  
  std::cout << "foo contains " << foo.size() << " elements:";
  std::cout << " (each in an unspecified but valid state)";
  std::cout << '\n';
  std::cout << " mai avem " << a.count<< std::endl;

  return 0;
}
