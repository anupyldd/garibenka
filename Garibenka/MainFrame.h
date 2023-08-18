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
#include <wx/richtext/richtextctrl.h>
#include <algorithm>
#include <random>

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
	void UpdateModuleList(std::vector<Module>& modules);	// needs fixing, does not update shit

	void KillChatRichTextFocus(wxFocusEvent& event);

private:
		
	void ChattingLoop();
	void StudyLoop();

	void WriteInitialGreeting();
	void ChooseModule(wxCommandEvent& event);
	void FillCurrentSymbols(std::vector<Module>& modules);
	void ChooseVocabOrKanji();
	void ChooseStudyMode();
	void ChooseAskBy();
	void ReadAnswer();

private:

	bool isStudying = false;
	std::wstring currentModule;		// temp for storing names
	std::wstring currentFile;		// temp for storing names

	std::wstring currentVocabOrKanji;	// kanji or words
	std::wstring currentMode;			// terms, reading, meaning
	std::wstring currentAskBy;			// by terms, reading, meaning
	static std::vector<std::wstring> currentSymbols;	//stores symbols from current active module

	wxPanel* leftPanel;
	wxBitmapButton* botBtn;
	wxBitmapButton* profileBtn;
	wxBitmapButton* filesBtn;
	wxStaticText* fillerLabel;
	wxBitmapButton* settingsBtn;
	wxSimplebook* genWorkingAreaBook;
	wxPanel* chatWorkingAreaPanel;
	wxRichTextCtrl* chatRichTextCtrl;
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

