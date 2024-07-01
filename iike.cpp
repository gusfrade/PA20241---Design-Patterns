#include <iostream>

using namespace std;

class Singleton {
private:
    // Private constructor to prevent instantiation
    Singleton() {
        cout << "\nSingleton instance created!" << endl;
    }

public:
    // Static function to get the singleton instance
    static Singleton& getInstance() {

        // Use a static local variable inside an IIFE-like lambda
        
        static Singleton instance = []() {
            return Singleton();
        }();
        
        return instance;
    }

    // Other methods and data members of Singleton class
    void doSomething() {
        cout << "Singleton is doing something." << endl;
    }
};

int main() {
    Singleton& singleton = Singleton::getInstance();
    singleton.doSomething();

    return 0;
}