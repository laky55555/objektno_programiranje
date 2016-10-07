#include <iostream>
#include <vector>

class A {
   public:
      virtual void name() const {  std::cout << "class A" << std::endl; }
};

class B : public A
{
   public:
      virtual void name() const {  std::cout << "class B" << std::endl; }
};

int main()
{
    std::vector<A*> vec_pA;

    A a;
    B b;

    vec_pA.push_back(&a);
    vec_pA.push_back(&b);

    vec_pA[0]->name();
    vec_pA[1]->name();

    return 0;
}
