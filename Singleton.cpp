#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Singleton
{
private:
    Singleton(const string value_): value(value_){}

    static Singleton* singleton_;

    std::string value;

public:

    
    //Singletons should not be cloneable.
    Singleton(Singleton &other) = delete;

    //Singletons should not be assignable.
    void operator=(const Singleton &) = delete;

    static Singleton *GetInstance(const string& value);
    
    //testing if the singleton is unique
    void WhoAmI()
    {
        cout << "I am a Singleton and my value is "  << this->getValue() << endl << endl;
    }

    string getValue() const{
        return value;
    } 
};

//This is a safer way to create an instance. instance = new Singleton is
//dangeruous in case two instance threads wants to access at the same time
Singleton* Singleton::singleton_= nullptr;;
Singleton *Singleton::GetInstance(const std::string& value)
{
    if(singleton_==nullptr){
        singleton_ = new Singleton(value);
    }
    return singleton_;
}



void Process_1(){
    Singleton* singleton = Singleton::GetInstance("Process 1");
    cout << "I am Process 1 and I created a singleton" << endl; 
    singleton->WhoAmI();
}

void Process_2(){
    Singleton* singleton = Singleton::GetInstance("Process 2");
    cout << "I am Process 2 and I created a singleton" << endl; 
    singleton->WhoAmI();
}


int main()
{
    cout <<"\nIf both Process see the same value, then Singleton was reused\n" <<
            "If they see different values, then 2 Singletons were created\n\n" <<
            "RESULT:\n" << endl;   

    Process_1();
    Process_2();

    return 0;
}