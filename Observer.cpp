#include <iostream>
#include <list>
#include <string>

using namespace std;

class Observer {
  public:
    virtual ~Observer(){};
    virtual void Update(const string &message_from_subject) = 0;
};

class Subject {
  public:
    virtual ~Subject(){};
    virtual void Attach(Observer *observer) = 0;
    virtual void Detach(Observer *observer) = 0;
    virtual void Notify() = 0;
};


class BookShop : public Subject {
  public:
    virtual ~BookShop() {}


  //The subscription management methods.
  void Attach(Observer *client) {
    list_clients.push_back(client);
  }
  void Detach(Observer *client) {
    list_clients.remove(client);
  }
  void Notify() {
    list<Observer *>::iterator iterator = list_clients.begin();
    HowManyObserver();
    while (iterator != list_clients.end()) {
      (*iterator)->Update(message);
      ++iterator;
    }
  }

  void HowManyObserver() {
    std::cout << "There are " << list_clients.size() << " clients in the list.\n";
  }

  //method to create a notification of a new book in the store
  void NewBookAvaible(string new_book) {
    this->message = "There is  a new book avaible: " + new_book;
    Notify();
  }

 private:
  list<Observer *> list_clients;
  string message;
};

class Client : public Observer {
 public:
  Client(BookShop &bookshop_) : store(bookshop_) {
    this->store.Attach(this);
    cout << "Hi, I'm the Client \"" << ++Client::static_number << "\".\n";
    this->number = Client::static_number;
  }

  virtual ~Client() {}

  void Update(const string &message_from_subject_) {
    this->message_from_subject = message_from_subject_;
    PrintInfo();
  }
  
  void RemoveMeFromTheList() {
    store.Detach(this);
    cout << "Client \"" << number << "\" removed from the list.\n";
  }
  void PrintInfo() {
    cout << "Client \"" << this->number << "\": a new message is available --> " << this->message_from_subject << "\n";
  }

 private:
  string message_from_subject;
  BookShop& store;
  static int static_number;
  int number;
};

int Client::static_number = 0;

void ClientCode() {
  BookShop *subject = new BookShop;
  Client *observer1 = new Client(*subject);
  Client *observer2 = new Client(*subject);
  Client *observer3 = new Client(*subject);
  Client *observer4;
  Client *observer5;

  subject->NewBookAvaible("\"Lord of The Rings\"");
  observer3->RemoveMeFromTheList();

  subject->NewBookAvaible("\"Signal Processing and Linear Systems\"");
  observer4 = new Client(*subject);

  observer2->RemoveMeFromTheList();
  observer5 = new Client(*subject);

  subject->NewBookAvaible("\"Dive Into Design Patterns\"");
  observer5->RemoveMeFromTheList();

  observer4->RemoveMeFromTheList();
  observer1->RemoveMeFromTheList();

  delete observer5;
  delete observer4;
  delete observer3;
  delete observer2;
  delete observer1;
  delete subject;
}

int main() {
  ClientCode();
  return 0;
}