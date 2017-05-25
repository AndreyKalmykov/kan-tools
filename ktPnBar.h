#ifndef KT_PANEL_BAR
#define KT_PANEL_BAR

#include <nana/gui.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/button.hpp>

class ktMainForm;

using namespace nana;

  class ktPnBar: public panel<true> {

    place pl {*this};
    button btn_menu {*this};

    void btn_menu_click();
  public:
    ktPnBar(ktMainForm& wd);

    ktMainForm& mf;
  };

#endif


