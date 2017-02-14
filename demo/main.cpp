#include <iostream>
#include <map>
#include <unordered_map>

class Foo
{
public:
    static int get(void)
    {
        return 0;
    }
};

class Bar
{
public:
    static  const char* get(void)
    {
        return "0";
    }
};

template <class A>
void func(void)
{
    auto val = A::get();
}
void mapC98()
{
    std::map<double,double> resultMap;
    std::map<double,double >::iterator it = resultMap.begin();
    for(; it != resultMap.end();++it)
    {

    }
}

void mapC11()
{
    std::map<double ,double > resultMap;
    for(auto it = resultMap.begin(); it != resultMap.end();++it)
    {

    }

}

void unordered_multimap_c98()
{
    int key = 10;
    std::unordered_multimap<int,int> resultMap;

    std::pair<std::unordered_multimap<int,int>::iterator,std::unordered_multimap<int,int>::iterator>
            range = resultMap.equal_range(key);

}

void unordered_multimap_c11()
{
    int key = 10;
    std::unordered_multimap<int,int> map;

    auto range = map.equal_range(key);
}
#include "Kthread.h"
int main() {
    // std::cout << "Hello, World!" << std::endl;
    // func<Foo>();
    // func<Bar>();
    //thread_test1();
    //mutex_test();
    //time_mutex_test();
    //unique_lock_test();
    //lock_guard_test();
    lock_guard_exception_test();
    return 0;
}