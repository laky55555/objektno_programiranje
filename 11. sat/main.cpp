#include <iostream>
#include <string>
#include <vector>

#include "aux1.h"
#include "smartptr.h"


int main(void)
{
    SmartPtr<int> p1;
    SmartPtr<int> p2(new int(5));
    p2 = p1;
    p1 =  makeSmartPtr<int>(5);
    TEST(*p1 == 5);
    SmartPtr<A>  p5(new B);
    SmartPtr<A>  p6(p5);
    TEST(p6->name == "_");
    TEST(p6.use_count() == 2);
    SmartPtr<A>  p61(p6);
    TEST(p5.use_count() == 3);

    int x = 3;
    std::string ss = "xyz";
    cout<< p6.use_count() <<"   222\n";
    p6 = makeSmartPtr<B>(ss,x);
    cout<< p6.use_count() <<"   222\n";
    TEST(p6.use_count() == 1);
    TEST(p5.use_count() == 2);

    //TEST(dynamic_cast<B*>(p6.get())->z == 3);

    SmartPtr<B>  p7(new B("zzz",11));
    TEST(p7->name == std::string("zzz_"));

    SmartPtr<A>  p8(p7);
    TEST(p8->name == std::string("zzz_"));
    p8->name= "4";
    p8 = std::move(p8);
    TEST(p8->name == std::string("4"));
    SmartPtr<A> p9 = makeSmartPtr<B>(std::string("eee"),x);
    SmartPtr<B> p91;
    p9 = p91;
    std::vector< SmartPtr<A> > vec;
    vec.push_back(p5);
    cout<<"333";
        cout<< p7.use_count() <<"   222\n";

    vec.push_back(p7);
    cout<<"444";
    TEST( vec[0]->f() == 'B');
    TEST( vec[1]->f() == 'B');

/*
    SmartPtr<int[]> p10(new int[10]);
    p10[4] = 3;
    SmartPtr<int[]> p11(p10);
    TEST(p11[4] == 3);
    p10[0] = 7;
    p11 = p10;
    TEST(p11[0] == 7);


    SmartPtr<B[]> p12(new B[2]);
    SmartPtr<A[]> p13(new A[2]);
    p13 = p12;
*/
    return 0;
}
/*

int main (void)
{
    SmartPtr<int> p1;
    SmartPtr<int> p2(new int(5));
    p2 = p1;
    p1 =  makeSmartPtr<int>(5);
    TEST(*p1 == 5);

    SmartPtr<A>  p5(new B);
    SmartPtr<A>  p6(p5);
    TEST(p6->name == "_");
    TEST(p6.use_count() == 2);
    SmartPtr<A>  p61(p6);
    TEST(p5.use_count() == 3);

    int x = 3;
    std::string ss = "xyz";
    p6 = makeSmartPtr<B>(ss,x);
    TEST(p6.use_count() == 1);
    TEST(p5.use_count() == 2);

    TEST(dynamic_cast<B*>(p6.get())->z == 3);

    SmartPtr<B>  p7(new B("zzz",11));
    TEST(p7->name == std::string("zzz_"));
    return 0;
}*/
