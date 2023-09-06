#pragma once
#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>

class HelpDialog : public wxDialog
{
private:


public:
	wxRichTextCtrl* helpText;

	HelpDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(640, 480), long style = wxDEFAULT_DIALOG_STYLE);

};

