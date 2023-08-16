#pragma once
#include "FileLoader.h"
#include "BrowseDialog.h"
#include <wx/wx.h>
#include <wx/simplebook.h>
#include <wx/listctrl.h>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <wx/filefn.h> 

class MainFrame : public wxFrame
{
private:
	void CreateControls();
	void BindEventHandlers();

	void ChangePageToBot(wxCommandEvent& event);
	void ChangePageToProfile(wxCommandEvent& event);
	void ChangePageToFiles(wxCommandEvent& event);
	void ChangePageToSettings(wxCommandEvent& event);

	void FillModulesList(std::vector<Module> modules);

	void ShowBrowseDialog(wxCommandEvent& event);
	std::vector<std::wstring> FillBrowseSymbolsList(std::vector<Module> modules, long item);

	void LoadFile(wxCommandEvent& event);
	void UpdateModuleList(std::vector<Module>& modules);

private:

	bool currentlyStudying = false;

	wxPanel* leftPanel;
	wxBitmapButton* botBtn;
	wxBitmapButton* profileBtn;
	wxBitmapButton* filesBtn;
	wxStaticText* fillerLabel;
	wxBitmapButton* settingsBtn;
	wxSimplebook* genWorkingAreaBook;
	wxPanel* chatWorkingAreaPanel;
	wxListBox* chatListBox;
	wxTextCtrl* answerInputTextCtrl;
	wxBitmapButton* answerSendBtn;
	wxPanel* profileWorkingAreaPanel;
	wxStaticText* userNameLabel;
	wxBitmapButton* editNameBtn;
	wxListCtrl* m_listCtrl2;
	wxPanel* filesWorkingAreaPanel;
	wxStaticText* filesTitleLabel;
	wxButton* loadFileBtn;
	wxListCtrl* filesListCtrl;
	wxButton* studyBtn;
	wxButton* browseBtn;
	wxPanel* settingsWorkingAreaPanel;
	wxStaticText* languageOptionLabel;
	wxChoice* langChoice;
	wxStaticText* themeOptionLabel;
	wxChoice* themeChoice;
	BrowseDialog* browseDialog;

public:
	MainFrame(const wxString& title);
};

