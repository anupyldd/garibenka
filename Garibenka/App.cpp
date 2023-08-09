#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainFrame = new MainFrame("Garibenka");
    mainFrame->SetClientSize(640, 480);
    mainFrame->Center();
    mainFrame->Show(true);
    
    return true;
}
