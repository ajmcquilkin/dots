#include "generic_selector.hpp"
#include <iostream>

GenericTextInput::GenericTextInput()
    : m_globalBox(Gtk::Orientation::VERTICAL),
    m_submit("Submit")
{
    set_size_request(400, 20);
    set_title("generic text input");

    // gtk_widget_class_set_accessible_role(window, GTK_ACCESSIBLE_ROLE_DIALOG);

    // m_entry.set_max_length(50);
    m_entry.set_activates_default(true);
    m_globalBox.append(m_entry);

    m_submit.signal_clicked().connect(sigc::mem_fun(*this, &GenericTextInput::on_submit));
    m_globalBox.append(m_submit);

    set_default_widget(m_submit);
    set_child(m_globalBox);
}

GenericTextInput::~GenericTextInput()
{

}

void GenericTextInput::on_submit()
{
    std::cout << m_entry.get_text() << std::endl;
    hide();
}
