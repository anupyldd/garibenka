#include "MainFrame.h"
#include "FileLoader.h"
#include <wx/wx.h>


void MainFrame::CreateControls()
{
	wxInitAllImageHandlers();

	
	GenBoxSizer = new wxBoxSizer(wxVERTICAL);
	SetSizerAndFit(GenBoxSizer);

	GenPanel = new wxPanel(this, 3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	GenPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));

	
	SizerScreenSplit = new wxBoxSizer(wxHORIZONTAL);

	
	LeftPanelSizer = new wxBoxSizer(wxVERTICAL);

	BotBtn = new wxBitmapButton(GenPanel, 4, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	BotBtn->SetBitmap(wxBitmap(wxT("Icons/BotBtn.xpm"), wxBITMAP_TYPE_ANY));
	LeftPanelSizer->Add(BotBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);

	ProfileBtn = new wxBitmapButton(GenPanel, 5, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	ProfileBtn->SetBitmap(wxBitmap(wxT("Icons/ProfileBtn.xpm"), wxBITMAP_TYPE_ANY));
	LeftPanelSizer->Add(ProfileBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);

	FileBtn = new wxBitmapButton(GenPanel, 6, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	FileBtn->SetBitmap(wxBitmap(wxT("Icons/FileBtn.xpm"), wxBITMAP_TYPE_ANY));
	LeftPanelSizer->Add(FileBtn, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);

	LeftPanelFillerPanel = new wxPanel(GenPanel, wxID_ANY, wxDefaultPosition, wxSize(80, -1), wxTAB_TRAVERSAL);
	LeftPanelFillerPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));

	LeftPanelSizer->Add(LeftPanelFillerPanel, 1, wxEXPAND | wxTOP, 5);

	SettingsBtn = new wxBitmapButton(GenPanel, 7, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	SettingsBtn->SetBitmap(wxBitmap(wxT("Icons/SettingsBtn.xpm"), wxBITMAP_TYPE_ANY));
	LeftPanelSizer->Add(SettingsBtn, 0, wxALL, 5);


	SizerScreenSplit->Add(LeftPanelSizer, 0, wxEXPAND | wxTOP, 5);

	
	MainWorkingAreaSizer = new wxBoxSizer(wxVERTICAL);

	
	BotScreenSizer = new wxBoxSizer(wxVERTICAL);

	
	ChatAreaSizer = new wxBoxSizer(wxHORIZONTAL);

	ChatListBox = new wxListBox(GenPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	ChatAreaSizer->Add(ChatListBox, 1, wxEXPAND | wxRIGHT | wxTOP, 5);


	BotScreenSizer->Add(ChatAreaSizer, 1, wxEXPAND, 0);

	
	AnswerAreaSizer = new wxBoxSizer(wxHORIZONTAL);

	AnswerAreaSizer->SetMinSize(wxSize(-1, 80));
	AnswerFieldTextCtrl = new wxTextCtrl(GenPanel, 11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	AnswerFieldTextCtrl->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	AnswerAreaSizer->Add(AnswerFieldTextCtrl, 1, wxBOTTOM | wxEXPAND | wxTOP, 5);

	AnswerBtn = new wxBitmapButton(GenPanel, 10, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	AnswerBtn->SetBitmap(wxBitmap(wxT("Icons/SendBtn.xpm"), wxBITMAP_TYPE_ANY));
	AnswerAreaSizer->Add(AnswerBtn, 0, wxALL, 5);


	BotScreenSizer->Add(AnswerAreaSizer, 0, wxEXPAND, 0);


	MainWorkingAreaSizer->Add(BotScreenSizer, 1, wxEXPAND, 0);


	SizerScreenSplit->Add(MainWorkingAreaSizer, 1, wxEXPAND, 0);


	GenPanel->SetSizer(SizerScreenSplit);
	GenPanel->Layout();
	SizerScreenSplit->Fit(GenPanel);
	GenBoxSizer->Add(GenPanel, 1, wxEXPAND | wxALL, 0);

	this->SetSizer(GenBoxSizer);
	this->Layout();
}

void MainFrame::BindEventHandlers()
{
	BotBtn->Bind(wxEVT_BUTTON,&MainFrame::TmpHdeSizer, this);
	ProfileBtn->Bind(wxEVT_BUTTON, &MainFrame::TmpHdeSizer, this);
}

void MainFrame::TmpHdeSizer(wxCommandEvent& event)
{
	MainWorkingAreaSizer->Show(BotScreenSizer, false);

	//MainWorkingAreaSizer->Hide(BotScreenSizer, true);
	//this->Layout();
}

// TODO FIX THIS SHIT IT DOES NOT SHOW SIZER BACK
void MainFrame::TmpShowSizer(wxCommandEvent& event)
{
	//this->Layout();
	MainWorkingAreaSizer->Show(BotScreenSizer, true);
}

MainFrame::MainFrame(const wxString& title)
	:
	wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventHandlers();
	FileLoader::RunPythonScript();


	this->Centre(wxBOTH);
	this->SetMinClientSize(wxSize(640, 480));
}
