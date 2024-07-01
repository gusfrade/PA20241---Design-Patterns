#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * The Handler interface declares a method for building the chain of handlers.
 * It also declares a method for executing a request.
 */
class Handler {
 public:
  virtual Handler *SetNext(Handler *handler) = 0;
  virtual string Handle(string request) = 0;
  virtual ~Handler() {}
};
/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
class AbstractHandler : public Handler {

 public:
  AbstractHandler() : next_handler(nullptr) {
  }
  Handler *SetNext(Handler *handler) {
    this->next_handler = handler;
    return handler;
  }
  string Handle(string request) {
    if (this->next_handler) {
      return this->next_handler->Handle(request);
    }
    return {};
  }

  private:
  Handler *next_handler;
};

//All Concrete Handlers either handle a request or pass it to the next handler in the chain.
class MonkeyHandler : public AbstractHandler {
 public:
  string Handle(string request) override {
    if (request == "Banana") {
      return "Monkey: I'll eat the " + request + ".\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
class SquirrelHandler : public AbstractHandler {
 public:
  string Handle(std::string request) override {
    if (request == "Nut") {
      return "Squirrel: I'll eat the " + request + ".\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
class DogHandler : public AbstractHandler {
 public:
  string Handle(std::string request) override {
    if (request == "MeatBall") {
      return "Dog: I'll eat the " + request + ".\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};

void ClientCode(Handler &handler) {
  vector<string> food = {"Nut", "Banana", "Cup of coffee"};
  for (const string &f : food) {
    cout << "Client: Who wants a " << f << "?\n";
    const string result = handler.Handle(f);
    if (!result.empty()) {
      cout << "  " << result;
    } else {
      cout << "  " << f << " was left untouched.\n";
    }
  }
}
/**
 * The other part of the client code constructs the actual chain.
 */
int main() {
  MonkeyHandler *monkey = new MonkeyHandler;
  SquirrelHandler *squirrel = new SquirrelHandler;
  DogHandler *dog = new DogHandler;
  monkey->SetNext(squirrel)->SetNext(dog);

  /**
   * The client should be able to send a request to any handler, not just the
   * first one in the chain.
   */
  cout << "\nChain: Monkey > Squirrel > Dog\n\n";
  ClientCode(*monkey);
  cout << "\n";
  cout << "Subchain: Squirrel > Dog\n\n";
  ClientCode(*squirrel);

  delete monkey;
  delete squirrel;
  delete dog;

  return 0;
}