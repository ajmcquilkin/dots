#pragma once

#include <gtkmm.h>

class GenericTextInput : public Gtk::Dialog
{
    public:
        GenericTextInput();
        ~GenericTextInput();

    protected:
        void on_submit();

        // Child Wigets        
        Gtk::Box m_globalBox;
        Gtk::Entry m_entry;
        Gtk::Button m_submit;
};