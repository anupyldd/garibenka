#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
private:
	void CreateControls();
	void BindEventHandlers();

	void TmpHdeSizer(wxCommandEvent& event);
	void TmpShowSizer(wxCommandEvent& event);

	wxBoxSizer* GenBoxSizer;
	wxBoxSizer* SizerScreenSplit;
	wxBoxSizer* LeftPanelSizer;
	wxBoxSizer* MainWorkingAreaSizer;
	wxBoxSizer* BotScreenSizer;
	wxBoxSizer* ChatAreaSizer;
	wxBoxSizer* AnswerAreaSizer;

	wxPanel* GenPanel;
	wxBitmapButton* BotBtn;
	wxBitmapButton* ProfileBtn;
	wxBitmapButton* FileBtn;
	wxPanel* LeftPanelFillerPanel;
	wxBitmapButton* SettingsBtn;
	wxListBox* ChatListBox;
	wxTextCtrl* AnswerFieldTextCtrl;
	wxBitmapButton* AnswerBtn;

public:
	MainFrame(const wxString& title);
};

