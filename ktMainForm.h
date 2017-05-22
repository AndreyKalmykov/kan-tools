#ifndef KT_MAIN_FORM
#define KT_MAIN_FORM

#include <nana/gui.hpp>
//~ #include <nana/gui/widgets/panel.hpp>
//~ #include <nana/gui/widgets/button.hpp>

#include "ktPnMenu.h"
#include "ktPnWrk.h"

using namespace nana;

  class ktMainForm: public form {
    place pl {*this};
    ktPnMenu pn_menu {*this};
    ktPnWrk pn_wrk {*this};

  public:
    ktMainForm();
  };
#endif
