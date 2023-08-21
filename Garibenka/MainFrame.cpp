﻿#include "MainFrame.h"
#include "FileLoader.h"
#include <wx/wx.h>



void MainFrame::CreateControls()
{
	wxInitAllImageHandlers();

	
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	//this->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Noto Sans")));

	browseDialog = new BrowseDialog(this, wxID_ANY, currentLang[L"Module Browser"], wxDefaultPosition, wxDefaultSize,
		wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxMAXIMIZE_BOX | wxMINIMIZE_BOX | wxRESIZE_BORDER);

	wxBoxSizer* genSizer;
	genSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxHORIZONTAL);

	leftPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(80, -1), wxTAB_TRAVERSAL);
	leftPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));

	wxBoxSizer* leftPanelSizer;
	leftPanelSizer = new wxBoxSizer(wxVERTICAL);

	leftPanelSizer->SetMinSize(wxSize(80, -1));
	botBtn = new wxBitmapButton(leftPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	botBtn->SetBitmap(wxBitmap(wxT("Icons/BotBtn.png"), wxBITMAP_TYPE_ANY));
	botBtn->SetToolTip(currentLang[L"Helper Bot"]);
	leftPanelSizer->Add(botBtn, 0, wxLEFT | wxRIGHT | wxTOP, 5);

	profileBtn = new wxBitmapButton(leftPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	profileBtn->SetBitmap(wxBitmap(wxT("Icons/ProfileBtn.png"), wxBITMAP_TYPE_ANY));
	profileBtn->SetToolTip(currentLang[L"Profile"]);
	leftPanelSizer->Add(profileBtn, 0, wxLEFT | wxRIGHT | wxTOP, 5);

	filesBtn = new wxBitmapButton(leftPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	filesBtn->SetBitmap(wxBitmap(wxT("Icons/FileBtn.png"), wxBITMAP_TYPE_ANY));
	filesBtn->SetToolTip(currentLang[L"Files"]);
	filesBtn->Disable();
	leftPanelSizer->Add(filesBtn, 0, wxALL, 5);

	fillerLabel = new wxStaticText(leftPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	fillerLabel->Wrap(-1);
	leftPanelSizer->Add(fillerLabel, 1, wxALL | wxEXPAND, 0);

	settingsBtn = new wxBitmapButton(leftPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	settingsBtn->SetBitmap(wxBitmap(wxT("Icons/SettingsBtn.png"), wxBITMAP_TYPE_ANY));
	settingsBtn->SetToolTip(currentLang[L"Settings"]);
	leftPanelSizer->Add(settingsBtn, 0, wxALL, 5);


	leftPanel->SetSizer(leftPanelSizer);
	leftPanel->Layout();
	mainSizer->Add(leftPanel, 0, wxEXPAND | wxALL, 0);

	genWorkingAreaBook = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	genWorkingAreaBook->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	chatWorkingAreaPanel = new wxPanel(genWorkingAreaBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* chatAreaSizer;
	chatAreaSizer = new wxBoxSizer(wxVERTICAL);

	/*chatRichTextCtrl = new wxRichTextCtrl(chatWorkingAreaPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxHSCROLL | wxVSCROLL);
	chatRichTextCtrl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));*/
	
	chatHtmlWindow = new wxHtmlWindow(chatWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_NO_SELECTION | wxHW_SCROLLBAR_AUTO);
	chatHtmlWindow->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	chatAreaSizer->Add(chatHtmlWindow, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);

	//chatAreaSizer->Add(chatRichTextCtrl, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* answerAreaSizer;
	answerAreaSizer = new wxBoxSizer(wxHORIZONTAL);

	answerAreaSizer->SetMinSize(wxSize(-1, 80));
	answerInputTextCtrl = new wxTextCtrl(chatWorkingAreaPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	answerInputTextCtrl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	answerAreaSizer->Add(answerInputTextCtrl, 1, wxALL | wxEXPAND, 5);

	answerSendBtn = new wxBitmapButton(chatWorkingAreaPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	answerSendBtn->SetBitmap(wxBitmap(wxT("Icons/SendBtn.png"), wxBITMAP_TYPE_ANY));
	answerSendBtn->SetToolTip(currentLang[L"Send"]);
	answerSendBtn->Disable();
	
	answerAreaSizer->Add(answerSendBtn, 0, wxBOTTOM | wxRIGHT | wxTOP, 5);


	chatAreaSizer->Add(answerAreaSizer, 0, wxEXPAND, 5);


	chatWorkingAreaPanel->SetSizer(chatAreaSizer);
	chatWorkingAreaPanel->Layout();
	chatAreaSizer->Fit(chatWorkingAreaPanel);
	genWorkingAreaBook->AddPage(chatWorkingAreaPanel, wxT("a page"), false);
	profileWorkingAreaPanel = new wxPanel(genWorkingAreaBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* profileAreaSizer;
	profileAreaSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* profileHeaderSizer;
	profileHeaderSizer = new wxBoxSizer(wxHORIZONTAL);

	userNameLabel = new wxStaticText(profileWorkingAreaPanel, wxID_ANY, userSettings["Username"], wxDefaultPosition, wxDefaultSize, 0);
	userNameLabel->Wrap(-1);
	userNameLabel->SetFont(wxFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	profileHeaderSizer->Add(userNameLabel, 1, wxALL, 5);

	editNameBtn = new wxBitmapButton(profileWorkingAreaPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	editNameBtn->SetBitmap(wxBitmap(wxT("Icons/editBtn.png"), wxBITMAP_TYPE_ANY));
	editNameBtn->SetToolTip(currentLang[L"Change"]);
	profileHeaderSizer->Add(editNameBtn, 0, wxALL, 0);


	profileAreaSizer->Add(profileHeaderSizer, 0, wxEXPAND, 5);

	m_listCtrl2 = new wxListCtrl(profileWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON | wxLC_REPORT | wxLC_SINGLE_SEL);
	m_listCtrl2->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	profileAreaSizer->Add(m_listCtrl2, 1, wxALL | wxEXPAND, 0);


	profileWorkingAreaPanel->SetSizer(profileAreaSizer);
	profileWorkingAreaPanel->Layout();
	profileAreaSizer->Fit(profileWorkingAreaPanel);
	genWorkingAreaBook->AddPage(profileWorkingAreaPanel, wxT("a page"), false);
	filesWorkingAreaPanel = new wxPanel(genWorkingAreaBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* filesAreaSizer;
	filesAreaSizer = new wxBoxSizer(wxVERTICAL);

	filesTitleLabel = new wxStaticText(filesWorkingAreaPanel, wxID_ANY, currentLang[L"Files"], wxDefaultPosition, wxDefaultSize, 0);
	filesTitleLabel->Wrap(-1);
	filesTitleLabel->SetFont(wxFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	filesAreaSizer->Add(filesTitleLabel, 0, wxALL | wxEXPAND, 5);

	loadFileBtn = new wxButton(filesWorkingAreaPanel, wxID_ANY, currentLang[L"Import File"], wxDefaultPosition, wxSize(-1, -1), 0);
	filesAreaSizer->Add(loadFileBtn, 0, wxALL | wxEXPAND, 5);

	filesListCtrl = new wxListCtrl(filesWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON | wxLC_REPORT);
	filesListCtrl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	//filesListCtrl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Noto Sans")));
	filesAreaSizer->Add(filesListCtrl, 1, wxALL | wxEXPAND, 0);

	wxBoxSizer* studyOrBrowseSizer;
	studyOrBrowseSizer = new wxBoxSizer(wxHORIZONTAL);

	studyOrBrowseSizer->SetMinSize(wxSize(-1, 40));
	studyBtn = new wxButton(filesWorkingAreaPanel, wxID_ANY, currentLang[L"Study"], wxDefaultPosition, wxDefaultSize, 0);
	studyOrBrowseSizer->Add(studyBtn, 1, wxALL | wxEXPAND, 5);

	browseBtn = new wxButton(filesWorkingAreaPanel, wxID_ANY, currentLang[L"Browse"], wxDefaultPosition, wxDefaultSize, 0);
	studyOrBrowseSizer->Add(browseBtn, 1, wxALL | wxEXPAND, 5);


	filesAreaSizer->Add(studyOrBrowseSizer, 0, wxEXPAND, 0);


	filesWorkingAreaPanel->SetSizer(filesAreaSizer);
	filesWorkingAreaPanel->Layout();
	filesAreaSizer->Fit(filesWorkingAreaPanel);
	genWorkingAreaBook->AddPage(filesWorkingAreaPanel, wxT("a page"), false);
	settingsWorkingAreaPanel = new wxPanel(genWorkingAreaBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* settingsAreaSizer;
	settingsAreaSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* languageOptionSizer;
	languageOptionSizer = new wxBoxSizer(wxHORIZONTAL);

	languageOptionLabel = new wxStaticText(settingsWorkingAreaPanel, wxID_ANY, currentLang[L"Language"], wxDefaultPosition, wxDefaultSize, 0);
	languageOptionLabel->Wrap(-1);
	languageOptionLabel->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	languageOptionSizer->Add(languageOptionLabel, 2, wxALL | wxEXPAND, 5);

	wxArrayString langChoiceChoices;
	langChoiceChoices.push_back(currentLang[L"EN"]);
	langChoiceChoices.push_back(currentLang[L"RU"]);

	langChoice = new wxChoice(settingsWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, langChoiceChoices, wxCB_SORT);
	langChoice->SetSelection(0);
	langChoice->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	languageOptionSizer->Add(langChoice, 1, wxALL | wxEXPAND, 5);


	settingsAreaSizer->Add(languageOptionSizer, 0, wxEXPAND, 0);

	wxBoxSizer* themeOptionSizer;
	themeOptionSizer = new wxBoxSizer(wxHORIZONTAL);

	themeOptionLabel = new wxStaticText(settingsWorkingAreaPanel, wxID_ANY, currentLang[L"Theme"], wxDefaultPosition, wxDefaultSize, 0);
	themeOptionLabel->Wrap(-1);
	themeOptionLabel->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	themeOptionSizer->Add(themeOptionLabel, 2, wxALL | wxEXPAND, 5);

	wxArrayString themeChoiceChoices;
	themeChoiceChoices.push_back(currentLang[L"Dark"]);
	themeChoiceChoices.push_back(currentLang[L"Light"]);

	themeChoice = new wxChoice(settingsWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, themeChoiceChoices, wxCB_SORT);
	themeChoice->SetSelection(0);
	themeChoice->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	themeOptionSizer->Add(themeChoice, 1, wxALL | wxEXPAND, 5);


	settingsAreaSizer->Add(themeOptionSizer, 0, wxEXPAND, 0);


	settingsWorkingAreaPanel->SetSizer(settingsAreaSizer);
	settingsWorkingAreaPanel->Layout();
	settingsAreaSizer->Fit(settingsWorkingAreaPanel);
	genWorkingAreaBook->AddPage(settingsWorkingAreaPanel, wxT("a page"), false);

	mainSizer->Add(genWorkingAreaBook, 1, wxEXPAND | wxALL, 0);


	genSizer->Add(mainSizer, 1, wxEXPAND, 0);

	genWorkingAreaBook->ChangeSelection(2);

	this->SetSizer(genSizer);
	this->Layout();
}

void MainFrame::BindEventHandlers()
{
	botBtn->Bind(wxEVT_BUTTON, &MainFrame::ChangePageToBot, this);
	profileBtn->Bind(wxEVT_BUTTON, &MainFrame::ChangePageToProfile, this);
	filesBtn->Bind(wxEVT_BUTTON, &MainFrame::ChangePageToFiles, this);
	settingsBtn->Bind(wxEVT_BUTTON, &MainFrame::ChangePageToSettings, this);
	browseBtn->Bind(wxEVT_BUTTON, &MainFrame::ShowBrowseDialog, this);
	loadFileBtn->Bind(wxEVT_BUTTON, &MainFrame::LoadFile, this);
	studyBtn->Bind(wxEVT_BUTTON, &MainFrame::ChooseModule, this);
	answerSendBtn->Bind(wxEVT_BUTTON, &MainFrame::ReadAnswer, this);
	answerInputTextCtrl->Bind(wxEVT_TEXT_ENTER, &MainFrame::ReadAnswerOnEnter, this);
}

void MainFrame::ChangePageToBot(wxCommandEvent& event)
{
	genWorkingAreaBook->ChangeSelection(0);

	botBtn->Disable();
	profileBtn->Enable(true);
	filesBtn->Enable(true);
	settingsBtn->Enable(true);
}

void MainFrame::ChangePageToProfile(wxCommandEvent& event)
{
	genWorkingAreaBook->ChangeSelection(1);

	botBtn->Enable(true);;
	profileBtn->Disable();
	filesBtn->Enable(true);
	settingsBtn->Enable(true);
}

void MainFrame::ChangePageToFiles(wxCommandEvent& event)
{
	genWorkingAreaBook->ChangeSelection(2);

	botBtn->Enable(true);
	profileBtn->Enable(true);
	filesBtn->Disable();
	settingsBtn->Enable(true);
}

void MainFrame::ChangePageToSettings(wxCommandEvent& event)
{
	genWorkingAreaBook->ChangeSelection(3);

	botBtn->Enable(true);;
	profileBtn->Enable(true);
	filesBtn->Enable(true);
	settingsBtn->Disable();
}

void MainFrame::FillModulesList(std::vector<Module> modules)
{
	filesListCtrl->InsertColumn(0, "File", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
	filesListCtrl->InsertColumn(1, "Module", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);

	int size = modules.size();
	for (size_t i = 0; i < size; i++)
	{
		//filesListCtrl->InsertItem(i, modules.at(i).GetFileName());
		filesListCtrl->SetItem(filesListCtrl->InsertItem(i, modules.at(i).GetFileName()), 1, modules.at(i).GetModuleName());
	}

	filesListCtrl->SetColumnWidth(0, wxLIST_AUTOSIZE);
	filesListCtrl->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
}

void MainFrame::ShowBrowseDialog(wxCommandEvent& event)
{
	if (filesListCtrl->GetSelectedItemCount() < 1)
	{
		return;
	}
	
	long item = -1;

	browseDialog->ClearList();
	browseDialog->AddColumns();
	//browseDialog->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Noto Sans")));

	for (;;)
	{
		item = filesListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (item == -1)
			break;

		
		std::vector<std::wstring> symbolsData = FillBrowseSymbolsList(modules, item);
		int size = symbolsData.size();
		for (size_t i = 0; i < size; i+=3)
		{
			browseDialog->AddToList(symbolsData[i], symbolsData[i + 1], symbolsData[i + 2], i);
		}

		browseDialog->AdjustSize();
	}
	
	browseDialog->Show();


}

std::vector<std::wstring> MainFrame::FillBrowseSymbolsList(std::vector<Module> modules, long item)
{
	std::vector<std::wstring> symbolsData;

	for (auto mod : modules)
	{
		if (mod.GetModuleName() == filesListCtrl->GetItemText(item, 1) && mod.GetFileName() == filesListCtrl->GetItemText(item, 0))
		{
			for (auto sym : mod.GetWordList())
			{
				
				symbolsData.push_back(sym.GetSymbol());
				symbolsData.push_back(sym.GetReading());
				symbolsData.push_back(sym.GetMeaning());
			}
			for (auto sym : mod.GetKanjiList())
			{

				symbolsData.push_back(sym.GetSymbol());
				symbolsData.push_back(sym.GetReading());
				symbolsData.push_back(sym.GetMeaning());
			}
		}
	}

	return symbolsData;
}

void MainFrame::LoadFile(wxCommandEvent& event)
{
	wxString pathToFile;
	const wxString pathtoDest = "D:/Projects/Garibenka/Garibenka/Garibenka/Tables/";

	wxFileDialog fileDialog(this, "Select file", "", "", "Excel Files (*.xls;*.xlsx) | *.xls;*.xlsx", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	if (fileDialog.ShowModal() == wxID_OK)
	{
		pathToFile = fileDialog.GetPath();
		
		wxCopyFile(pathToFile, pathtoDest + fileDialog.GetFilename(), false);

		//UpdateModuleList(modules);

	}
}

//void MainFrame::KillChatRichTextFocus(wxFocusEvent& event)
//{
//	answerInputTextCtrl->SetFocus();
//	chatRichTextCtrl->SetInsertionPointEnd();
//}

void MainFrame::TransferModules(std::vector<Module> modules)
{
	localModules = modules;
}

void MainFrame::ChooseModule(wxCommandEvent& event)
{
	if (filesListCtrl->GetSelectedItemCount() < 1)
	{
		return;
	}

	if (userState != CHOOSING_MODULE)
	{
		return;
	}
	
	long item = -1;
	userState = CHOOSING_VOC_OR_KAN;

	for (;;)
	{
		item = filesListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (item == -1)
			break;

		/*currentModule = filesListCtrl->GetItemText(item, 1);
		currentFile = filesListCtrl->GetItemText(item, 0);*/
		for (auto mod : modules)
		{
			if (mod.GetModuleName() == filesListCtrl->GetItemText(item, 1) && 
				mod.GetFileName() == filesListCtrl->GetItemText(item, 0))
			{
				currentModule = mod;
			}
		}
	}

	genWorkingAreaBook->ChangeSelection(0);

	botBtn->Disable();
	profileBtn->Enable(true);
	filesBtn->Enable(true);
	settingsBtn->Enable(true);
	answerSendBtn->Enable(true);

	studyBtn->Disable();

	// chat reply
	htmlContents += "<html><body>";
	htmlContents += currentLang[L"VocabOrKanji1"] + ' ';
	htmlContents += "</body></html>";

	htmlContents += "<html><body><b>";
	htmlContents += currentModule.GetModuleName() + '.';
	htmlContents += "</b></body></html><br>";

	htmlContents += "<html><body>";
	htmlContents += currentLang[L"VocabOrKanji2"] + ' ';
	htmlContents += "</body></html>";

	htmlContents += "<html><body><u>";
	htmlContents += currentLang[L"VocabOrKanjiVoc"];
	htmlContents += "</u></body></html>";

	htmlContents += "<html><body>";
	htmlContents += currentLang[L"VocabOrKanji3"];
	htmlContents += "</body></html>";

	htmlContents += "<html><body><u>";
	htmlContents += currentLang[L"VocabOrKanjiKan"];
	htmlContents += "</u></body></html>";

	chatHtmlWindow->SetPage(htmlContents);
	
}

void MainFrame::FillCurrentSymbols(std::vector<Module>& modules)
{
	
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };

	if (currentVocabOrKanji == VOCAB)
	{
		currentSymbols = currentModule.GetWordList();
	}
	else
	{
		currentSymbols = currentModule.GetKanjiList();
	}
	
}

void MainFrame::ChooseVocabOrKanji()
{
	
}


void MainFrame::WriteInitialGreeting()
{
	htmlContents += "<FONT SIZE = +2>";
	htmlContents += "<html><body>";
	htmlContents += currentLang[L"Greeting1"];
	htmlContents += "</body></html><br>";

	htmlContents += "<html><body>";
	htmlContents += currentLang[L"Greeting2"];
	htmlContents += "</body></html><br>";

	htmlContents += "<html><body><b>";
	htmlContents += currentLang[L"GreetingFiles"];
	htmlContents += "</b></body></html>";

	htmlContents += "<html><body>";
	htmlContents += currentLang[L"Greeting3"];
	htmlContents += "</body></html>";

	htmlContents += "<html><body><b>";
	htmlContents += currentLang[L"GreetingStudy"];
	htmlContents += "</b></body></html><br><br>";

	chatHtmlWindow->SetPage(htmlContents);
}

void MainFrame::ReadAnswer(wxCommandEvent& event)
{

	if (userState == CHOOSING_MODULE)
	{
		return;
	}

	htmlContents += "<br><html><body>";
	htmlContents += "<div ALIGN = \"RIGHT\">";
	htmlContents += answerInputTextCtrl->GetValue();
	htmlContents += "</div></body></html><br><br>";
	chatHtmlWindow->SetPage(htmlContents);

	wxString answ = answerInputTextCtrl->GetValue();

	if (DetectStop(answ))
	{
		ResetStudy();
	}

	switch (userState)
	{
	case CHOOSING_MODULE:
		break;
	case CHOOSING_VOC_OR_KAN:
		ProcessAnswerWhenVocOrKan();
		break;
	case CHOOSING_MODE:
		ProcessAnswerWhenMode();
		break;
	case CHOOSING_ASK_BY:
		ProcessAnswerWhenAskBy();
		break;
	case GETTING_READY:
		ProcessAnswerWhenGettingReady();
		break;
	case STUDYING:
		ProcessAnswerWhenStudy();
		break;
	default:
		break;
	}

	//chatRichTextCtrl->ShowPosition(chatRichTextCtrl->GetLastPosition());
	answerInputTextCtrl->Clear();
	ScrollToBottom();
}

void MainFrame::ReadAnswerOnEnter(wxCommandEvent& event)
{
	if (userState == CHOOSING_MODULE)
	{
		return;
	}

	htmlContents += "<br><html><body>";
	htmlContents += "<div ALIGN = \"RIGHT\">";
	htmlContents += answerInputTextCtrl->GetValue();
	htmlContents += "</div></body></html><br><br>";
	chatHtmlWindow->SetPage(htmlContents);

	wxString answ = answerInputTextCtrl->GetValue();

	if (DetectStop(answ))
	{
		ResetStudy();
	}

	switch (userState)
	{
	case CHOOSING_MODULE:
		break;
	case CHOOSING_VOC_OR_KAN:
		ProcessAnswerWhenVocOrKan();
		break;
	case CHOOSING_MODE:
		ProcessAnswerWhenMode();
		break;
	case CHOOSING_ASK_BY:
		ProcessAnswerWhenAskBy();
		break;
	case GETTING_READY:
		ProcessAnswerWhenGettingReady();
		break;
	case STUDYING:
		ProcessAnswerWhenStudy();
		break;
	default:
		break;
	}

	//chatRichTextCtrl->ShowPosition(chatRichTextCtrl->GetLastPosition());
	answerInputTextCtrl->Clear();
}

bool MainFrame::DetectStop(wxString& answ)
{
	if (CheckAnswerArrays(stop, answ))
	{
		return true;
	}
	return false;
}

void MainFrame::ResetStudy()
{
	userState = CHOOSING_MODULE;
	currentSymbols.clear();
	currentSymbols.shrink_to_fit();

	currentMistakes.clear();
	currentMistakes.shrink_to_fit();

	questionsAsked = 0;
	currentQuestion = 0;

	studyBtn->Enable(true);

	// chat reply
	htmlContents += "<html><body>";
	htmlContents += currentLang[L"ResetStudy1"];
	htmlContents += "</body></html><br>";

	htmlContents += "<html><body>";
	htmlContents += currentLang[L"ResetStudy2"];
	htmlContents += "</body></html>";

	chatHtmlWindow->SetPage(htmlContents);
}

void MainFrame::ResetStudyOnFinish()
{
	userState = CHOOSING_MODULE;
	currentSymbols.clear();
	currentSymbols.shrink_to_fit();

	currentMistakes.clear();
	currentMistakes.shrink_to_fit();

	questionsAsked = 0;
	currentQuestion = 0;

	studyBtn->Enable(true);

	// chat reply
	htmlContents += "<html><body>";
	htmlContents += currentLang[L"NoMistakes1"];
	htmlContents += "</body></html><br>";

	htmlContents += "<html><body>";
	htmlContents += currentLang[L"NoMistakes2"];
	htmlContents += "</body></html>";

	chatHtmlWindow->SetPage(htmlContents);
}

void MainFrame::ProcessAnswerWhenVocOrKan()
{
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };

	wxString answer;
	answer = answerInputTextCtrl->GetValue();
	if (answer.empty())
	{
		return;
	}


	if (CheckAnswerArrays(vocab, answer))
	{
		currentVocabOrKanji = VOCAB;
		currentSymbols = currentModule.GetWordList();
		//gotAnswer = true;
		userState = CHOOSING_MODE;
	}
	else if (CheckAnswerArrays(kanji, answer))
	{
		currentVocabOrKanji = KANJI;
		currentSymbols = currentModule.GetKanjiList();
		//gotAnswer = true;
		userState = CHOOSING_MODE;
	}
	else
	{
		DoNotUnderstandAnswer();
		currentVocabOrKanji = NOT_CHOSEN;
	}

	if (currentVocabOrKanji == VOCAB)
	{
		htmlContents += "<html><body>";
		htmlContents += currentLang[L"StartVocabChooseMode"];
		htmlContents += "</body></html>";

		htmlContents += "<html><body><b>";
		htmlContents += currentLang[L"StartVocabChooseModeVoc"];
		htmlContents += "</b></body></html><br>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"StartVocabChooseMode2"] + ' ';
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"StartVocabChooseModeTerm"];
		htmlContents += "</u></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"StartVocabChooseMode3"];
		htmlContents += "</body></html><br>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"StartVocabChooseModeRead"];
		htmlContents += "</u></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"StartVocabChooseMode4"];
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"StartVocabChooseModeMean"];
		htmlContents += "</u></body></html>";

		chatHtmlWindow->SetPage(htmlContents);
		
	}
	else if (currentVocabOrKanji == KANJI)
	{
		htmlContents += "<html><body>";
		htmlContents += currentLang[L"StartKanjiChooseMode"];
		htmlContents += "</body></html>";

		htmlContents += "<html><body><b>";
		htmlContents += currentLang[L"StartKanjiChooseModeKan"];
		htmlContents += "</b></body></html><br>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"StartKanjiChooseMode2"] + ' ';
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"StartKanjiChooseModeTerm"];
		htmlContents += "</u></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"StartKanjiChooseMode3"];
		htmlContents += "</body></html><br>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"StartKanjiChooseModeRead"];
		htmlContents += "</u></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"StartKanjiChooseMode4"];
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"StartKanjiChooseModeMean"];
		htmlContents += "</u></body></html>";

		chatHtmlWindow->SetPage(htmlContents);
		
	}

	if (currentVocabOrKanji != NOT_CHOSEN)
	{
		std::shuffle(std::begin(currentSymbols), std::end(currentSymbols), rng);
	}
	//gotAnswer = false;
		
}

void MainFrame::ProcessAnswerWhenMode()
{
	wxString answer;
	answer = answerInputTextCtrl->GetValue();
	if (answer.empty())
	{
		return;
	}

	if (CheckAnswerArrays(terms, answer))
	{
		currentMode = TERM;
		userState = CHOOSING_ASK_BY;
	}
	else if (CheckAnswerArrays(readings, answer))
	{
		currentMode = READING;
		userState = CHOOSING_ASK_BY;
	}
	else if (CheckAnswerArrays(meanings, answer))
	{
		currentMode = MEANING;
		userState = CHOOSING_ASK_BY;
	}
	else
	{
		DoNotUnderstandAnswer();
		currentMode = MODE_NOT_CHOSEN;
	}

	// chat reply
	switch (currentMode)
	{
	case MainFrame::TERM:
		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectTermAskBy1"] + ' ';
		htmlContents += "</body></html>";

		htmlContents += "<html><body><b>";
		htmlContents += currentLang[L"SelectTermAskByCatTerm"];
		htmlContents += "</b></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectTermAskBy2"];
		htmlContents += "</body></html><br>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectTermAskBy3"] + ' ';
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"SelectTermAskByRead"];
		htmlContents += "</u></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectTermAskBy4"];
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"SelectTermAskByMean"];
		htmlContents += "</u></body></html>";

		chatHtmlWindow->SetPage(htmlContents);

		break;
	case MainFrame::READING:
		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectReadAskBy1"] + ' ';
		htmlContents += "</body></html>";

		htmlContents += "<html><body><b>";
		htmlContents += currentLang[L"SelectReadAskByCatRead"];
		htmlContents += "</b></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectReadAskBy2"];
		htmlContents += "</body></html><br>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectReadAskBy3"];
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"SelectReadAskByTerm"];
		htmlContents += "</u></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectReadAskBy4"];
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"SelectReadAskByMean"];
		htmlContents += "</u></body></html>";

		chatHtmlWindow->SetPage(htmlContents);

		break;
	case MainFrame::MEANING:
		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectMeanAskBy1"] + ' ';
		htmlContents += "</body></html>";

		htmlContents += "<html><body><b>";
		htmlContents += currentLang[L"SelectMeanAskByCatMean"];
		htmlContents += "</b></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectMeanAskBy2"];
		htmlContents += "</body></html><br>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectMeanAskBy3"];
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"SelectMeanAskByTerm"];
		htmlContents += "</u></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"SelectMeanAskBy4"] + ' ';
		htmlContents += "</body></html>";

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"SelectMeanAskByRead"];
		htmlContents += "</u></body></html>";

		chatHtmlWindow->SetPage(htmlContents);
		break;
	case MainFrame::MODE_NOT_CHOSEN:
		break;
	default:
		break;
	}
	
}

