#include <iostream>
#include "Violet.hpp"

using namespace std;

class Sandbox: public Violet::Application {
    public:
        Sandbox(){
            Violet::Log:getCoreLogger();

        }

        ~Sandbox(){

        }

};

Violet::Application* Violet::CreateApplication(){
    return new Sandbox();
}
