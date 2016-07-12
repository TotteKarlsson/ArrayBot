#include <iostream>
#include <functional>
#include <vector>
using namespace std;
using namespace tr1;
using std::tr1::placeholders;
using std::tr1::function;

class Foo
{
public:
    bool foo()
    {
        cout << "Hello" << '\n';
        return true;
    }
};

class Bar
{
public:
    bool bar(double nr)
    {
        cout << "Hello"  << nr << '\n';
        return true;
    }
};

int main(int argc, char **argv)
{
    Foo fooO;
    Bar* barO = new Bar;

	typedef function<void (const double& nr)> ClassFunc;

    vector< ClassFunc > collection;

	ClassFunc f1 = bind(&Foo::foo, fooO);
    collection.push_back(f1);

	ClassFunc f2 = bind(&Bar::bar, barO, 23);
    collection.push_back(f2);

    for (int i = 0; i < collection.size(); i++)
    {
        collection[i](1);
    }

    return 0;
}//
//
//#include <iostream>
//#include <vector>
//#include <functional>
//
//using namespace std;
//using namespace tr1;
//
//typedef function< void(void)>  myFunc;
//typedef vector< myFunc > f_list;
//
//f_list f1;
//
//void sayHi();
//void sayNum(int num);
//
//int main()
//{
//    f1.push_back(bind(&sayHi));
//    f1.push_back(bind(&sayNum, 10));
//
//    for (int i = 0; i < f1.size(); i++)
//    {
//        f1.at(i)();
//    }
//}
//
//void sayHi()
//{
//    cout << "hi" << endl;
//}
//
//void sayNum(int num)
//{
//    cout << num << endl;
//}
//

//#include <functional>
//#include <string>
//#include <iostream>
//
//using namespace std;
//using namespace tr1;
//
//void goodbye(const std::string& s)
//{
//    std::cout << "Goodbye " << s << '\n';
//}
//
//class Object {
//public:
//    void hello(const std::string& s)
//    {
//        std::cout << "Hello " << s << '\n';
//    }
//};
//
//int main(int argc, char* argv[])
//{
//    typedef function<void(const string&)> ExampleFunction;
//    Object instance;
//    string str("World");
//    ExampleFunction f = bind(&Object::hello, &instance, placeholders::_1);
//
//    // equivalent to instance.hello(str)
//    f(str);
//
//    f = bind(&goodbye, placeholders::_1);
//
//    // equivalent to goodbye(str)
//    f(str);
//    return 0;
//}
//