void MainFrame::ProcessAnswerWhenAskBy()
{
	wxString answer;
	answer = answerInputTextCtrl->GetValue();
	if (answer.empty())
	{
		return;
	}

	switch (currentMode)
	{
	case MainFrame::TERM:
		if (CheckAnswerArrays(readings, answer))
		{
			currentAskBy = BY_READING;
			userState = GETTING_READY;
		}
		else if (CheckAnswerArrays(meanings, answer))
		{
			currentAskBy = BY_MEANING;
			userState = GETTING_READY;
		}
		else
		{
			DoNotUnderstandAnswer();
			currentAskBy = ASK_BY_NOT_CHOSEN;
		}
		break;
	case MainFrame::READING:
		if (CheckAnswerArrays(terms, answer))
		{
			currentAskBy = BY_TERM;
			userState = GETTING_READY;
		}
		else if (CheckAnswerArrays(meanings, answer))
		{
			currentAskBy = BY_MEANING;
			userState = GETTING_READY;
		}
		else
		{
			DoNotUnderstandAnswer();
			currentAskBy = ASK_BY_NOT_CHOSEN;
		}
		break;
	case MainFrame::MEANING:
		if (CheckAnswerArrays(terms, answer))
		{
			currentAskBy = BY_TERM;
			userState = GETTING_READY;
		}
		else if (CheckAnswerArrays(readings, answer))
		{
			currentAskBy = BY_READING;
			userState = GETTING_READY;
		}
		else
		{
			DoNotUnderstandAnswer();
			currentAskBy = ASK_BY_NOT_CHOSEN;
		}
		break;
	case MainFrame::MODE_NOT_CHOSEN:
		break;
	default:
		break;
	}

	if (currentAskBy != ASK_BY_NOT_CHOSEN)
	{
		switch (currentMode)
	{
	case MainFrame::TERM:
		htmlContents += "<html><body>";
		htmlContents += currentLang[L"WillAsk1"];
		htmlContents += "</body></html><br>";

		htmlContents += "<html><body><b>";
		htmlContents += currentLang[L"SelectTermAskByCatTerm"] + ' ';
		htmlContents += "</b></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"WillAsk2"];
		htmlContents += "</body></html>";

		if (currentAskBy == BY_READING)
		{
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"SelectTermAskByRead"];
			htmlContents += "</b></body></html><br>";
		}
		else if (currentAskBy == BY_MEANING)
		{
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"SelectTermAskByMean"];
			htmlContents += "</b></body></html><br>";
		}

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"ShouldStart"];
		htmlContents += "</u></body></html>";

		chatHtmlWindow->SetPage(htmlContents);

		break;
	case MainFrame::READING:

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"WillAsk1"];
		htmlContents += "</body></html><br>";

		htmlContents += "<html><body><b>";
		htmlContents += currentLang[L"SelectReadAskByCatRead"] + ' ';
		htmlContents += "</b></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"WillAsk2"];
		htmlContents += "</body></html>";

		if (currentAskBy == BY_TERM)
		{
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"SelectReadAskByTerm"];
			htmlContents += "</b></body></html><br>";
		}
		else if (currentAskBy == BY_MEANING)
		{
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"SelectTermAskByMean"];
			htmlContents += "</b></body></html><br>";
		}

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"ShouldStart"];
		htmlContents += "</u></body></html>";

		chatHtmlWindow->SetPage(htmlContents);

		break;
	case MainFrame::MEANING:

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"WillAsk1"];
		htmlContents += "</body></html><br>";

		htmlContents += "<html><body><b>";
		htmlContents += currentLang[L"SelectMeanAskByCatMean"] + ' ';
		htmlContents += "</b></body></html>";

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"WillAsk2"];
		htmlContents += "</body></html>";

		if (currentAskBy == BY_TERM)
		{
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"SelectReadAskByTerm"];
			htmlContents += "</b></body></html><br>";
		}
		else if (currentAskBy == BY_READING)
		{
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"SelectTermAskByRead"];
			htmlContents += "</b></body></html><br>";
		}

		htmlContents += "<html><body><u>";
		htmlContents += currentLang[L"ShouldStart"];
		htmlContents += "</u></body></html>";

		chatHtmlWindow->SetPage(htmlContents);

		break;
	case MainFrame::MODE_NOT_CHOSEN:
		break;
	default:
		break;
	}
	}
}

