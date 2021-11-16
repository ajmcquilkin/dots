#pragma once

#include <gtkmm.h>

class HelloWorld : public Gtk::Window
{
    public:
        HelloWorld();
        ~HelloWorld() override;

    protected:
        void on_button_clicked();

        Gtk::Button m_button;
};