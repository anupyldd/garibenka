#include "MainFrame.h"
#include "FileLoader.h"
#include <wx/wx.h>



void MainFrame::CreateControls()
{
	wxInitAllImageHandlers();

	
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

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

	chatRichTextCtrl = new wxRichTextCtrl(chatWorkingAreaPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxHSCROLL | wxVSCROLL);
	chatRichTextCtrl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	chatAreaSizer->Add(chatRichTextCtrl, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* answerAreaSizer;
	answerAreaSizer = new wxBoxSizer(wxHORIZONTAL);

	answerAreaSizer->SetMinSize(wxSize(-1, 80));
	answerInputTextCtrl = new wxTextCtrl(chatWorkingAreaPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
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
	chatRichTextCtrl->Bind(wxEVT_SET_FOCUS, &MainFrame::KillChatRichTextFocus, this);
	studyBtn->Bind(wxEVT_BUTTON, &MainFrame::ChooseModule, this);
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

void MainFrame::KillChatRichTextFocus(wxFocusEvent& event)
{
	answerInputTextCtrl->SetFocus();
	
}

void MainFrame::ChooseModule(wxCommandEvent& event)
{
	if (filesListCtrl->GetSelectedItemCount() < 1)
	{
		return;
	}
	
	long item = -1;

	for (;;)
	{
		item = filesListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (item == -1)
			break;

		currentModule = filesListCtrl->GetItemText(item, 1);
		currentFile = filesListCtrl->GetItemText(item, 0);
	}

	genWorkingAreaBook->ChangeSelection(0);

	botBtn->Disable();
	profileBtn->Enable(true);
	filesBtn->Enable(true);
	settingsBtn->Enable(true);
	answerSendBtn->Enable(true);


}

void MainFrame::FillCurrentSymbols(std::vector<Module>& modules)
{
	
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };

	
	
	for (auto mod : modules)
	{
		if (mod.GetModuleName() == currentModule && mod.GetFileName() == currentFile)
		{
			
			
		}
	}
}


void MainFrame::WriteInitialGreeting()
{
	chatRichTextCtrl->WriteText(currentLang[L"Greeting1"] + '\n');
	
	chatRichTextCtrl->SetInsertionPointEnd();

	chatRichTextCtrl->WriteText(currentLang[L"Greeting2"] + '\n');

	chatRichTextCtrl->SetInsertionPointEnd();

	chatRichTextCtrl->BeginBold();
	chatRichTextCtrl->WriteText(currentLang[L"GreetingFiles"]);
	chatRichTextCtrl->EndBold();


	chatRichTextCtrl->EndBold();

	chatRichTextCtrl->WriteText(currentLang[L"Greeting3"]);

	chatRichTextCtrl->SetInsertionPointEnd();

	chatRichTextCtrl->BeginBold();
	chatRichTextCtrl->WriteText(currentLang[L"GreetingStudy"] + '\n');
	chatRichTextCtrl->EndBold();
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


	// temp testing stuff, delete later
	WriteInitialGreeting();

	//FileHandler::UpdateUserSettingsMap("Language", "ru", userSettings);
	//wxString title9 = moduleVector[0].GetModuleName();
	//wxString t7 = userSettings["Language"];
	//filesTitleLabel->SetLabel(t7);
	// end of temp stuff
	
	this->Centre(wxBOTH);
	this->SetMinClientSize(wxSize(640, 480));
}
