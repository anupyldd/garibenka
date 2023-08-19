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
	enum State
	{
		CHOOSING_MODULE,		// when no module has yet been selected
		CHOOSING_VOC_OR_KAN,	// when module has just been selected
		CHOOSING_MODE,			// when user has chosen voc or kan
		CHOOSING_ASK_BY,		// when choosing, what to ask by
		STUDYING				// when all is set up
	};

	enum VocOrKan
	{
		VOCAB,
		KANJI,
		NOT_CHOSEN
	};

	// for checking answers
	wxString vocab[4] = { "vocab", "vocabulary", "лексика", "лексику" };
	wxString kanji[2] = { "kanji", "кандзи"};
	wxString terms[4] = { "term", "terms", "термины", "терминах"};
	wxString readings[7] = { "reading", "readings", "чтения", "чтениях", "чтение", "чтениям", "по чтениям"};
	wxString meanings[7] = { "meaning", "meanings", "значения", "значениях", "значение", "значениям", "по значениям"};

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

	void TransferModules(std::vector<Module> modules);

private:
		
	void ChattingLoop();
	void StudyLoop();

	void WriteInitialGreeting();
	void ChooseModule(wxCommandEvent& event);
	void FillCurrentSymbols(std::vector<Module>& modules);
	void ChooseVocabOrKanji();
	void ChooseStudyMode();
	void ChooseAskBy();

	void ReadAnswer(wxCommandEvent& event);
	void ProcessAnswerWhenVocOrKan();
	void ProcessAnswerWhenMode();
	void ProcessAnswerWhenAskBy();
	void ProcessAnswerWhenStudy();
	void DoNotUnderstandAnswer();

	bool CheckAnswerArrays(wxString variants[], wxString answ);

private:

	bool gotAnswer = false;

	std::vector<Module> localModules;	// bandaid because i fucked up and dont want to remake the whole thing

	State userState = CHOOSING_MODULE;
	//std::wstring currentModule;		// temp for storing names
	//std::wstring currentFile;		// temp for storing names

	Module currentModule;
	VocOrKan currentVocabOrKanji;	// kanji or words
	std::wstring currentMode;			// terms, reading, meaning
	std::wstring currentAskBy;			// by terms, reading, meaning
	std::vector<Symbol> currentSymbols;	//stores symbols from current active module

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

