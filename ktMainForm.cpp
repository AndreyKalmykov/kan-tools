#include <iostream>

#include "ktMainForm.h"

ktMainForm::ktMainForm(){
  size({700,400});

  pl.div("<vertical <bar weight=25 margin=[0,0,2,0]>\
          <horizontal<menu weight=0%>|<wrk>>>");

  pl["bar"] << pn_bar;
  pl["menu"] << pn_menu;
  pl["wrk"] << pn_wrk;
  pl.collocate();
  //~ menuShow();
};
void ktMainForm::menuShow(){
  std::cout << "menuShow" << std::endl;
  std::cout << pl.div() << std::endl;

  //~ pl.div("<vertical <bar weight=25 margin=[0,0,2,0]>\
          //~ <horizontal<menu weight=30%>|<wrk>>>");
  //~ pl.collocate();
  //~ pl.modify("menu","weight=30%");

  //~ pl.field_display("menu",!pl.field_display("menu"));
  //~ std::cout << pl.div() << std::endl;
}
