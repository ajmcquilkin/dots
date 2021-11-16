#include <gtkmm.h>
#include <iostream>

namespace 
{
    Gtk::Dialog* pDialog = nullptr;
    Glib::RefPtr<Gtk::Application> app;

    void on_button_clicked()
    {
        if (pDialog) pDialog->hide();
    }

    void on_app_activate()
    {
        auto refBuilder = Gtk::Builder::create();

        try
        {
            refBuilder->add_from_file("example.xml");
        }
        catch(const Glib::FileError& ex)
        {
            std::cerr << "FileError: " << ex.what() << std::endl;
            return;
        }
        catch(const Glib::MarkupError& ex)
        {
            std::cerr << "MarkupError: " << ex.what() << std::endl;
            return;
        }
        catch(const Gtk::BuilderError& ex)
        {
            std::cerr << "BuilderError: " << ex.what() << std::endl;
            return;
        }

        pDialog = refBuilder->get_widget<Gtk::Dialog>("DialogBasic");

        if (!pDialog)
        {
            std::cerr << "Could not get dialog" << std::endl;
            return;
        }

        auto pButton = refBuilder->get_widget<Gtk::Button>("quit_button");

        if (pButton)
        {
            pButton->signal_clicked().connect([] () { on_button_clicked(); });
        }

        pDialog->signal_hide().connect([] () { delete pDialog; });

        app->add_window(*pDialog);
        pDialog->show();
    }
}

int main(int argc, char *argv[])
{
    app = Gtk::Application::create("org.gtkmm.example");
    app->signal_activate().connect([] () { on_app_activate(); });
    return app->run(argc, argv);
}