void MainFrame::ProcessAnswerWhenGettingReady()
{
	wxString answer;
	answer = answerInputTextCtrl->GetValue();
	if (answer.empty())
	{
		return;
	}
	if (CheckAnswerArrays(start, answer))
	{
		userState = STUDYING;
	

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"Given"];
		htmlContents += "</body></html>";

	

		switch (currentAskBy)
		{
		case MainFrame::BY_TERM:
			htmlContents += "<html><body><b>";
			htmlContents += currentSymbols[currentQuestion].GetSymbol();
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::BY_READING:
			htmlContents += "<html><body><b>";
			htmlContents += currentSymbols[currentQuestion].GetReading();
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::BY_MEANING:
			htmlContents += "<html><body><b>";
			htmlContents += currentSymbols[currentQuestion].GetMeaning();
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::ASK_BY_NOT_CHOSEN:
			break;
		default:
			break;
		}

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"Answer"];
		htmlContents += "</body></html>";

		switch (currentMode)
		{
		case MainFrame::TERM:
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"AnswerTerm"];
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::READING:
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"AnswerRead"];
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::MEANING:
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"AnswerMean"];
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::MODE_NOT_CHOSEN:
			break;
		default:
			break;
		}
	
		chatHtmlWindow->SetPage(htmlContents);
	}
	else
	{
		DoNotUnderstandAnswer();
	}
}

