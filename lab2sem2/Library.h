
#include <iostream>
#include <memory>
using namespace std;


class Strategy {
public:
    virtual void executeAlgorithm() const = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void executeAlgorithm() const override {
        std::cout << "Executing algorithm A." << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void executeAlgorithm() const override {
        std::cout << "Executing algorithm B." << std::endl;
    }
};

class Context {
private:
    std::unique_ptr<Strategy> strategy;
public:
    Context(std::unique_ptr<Strategy> strategy) : strategy(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<Strategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    void executeStrategy() const {
        strategy->executeAlgorithm();
    }
};


class AbstractProduct {
public:
    virtual void performTask() const = 0;
};

class ConcreteProductA : public AbstractProduct {
public:
    void performTask() const override {
        std::cout << "Performing task A." << std::endl;
    }
};

class ConcreteProductB : public AbstractProduct {
public:
    void performTask() const override {
        std::cout << "Performing task B." << std::endl;
    }
};

class AbstractFactory {
public:
    virtual std::unique_ptr<AbstractProduct> createProduct() const = 0;
};

class ConcreteFactoryA : public AbstractFactory {
public:
    std::unique_ptr<AbstractProduct> createProduct() const override {
        return std::make_unique<ConcreteProductA>();
    }
};

class ConcreteFactoryB : public AbstractFactory {
public:
    std::unique_ptr<AbstractProduct> createProduct() const override {
        return std::make_unique<ConcreteProductB>();
    }
};


class State {
public:
    virtual void handleRequest() = 0;
};

class ConcreteStateA : public State {
public:
    void handleRequest() override {
        std::cout << "Handling request A." << std::endl;
    }
};

class ConcreteStateB : public State {
public:
    void handleRequest() override {
        std::cout << "Handling request B." << std::endl;
    }
};

class ContextState {
private:
    std::unique_ptr<State> state;
public:
    ContextState(std::unique_ptr<State> state) : state(std::move(state)) {}

    void setState(std::unique_ptr<State> newState) {
        state = std::move(newState);
    }

    void request() const {
        state->handleRequest();
    }
};

class Singleton {
private:
    static Singleton* instance;
    Singleton() {}

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        if (!instance)
            instance = new Singleton();
        return instance;
    }

    void performTask() const {
        std::cout << "Singleton performing task." << std::endl;
    }
};

Singleton* Singleton::instance = nullptr;


class Adaptee {
public:
    void specificRequest() {
        std::cout << "Specific request." << std::endl;
    }
};

class Target {
public:
    virtual void request() = 0;
};

class Adapter : public Target {
private:
    Adaptee* adaptee;

public:
    Adapter(Adaptee* a) : adaptee(a) {}

    void request() override {
        adaptee->specificRequest();
    }
};

class Component {
public:
    virtual void operation() = 0;
};

class ConcreteComponent : public Component {
public:
    void operation() override {
        std::cout << "Concrete component operation." << std::endl;
    }
};

class Decorator : public Component {
protected:
    Component* component;

public:
    Decorator(Component* c) : component(c) {}

    void operation() override {
        component->operation();
    }
};

class ConcreteDecorator : public Decorator {
public:
    ConcreteDecorator(Component* c) : Decorator(c) {}

    void operation() override {
        std::cout << "Concrete decorator operation before." << std::endl;
        Decorator::operation();
        std::cout << "Concrete decorator operation after." << std::endl;
    }
};


#include <set>

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    std::set<Observer*> observers;

public:
    void attach(Observer* o) {
        observers.insert(o);
    }

    void detach(Observer* o) {
        observers.erase(o);
    }

    void notify() {
        for (Observer* o : observers) {
            o->update();
        }
    }
};

class ConcreteObserver : public Observer {
public:
    void update() override {
        std::cout << "Concrete observer updated." << std::endl;
    }
};


int main() {

    Context context(std::make_unique<ConcreteStrategyA>());
    context.executeStrategy();
    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.executeStrategy();


    ConcreteFactoryA factoryA;
    std::unique_ptr<AbstractProduct> productA = factoryA.createProduct();
    productA->performTask();

    ConcreteFactoryB factoryB;
    std::unique_ptr<AbstractProduct> productB = factoryB.createProduct();
    productB->performTask();


    ContextState contextState(std::make_unique<ConcreteStateA>());
    contextState.request();
    contextState.setState(std::make_unique<ConcreteStateB>());
    contextState.request();


    Singleton::getInstance()->performTask();


    Adaptee* adaptee = new Adaptee();
    Target* adapter = new Adapter(adaptee);
    adapter->request();
    delete adapter;
    delete adaptee;


    ConcreteComponent* component = new ConcreteComponent();
    Decorator* decorator = new ConcreteDecorator(component);
    decorator->operation();
    delete decorator;
    delete component;

  
    Subject subject;
    ConcreteObserver observer;
    subject.attach(&observer);
    subject.notify();
    subject.detach(&observer);

    return 0;
}
