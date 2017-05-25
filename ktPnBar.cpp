//~ #include <iostream>

#include "ktPnBar.h"

#include "ktMainForm.h"

ktPnBar::ktPnBar(ktMainForm& wd):panel(wd), mf{wd}{

  bgcolor(nana::colors::green);
  pl.div("<btn_menu weight=25><>");
  pl["btn_menu"] << btn_menu;
  pl.collocate();

  btn_menu.events().click([this]{ btn_menu_click(); });
}

void ktPnBar::btn_menu_click(){
  mf.menuShow();
}