void MainFrame::ProcessAnswerWhenStudy()
{
	AskQuestion();
}

void MainFrame::DoNotUnderstandAnswer()
{
	htmlContents += "<html><body>";
	htmlContents+= currentLang[L"DoNotUnderstand"];
	htmlContents += "</body></html>";
	chatHtmlWindow->SetPage(htmlContents);
}

bool MainFrame::CheckAnswerArrays(std::vector<wxString> variants, wxString answ)
{

	for (auto var : variants)
	{
		if (var == answ)
		{
			return true;
		}
	}
	return false;

}

void MainFrame::AskQuestion()
{
	wxString answer;
	answer = answerInputTextCtrl->GetValue();
	if (answer.empty())
	{
		return;
	}

	

	switch (currentMode)
	{
	case MainFrame::TERM:
		if (currentSymbols[currentQuestion].GetSymbol().find(answer) != std::string::npos)
		{
			htmlContents += "<html><body>";
			htmlContents += currentLang[L"CorrectAnswer"];
			htmlContents += "</body></html><br><br>";
		}
		else
		{
			htmlContents += "<html><body>";
			htmlContents += currentLang[L"WrongAnswer1"];
			htmlContents += "</body></html><br>";

			htmlContents += "<html><body>";
			htmlContents += currentLang[L"WrongAnswer2"] + ' ';
			htmlContents += "</body></html>";

			htmlContents += "<html><body>";
			htmlContents += currentSymbols[currentQuestion].GetSymbol();
			htmlContents += "</body></html><br><br>";

			currentMistakes.push_back(currentSymbols[currentQuestion]);

		}
		break;
	case MainFrame::READING:
		if (currentSymbols[currentQuestion].GetReading().find(answer) != std::string::npos)
		{
			htmlContents += "<html><body>";
			htmlContents += currentLang[L"CorrectAnswer"];
			htmlContents += "</body></html><br><br>";
		}
		else
		{
			htmlContents += "<html><body>";
			htmlContents += currentLang[L"WrongAnswer1"];
			htmlContents += "</body></html><br>";

			htmlContents += "<html><body>";
			htmlContents += currentLang[L"WrongAnswer2"] + ' ';
			htmlContents += "</body></html>";

			htmlContents += "<html><body>";
			htmlContents += currentSymbols[currentQuestion].GetReading();
			htmlContents += "</body></html><br><br>";

			currentMistakes.push_back(currentSymbols[currentQuestion]);

		}
		break;
	case MainFrame::MEANING:
		if (currentSymbols[currentQuestion].GetMeaning().find(answer) != std::string::npos)
		{
			htmlContents += "<html><body>";
			htmlContents += currentLang[L"CorrectAnswer"];
			htmlContents += "</body></html><br><br>";
		}
		else
		{
			htmlContents += "<html><body>";
			htmlContents += currentLang[L"WrongAnswer1"];
			htmlContents += "</body></html><br>";

			htmlContents += "<html><body>";
			htmlContents += currentLang[L"WrongAnswer2"] + ' ';
			htmlContents += "</body></html>";

			htmlContents += "<html><body>";
			htmlContents += currentSymbols[currentQuestion].GetMeaning();
			htmlContents += "</body></html><br><br>";

			currentMistakes.push_back(currentSymbols[currentQuestion]);
		}
		break;
	case MainFrame::MODE_NOT_CHOSEN:
		break;
	default:
		break;
	}
	chatHtmlWindow->SetPage(htmlContents);
	questionsAsked += 1;
	currentQuestion += 1;


	if (questionsAsked < currentSymbols.size())
	{
		htmlContents += "<html><body>";
		htmlContents += currentLang[L"Given"];
		htmlContents += "</body></html>";

		switch (currentAskBy)
		{
		case MainFrame::BY_TERM:
			htmlContents += "<html><body><b>";
			htmlContents += currentSymbols[currentQuestion].GetSymbol();
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::BY_READING:
			htmlContents += "<html><body><b>";
			// here be bug
			htmlContents += currentSymbols[currentQuestion].GetReading();
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::BY_MEANING:
			htmlContents += "<html><body><b>";
			htmlContents += currentSymbols[currentQuestion].GetMeaning();
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::ASK_BY_NOT_CHOSEN:
			break;
		default:
			break;
		}

		htmlContents += "<html><body>";
		htmlContents += currentLang[L"Answer"];
		htmlContents += "</body></html>";

		switch (currentMode)
		{
		case MainFrame::TERM:
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"AnswerTerm"];
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::READING:
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"AnswerRead"];
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::MEANING:
			htmlContents += "<html><body><b>";
			htmlContents += currentLang[L"AnswerMean"];
			htmlContents += "</b></body></html>";
			break;
		case MainFrame::MODE_NOT_CHOSEN:
			break;
		default:
			break;
		}

		chatHtmlWindow->SetPage(htmlContents);

	}
	else
	{
		if (currentMistakes.size() == 0)
		{
			ResetStudyOnFinish();
		}
		else
		{
			currentSymbols = currentMistakes;
			currentMistakes.clear();
			currentMistakes.shrink_to_fit();

			currentQuestion = 0;

			htmlContents += "<html><body>";
			htmlContents += currentLang[L"SomeMistakes1"];
			htmlContents += "</body></html><br>";

			htmlContents += "<html><body>";
			htmlContents += currentLang[L"SomeMistakes2"];
			htmlContents += "</body></html>";

			chatHtmlWindow->SetPage(htmlContents);

			userState = GETTING_READY;
		}
	}
}

