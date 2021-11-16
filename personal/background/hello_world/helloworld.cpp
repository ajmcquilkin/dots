#include "helloworld.hpp"
#include <iostream>

HelloWorld::HelloWorld()
: m_button("Hello World")
{
    m_button.set_margin(10);
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &HelloWorld::on_button_clicked));
    set_child(m_button);
}

HelloWorld::~HelloWorld()
{

}

void HelloWorld::on_button_clicked()
{
    std::cout << "Hello, World!" << std::endl;
}
