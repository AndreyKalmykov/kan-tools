#ifndef ktApp_h
#define ktApp_h

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "ktMainWindow.h"

class ktApp: public wxApp {
public:
  ktMainWindow *mw;
  wxString appDir;
  wxIcon appIcon;

  virtual bool OnInit();
};

#endif