void MainFrame::ScrollToBottom()
{
	/*int x;
	int y;
	int xUnit;
	int yUnit;

	chatHtmlWindow->GetVirtualSize(&x, &y);
	chatHtmlWindow->GetScrollPixelsPerUnit(&xUnit, &yUnit);
	chatHtmlWindow->Scroll(0, y / yUnit);*/
}

// FIX THIS SHIT IT DOESNT UPDATE THE LIST FOR SOME REASON
// 
//void MainFrame::UpdateModuleList(std::vector<Module>& modules)
//{
//	filesListCtrl->ClearAll();
//	modules.clear();
//	const char* path[1] = { "D:/Projects/Garibenka/Garibenka/Garibenka/Tables.py" };
//	FileHandler::RunPythonScript(1, path);
//	FileHandler::ReadTablesFile(modules);
//	FillModulesList(modules);
//	
//}


MainFrame::MainFrame(const wxString& title)
	:
	wxFrame(nullptr, wxID_ANY, title)
{
	FileHandler::ReadUserSettingsFile(userSettings);
	FileHandler::ReadLocFile(currentLang, userSettings);

	CreateControls();
	BindEventHandlers();

	const char* path[1] = { "D:/Projects/Garibenka/Garibenka/Garibenka/Tables.py" };
	FileHandler::RunPythonScript(1, path);
	FileHandler::ReadTablesFile(modules);
	FillModulesList(modules);
	TransferModules(modules);

	// temp testing stuff, delete later

	//FileHandler::UpdateUserSettingsMap("Language", "ru", userSettings);
	//wxString title9 = moduleVector[0].GetModuleName();
	//wxString t7 = userSettings["Language"];
	//filesTitleLabel->SetLabel(t7);
	// end of temp stuff
	
	this->Centre(wxBOTH);
	this->SetMinClientSize(wxSize(640, 480));
	
	WriteInitialGreeting();
}


