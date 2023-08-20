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
#include <wx/html/htmlwin.h>
#include <wx/wxhtml.h.>
#include <iterator> 



class MainFrame : public wxFrame
{
private:
	enum State
	{
		CHOOSING_MODULE,		// when no module has yet been selected
		CHOOSING_VOC_OR_KAN,	// when module has just been selected
		CHOOSING_MODE,			// when user has chosen voc or kan
		CHOOSING_ASK_BY,		// when choosing, what to ask by
		GETTING_READY,			// when asked if should start
		STUDYING				// when all is set up
	};

	enum VocOrKan
	{
		VOCAB,
		KANJI,
		NOT_CHOSEN
	};

	enum Mode
	{
		TERM,
		READING,
		MEANING,
		MODE_NOT_CHOSEN
	};

	enum AskBy
	{
		BY_TERM,
		BY_READING,
		BY_MEANING,
		ASK_BY_NOT_CHOSEN
	};

	// for checking answers
	std::vector<wxString> vocab = { "vocab", "vocabulary", "лексика", "лексику", "words", "слова" };
	std::vector<wxString> kanji = { "kanji", "kan", "кандзи", "иероглифы" };
	std::vector<wxString> terms = { "term", "terms", "термины", "терминах", "термин", "терминам", "по терминам" };
	std::vector<wxString>  readings = { "reading", "readings", "чтения", "чтениях", "чтение", "чтениям", "по чтениям" };
	std::vector<wxString>  meanings = { "meaning", "meanings", "значения", "значениях", "значение", "значениям", "по значениям" };
	std::vector<wxString> start = { "start","begin","начать", "начнем", "старт" };
	std::vector<wxString> stop = { "!stop", "!стоп" };

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

	//void KillChatRichTextFocus(wxFocusEvent& event);

	void TransferModules(std::vector<Module> modules);

private:
		
	//void ChattingLoop();
	//void StudyLoop();

	void WriteInitialGreeting();
	void ChooseModule(wxCommandEvent& event);
	void FillCurrentSymbols(std::vector<Module>& modules);
	void ChooseVocabOrKanji();
	//void ChooseStudyMode();
	//void ChooseAskBy();

	void ReadAnswer(wxCommandEvent& event);
	void ReadAnswerOnEnter(wxCommandEvent& event);

	void ProcessAnswerWhenVocOrKan();
	void ProcessAnswerWhenMode();
	void ProcessAnswerWhenAskBy();
	void ProcessAnswerWhenGettingReady();
	void ProcessAnswerWhenStudy();
	void DoNotUnderstandAnswer();

	bool DetectStop(wxString& answ);
	void ResetStudy();

	bool CheckAnswerArrays(std::vector<wxString> variants, wxString answ);

	void AskQuestion();

private:

	wxString htmlContents = "";

	bool gotAnswer = false;

	std::vector<Module> localModules;	// bandaid because i fucked up and dont want to remake the whole thing

	State userState = CHOOSING_MODULE;
	//std::wstring currentModule;		// temp for storing names
	//std::wstring currentFile;		// temp for storing names

	Module currentModule;
	VocOrKan currentVocabOrKanji;			// kanji or words
	Mode currentMode = MODE_NOT_CHOSEN;		// terms, reading, meaning
	AskBy currentAskBy = ASK_BY_NOT_CHOSEN;	// by terms, reading, meaning

	std::vector<Symbol> currentSymbols;		//stores symbols from current active module
	std::vector<Symbol> currentMistakes;	//stores symbols that were answered incorrectly in current session

	int questionsAsked = 0;
	int currentQuestion = 0;

	wxPanel* leftPanel;
	wxBitmapButton* botBtn;
	wxBitmapButton* profileBtn;
	wxBitmapButton* filesBtn;
	wxStaticText* fillerLabel;
	wxBitmapButton* settingsBtn;
	wxSimplebook* genWorkingAreaBook;
	wxPanel* chatWorkingAreaPanel;
	wxRichTextCtrl* chatRichTextCtrl;
	wxHtmlWindow* chatHtmlWindow;
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

