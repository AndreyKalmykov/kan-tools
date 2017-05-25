#ifndef KT_MAIN_FORM
#define KT_MAIN_FORM

#include <nana/gui.hpp>

#include "ktPnBar.h"
#include "ktPnMenu.h"
#include "ktPnWrk.h"

using namespace nana;

  class ktMainForm: public form {
    place pl {*this};
    ktPnBar pn_bar {*this};
    ktPnMenu pn_menu {*this};
    ktPnWrk pn_wrk {*this};

  public:
    ktMainForm();
    void menuShow();
  };
#endif
