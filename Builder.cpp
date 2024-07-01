#include <vector>
#include <string>
#include <iostream>

using namespace std;


class House{
    public:
    vector<string> parts;
    void ListParts()const{
        cout << "House features: ";
        for (size_t i=0;i<parts.size();i++){
            if(parts[i]== parts.back()){
                cout << parts[i];
            }else{
                cout << parts[i] << ", ";
            }
        }
        cout << "\n\n"; 
    }
};


class Builder{
    public:
    virtual ~Builder(){}
    virtual void ProduceHouse() =0;
    virtual void ProduceGarage() =0;
    virtual void ProduceGarden() =0;
};

class ConcreteBuilder : public Builder{
    private:
        House* house;
    public:
        ConcreteBuilder(){
            this->Reset();
        }
        ~ConcreteBuilder(){
            delete house;
        }
        void Reset(){
            this->house= new House();
        }
        //All production steps work with the same product instance.
        void ProduceHouse() {
            this->house->parts.push_back("House");
        }

        void ProduceGarage() {
            this->house->parts.push_back("Garage");
        }

        void ProduceGarden() {
            this->house->parts.push_back("Garden");
        }
        House* GetHouse() {
            House* result= this->house;
            this->Reset();
            return result;
        }
};


class Director{

    private:
    Builder* builder;

    public:

    void set_builder(Builder* builder_){
        this->builder=builder_;
    }

    void BuildMinimalViableProduct(){
        this->builder->ProduceHouse();
    }
    
    void BuildFullFeaturedProduct(){
        this->builder->ProduceHouse();
        this->builder->ProduceGarage();
        this->builder->ProduceGarden();
    }
};

void ClientCode(Director& director)
{
    ConcreteBuilder* builder = new ConcreteBuilder();
    director.set_builder(builder);
    cout << "\nStandard basic House:\n"; 
    director.BuildMinimalViableProduct();
    
    House* h= builder->GetHouse();
    h->ListParts();
    delete h;

    cout << "Standard full featured House:\n"; 
    director.BuildFullFeaturedProduct();

    h= builder->GetHouse();
    h->ListParts();
    delete h;

    // Remember, the Builder pattern can be used without a Director class.
    std::cout << "Custom House:\n";
    builder->ProduceHouse();
    builder->ProduceGarage();
    h=builder->GetHouse();
    h->ListParts();
    delete h;

    delete builder;
}

int main(){
    Director* director= new Director();
    ClientCode(*director);
    delete director;
    return 0;    
}