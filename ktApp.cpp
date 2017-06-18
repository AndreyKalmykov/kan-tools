#include "ktApp.h"

wxIMPLEMENT_APP(ktApp);

bool ktApp::OnInit() {
  appDir= wxPathOnly(argv[0])+"/";
  wxPrintf("appDir=%s\n",appDir.c_str());
  appIcon.LoadFile(appDir+"kTools.png",wxBITMAP_TYPE_PNG);
  ktMainWindow *mw= new ktMainWindow("kan Tools",wxDefaultPosition,wxSize(1024,600));
  //~ mw->Centre(wxBOTH); //wxHORIZONTAL, wxVERTICAL or wxBOTH
  mw->Show(true);
  //~ mw->SetIcon(appIcon);
  return true;
}
