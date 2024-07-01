#include <vector>
#include <string>
#include <iostream>

using namespace std;

//virtual generic class to serve as base for future implementations of the transport method
class Vehicle {
	public:
		virtual ~Vehicle() {}
		virtual string getName() = 0;
		virtual string Transport() = 0;
};

//concrete implamantations of transport method
class Truck : public Vehicle {
	public:
		string getName() {return this->name ; }
   	string Transport() { return "{land}"; }
	private:
		string name = "Truck";
};
class Ship : public Vehicle {
	public:
		string getName() {return this->name ; }
		string Transport() { return "{sea}"; }
	private:
		string name = "Ship";
};
class Plane : public Vehicle {
	public:
		string getName() {return this->name ; }
		string Transport() { return "{air}"; }
	private:
	string name = "Plane";
};

//class to define what is the generic logistic of transportation
class Logistic {
	public:
		virtual ~Logistic(){};
		virtual Vehicle* ChooseTransport() = 0;

		void TransportLoad() {
    // Call the factory method to create a Product object.
    		Vehicle* vehicle = this->ChooseTransport();
    // Now, use the product.
			cout << "Using a " << vehicle->getName() << "." << endl 
			<< "Begining logistics to make transportation by " + vehicle->Transport();
    		delete vehicle;
  }
};

//concrete logistic class to each diferent transportation
class LandLogistic : public Logistic {
	public:
		Vehicle* ChooseTransport() {
    return new Truck();
  }
};

class SeaLogistic : public Logistic {
	public:
		Vehicle* ChooseTransport() {
    return new Ship();
  }
};
class AirLogistic : public Logistic {
	public:
		Vehicle* ChooseTransport() {
    return new Plane();
  }
};

//implementing the function to make any kind of transportation
void MakeTransportation(Logistic& logistic) {
   // ...
	cout << "Choosing the correct logistic to transport the cargo." << endl;
	logistic.TransportLoad();
   // ...
}


int main() {
	cout << "\nFirst, we need to deliver cargo by land\n";
  	Logistic* logistic_1 = new LandLogistic();
  	MakeTransportation(*logistic_1);
  	cout << endl << endl;

	cout << "Then, we need to deliver cargo by sea\n";
  	Logistic* logistic_2 = new SeaLogistic();
  	MakeTransportation(*logistic_2);
  	cout << endl << endl;

	cout << "Finally, we need to deliver cargo by air\n";
  	Logistic* logistic_3 = new AirLogistic();
  	MakeTransportation(*logistic_3);
  	cout << endl << endl;

  delete logistic_1;
  delete logistic_2;
  delete logistic_3;
  return 0;
}