#include <iostream>
#include <memory>
#include <ostream>

using namespace std;

/*
 * 参考文章 https://www.cnblogs.com/lidabo/p/17979695
 */

class Test {
  friend ostream& operator<<(ostream& os, const Test& p);

private:
  int a_;

public:
  Test() : a_(0) {}
  void set_a(int a) { a_ = a; }
  int  get_a() const { return a_; }
};

ostream& operator<<(ostream& os, const Test& p) {
  os << "a_ = " << p.a_;
  return os;
}

int main() {
  shared_ptr<Test> p1(new Test); // 创建指向该对象的共享指针
  shared_ptr<Test> p2 =
      make_shared<Test>(*p1); // 创建新的对象，并把地址返回给共享指针类型
  shared_ptr<Test> p3(p1);    // 复制指针
  // p1与p3为同一个指针，p2为不同的指针

  cout << "p1.use_count() = " << p1.use_count() << endl;
  cout << "p2.use_count() = " << p2.use_count() << endl;
  cout << "p3.use_count() = " << p3.use_count() << endl;

  cout << "p1 == p3 = " << (p1 == p3) << endl; // 比较指针指向的地址
  cout << "p1 == p2 = " << (p1 == p2) << endl;

  cout << "p1.get() = " << p1.get() << endl; // 获取指针
  cout << "p2       = " << p2 << endl;
  cout << "p3       = " << p3 << endl;

  p1->set_a(1);

  cout << "*p1.get() = " << *p1.get() << endl;
  cout << "*p2       = " << *p2 << endl;

  //   p1.reset(p2.get()); //
  //   会创建一个新的共享指针，独立于p2，造成二次释放导致非法访问
  p1 = p2;
  cout << p1 << endl;
  cout << p2 << endl;

  cout << "p1.use_count() = " << p1.use_count() << endl;
  cout << "p2.use_count() = " << p2.use_count() << endl;
  cout << "p3.use_count() = " << p3.use_count() << endl;
}