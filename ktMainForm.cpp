#include "ktMainForm.h"

ktMainForm::ktMainForm(){
  size({700,400});
  pl.div("<horizontal<menu weight=30% gap=5>|<wrk gap=5>>");
  //~ pn1.bgcolor(nana::colors::aqua);
  //~ pn2.bgcolor(nana::colors::sienna);
  pl["menu"] << pn_menu;
  pl["wrk"] << pn_wrk;
  pl.collocate();
}
