#include "HelpDialog.h"

HelpDialog::HelpDialog(wxWindow* parent, wxWindowID id, const wxString& title, 
	const wxPoint& pos, const wxSize& size, long style)
	: 
	wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(this->FromDIP(wxSize(720, 480)), wxDefaultSize);

	wxBoxSizer* helpSizer;
	helpSizer = new wxBoxSizer(wxVERTICAL);

	helpText = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxBORDER_NONE | wxHSCROLL | wxVSCROLL | wxWANTS_CHARS);
	helpSizer->Add(helpText, 1, wxEXPAND | wxALL, 0);


	this->SetSizer(helpSizer);
	this->Layout();

	this->Centre(wxBOTH);
}
