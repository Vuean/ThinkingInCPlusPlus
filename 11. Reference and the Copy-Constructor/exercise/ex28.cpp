#include <iostream>
#include <vector>
using namespace std;

class SomeFuncs 
{
public:
    void function1() { cout << "SomeFuncs::function1() called." << endl; }
    void function2() { cout << "SomeFuncs::function2() called." << endl; }
    void function3() { cout << "SomeFuncs::function3() called." << endl; }
};

// typedef  返回类型(*新类型)(参数表)
typedef void (SomeFuncs::*function_ptr)();

class FuncStorage 
{
public:
    FuncStorage() : storage(), s() {}
    void add(function_ptr p) { storage.push_back(p); }
    void remove() { storage.pop_back(); }

    void run()
    {
        for (int i = 0; i < storage.size(); i++)
            (&s->*storage[i])();
    }

private:
    vector<function_ptr> storage;
    SomeFuncs s;
};

int main() 
{
    FuncStorage obj;

    obj.add(&SomeFuncs::function1);
    obj.add(&SomeFuncs::function2);
    obj.add(&SomeFuncs::function3);

    obj.run();

    obj.remove();

    obj.run();

    return 0;
}