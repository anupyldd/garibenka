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

	leftPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(-1, -1)), wxTAB_TRAVERSAL);
	leftPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));

	wxBoxSizer* leftPanelSizer;
	leftPanelSizer = new wxBoxSizer(wxVERTICAL);

	leftPanelSizer->SetMinSize(this->FromDIP(wxSize(-1, -1)));
	botBtn = new wxBitmapButton(leftPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxBORDER_NONE);

	botBtn->SetBitmap(wxBitmap(wxT("Icons/BotBtn.png"), wxBITMAP_TYPE_ANY));
	botBtn->SetToolTip(currentLang[L"Helper Bot"]);
	leftPanelSizer->Add(botBtn, 0, wxLEFT | wxRIGHT | wxTOP, this->FromDIP(5));

	/*profileBtn = new wxBitmapButton(leftPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | 0);

	profileBtn->SetBitmap(wxBitmap(wxT("Icons/ProfileBtn.png"), wxBITMAP_TYPE_ANY));
	profileBtn->SetToolTip(currentLang[L"Profile"]);
	leftPanelSizer->Add(profileBtn, 0, wxLEFT | wxRIGHT | wxTOP, 5);*/

	filesBtn = new wxBitmapButton(leftPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxBORDER_NONE);

	filesBtn->SetBitmap(wxBitmap(wxT("Icons/FileBtn.png"), wxBITMAP_TYPE_ANY));
	filesBtn->SetToolTip(currentLang[L"Files"]);
	filesBtn->Disable();
	leftPanelSizer->Add(filesBtn, 0, wxALL, this->FromDIP(5));

	fillerLabel = new wxStaticText(leftPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	fillerLabel->Wrap(-1);
	leftPanelSizer->Add(fillerLabel, 1, wxALL | wxEXPAND, 0);

	settingsBtn = new wxBitmapButton(leftPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxBORDER_NONE);

	settingsBtn->SetBitmap(wxBitmap(wxT("Icons/SettingsBtn.png"), wxBITMAP_TYPE_ANY));
	settingsBtn->SetToolTip(currentLang[L"Settings"]);
	leftPanelSizer->Add(settingsBtn, 0, wxALL, this->FromDIP(5));


	leftPanel->SetSizer(leftPanelSizer);
	leftPanel->Layout();
	mainSizer->Add(leftPanel, 0, wxEXPAND | wxALL, this->FromDIP(0));

	genWorkingAreaBook = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	genWorkingAreaBook->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	chatWorkingAreaPanel = new wxPanel(genWorkingAreaBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* chatAreaSizer;
	chatAreaSizer = new wxBoxSizer(wxVERTICAL);

	chatHtmlWindow = new wxHtmlWindow(chatWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_NO_SELECTION | wxHW_SCROLLBAR_AUTO);
	chatHtmlWindow->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	chatAreaSizer->Add(chatHtmlWindow, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, this->FromDIP(5));


	wxBoxSizer* answerAreaSizer;
	answerAreaSizer = new wxBoxSizer(wxHORIZONTAL);

	answerAreaSizer->SetMinSize(this->FromDIP(wxSize(-1, 40)));
	answerInputTextCtrl = new wxTextCtrl(chatWorkingAreaPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxBORDER_NONE);
	answerInputTextCtrl->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	answerAreaSizer->Add(answerInputTextCtrl, 1, wxALL | wxEXPAND, this->FromDIP(5));

	answerSendBtn = new wxBitmapButton(chatWorkingAreaPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxBORDER_NONE);

	answerSendBtn->SetBitmap(wxBitmap(wxT("Icons/SendBtn.png"), wxBITMAP_TYPE_ANY));
	answerSendBtn->SetToolTip(currentLang[L"Send"]);
	answerSendBtn->Disable();
	
	answerAreaSizer->Add(answerSendBtn, 0, wxBOTTOM | wxRIGHT | wxTOP, this->FromDIP(5));


	chatAreaSizer->Add(answerAreaSizer, 0, wxEXPAND, this->FromDIP(5));


	chatWorkingAreaPanel->SetSizer(chatAreaSizer);
	chatWorkingAreaPanel->Layout();
	chatAreaSizer->Fit(chatWorkingAreaPanel);
	genWorkingAreaBook->AddPage(chatWorkingAreaPanel, wxT("a page"), false);
	/*profileWorkingAreaPanel = new wxPanel(genWorkingAreaBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
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

	statsListCtrl = new wxListCtrl(profileWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON | wxLC_REPORT | wxLC_SINGLE_SEL);
	statsListCtrl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	profileAreaSizer->Add(statsListCtrl, 1, wxALL | wxEXPAND, 0);


	profileWorkingAreaPanel->SetSizer(profileAreaSizer);
	profileWorkingAreaPanel->Layout();
	profileAreaSizer->Fit(profileWorkingAreaPanel);
	genWorkingAreaBook->AddPage(profileWorkingAreaPanel, wxT("a page"), false);*/
	filesWorkingAreaPanel = new wxPanel(genWorkingAreaBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* filesAreaSizer;
	filesAreaSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* HeaderSizer;
	HeaderSizer = new wxBoxSizer(wxHORIZONTAL);

	filesTitleLabel = new wxStaticText(filesWorkingAreaPanel, wxID_ANY, currentLang[L"Files"], wxDefaultPosition, wxDefaultSize, 0);
	filesTitleLabel->Wrap(-1);
	filesTitleLabel->SetFont(wxFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	HeaderSizer->Add(filesTitleLabel, 1, wxALL, this->FromDIP(5));

	wxBoxSizer* loadDelSizer;
	loadDelSizer = new wxBoxSizer(wxVERTICAL);

	loadFileBtn = new wxBitmapButton(filesWorkingAreaPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxBORDER_NONE);
	loadDelSizer->Add(loadFileBtn, 0, wxALL, this->FromDIP(5));

	delFileButton = new wxBitmapButton(filesWorkingAreaPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxBORDER_NONE);
	loadDelSizer->Add(delFileButton, 0, wxALL, this->FromDIP(5));


	HeaderSizer->Add(loadDelSizer, 0, wxEXPAND, this->FromDIP(0));

	wxBoxSizer* studyOrBrowseSizer;
	studyOrBrowseSizer = new wxBoxSizer(wxVERTICAL);

	studyOrBrowseSizer->SetMinSize(this->FromDIP(wxSize(-1, 40)));
	studyBtn = new wxBitmapButton(filesWorkingAreaPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxBORDER_NONE);
	studyOrBrowseSizer->Add(studyBtn, 0, wxALL, this->FromDIP(5));

	browseBtn = new wxBitmapButton(filesWorkingAreaPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxBORDER_NONE);
	studyOrBrowseSizer->Add(browseBtn, 0, wxALL, this->FromDIP(5));


	HeaderSizer->Add(studyOrBrowseSizer, 0, wxEXPAND, this->FromDIP(0));


	filesAreaSizer->Add(HeaderSizer, 0, wxEXPAND, this->FromDIP(0));

	filesListCtrl = new wxListCtrl(filesWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_NO_HEADER | wxLC_ICON | wxLC_REPORT | wxBORDER_NONE);
	filesListCtrl->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	filesAreaSizer->Add(filesListCtrl, 1, wxALL | wxEXPAND, this->FromDIP(5));



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

	languageOptionSizer->Add(languageOptionLabel, 2, wxALL | wxEXPAND, this->FromDIP(5));

	wxArrayString langChoiceChoices;
	langChoiceChoices.push_back(currentLang[L"EN"]);
	langChoiceChoices.push_back(currentLang[L"RU"]);

	langChoice = new wxChoice(settingsWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, langChoiceChoices, wxCB_SORT);
	langChoice->SetSelection(0);
	langChoice->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	languageOptionSizer->Add(langChoice, 1, wxALL | wxEXPAND, this->FromDIP(5));


	settingsAreaSizer->Add(languageOptionSizer, 0, wxEXPAND, this->FromDIP(0));

	wxBoxSizer* themeOptionSizer;
	themeOptionSizer = new wxBoxSizer(wxHORIZONTAL);

	themeOptionLabel = new wxStaticText(settingsWorkingAreaPanel, wxID_ANY, currentLang[L"Theme"], wxDefaultPosition, wxDefaultSize, 0);
	themeOptionLabel->Wrap(-1);
	themeOptionLabel->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	themeOptionSizer->Add(themeOptionLabel, 2, wxALL | wxEXPAND, this->FromDIP(5));

	wxArrayString themeChoiceChoices;
	themeChoiceChoices.push_back(currentLang[L"Dark"]);
	themeChoiceChoices.push_back(currentLang[L"Light"]);

	themeChoice = new wxChoice(settingsWorkingAreaPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, themeChoiceChoices, wxCB_SORT);
	themeChoice->SetSelection(0);
	themeChoice->SetFont(wxFont(19, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	themeOptionSizer->Add(themeChoice, 1, wxALL | wxEXPAND, this->FromDIP(5));


	settingsAreaSizer->Add(themeOptionSizer, 0, wxEXPAND, this->FromDIP(0));

	wxBoxSizer* helpOptionSizer;
	helpOptionSizer = new wxBoxSizer(wxHORIZONTAL);

	helpOptionLabel = new wxStaticText(settingsWorkingAreaPanel, wxID_ANY, currentLang[L"HelpOption"], wxDefaultPosition, wxDefaultSize, 0);
	helpOptionLabel->Wrap(-1);
	helpOptionLabel->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	helpOptionSizer->Add(helpOptionLabel, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	helpOptionBtn = new wxBitmapButton(settingsWorkingAreaPanel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW | wxBORDER_NONE);
	helpOptionSizer->Add(helpOptionBtn, 0, wxALL, 5);


	settingsAreaSizer->Add(helpOptionSizer, 0, wxEXPAND, 0);

	settingsFillerLabel = new wxStaticText(settingsWorkingAreaPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	settingsFillerLabel->Wrap(-1);
	settingsAreaSizer->Add(settingsFillerLabel, 1, wxALL | wxEXPAND, 5);

	aboutLabel = new wxStaticText(settingsWorkingAreaPanel, wxID_ANY, currentLang[L"AboutMain"] + '\n' +
		currentLang[L"AboutProgramming"] + '\n' + currentLang[L"AboutIcons"] + '\n' + 
		currentLang[L"AboutTables"], wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	aboutLabel->Wrap(-1);
	settingsAreaSizer->Add(aboutLabel, 0, wxEXPAND | wxALL, 5);

	settingsWorkingAreaPanel->SetSizer(settingsAreaSizer);
	settingsWorkingAreaPanel->Layout();
	settingsAreaSizer->Fit(settingsWorkingAreaPanel);
	genWorkingAreaBook->AddPage(settingsWorkingAreaPanel, wxT("a page"), false);

	mainSizer->Add(genWorkingAreaBook, 1, wxEXPAND | wxALL, this->FromDIP(0));


	genSizer->Add(mainSizer, 1, wxEXPAND, this->FromDIP(0));

	genWorkingAreaBook->ChangeSelection(1);

	if (userSettings["Language"] == "ru")
	{
		langChoice->SetStringSelection(currentLang[L"RU"]);
	}
	else if (userSettings["Language"] == "en")
	{
		langChoice->SetStringSelection(currentLang[L"EN"]);
	}

	if (userSettings["Theme"] == "dark")
	{
		themeChoice->SetStringSelection(currentLang[L"Dark"]);
	}
	else if (userSettings["Theme"] == "light")
	{
		themeChoice->SetStringSelection(currentLang[L"Light"]);
	}

	this->SetSizer(genSizer);
	this->Layout();
}

void MainFrame::BindEventHandlers()
{
	botBtn->Bind(wxEVT_BUTTON, &MainFrame::ChangePageToBot, this);
	//profileBtn->Bind(wxEVT_BUTTON, &MainFrame::ChangePageToProfile, this);
	filesBtn->Bind(wxEVT_BUTTON, &MainFrame::ChangePageToFiles, this);
	settingsBtn->Bind(wxEVT_BUTTON, &MainFrame::ChangePageToSettings, this);
	browseBtn->Bind(wxEVT_BUTTON, &MainFrame::ShowBrowseDialog, this);
	loadFileBtn->Bind(wxEVT_BUTTON, &MainFrame::LoadFile, this);
	delFileButton->Bind(wxEVT_BUTTON, &MainFrame::RemoveFile, this);
	studyBtn->Bind(wxEVT_BUTTON, &MainFrame::ChooseModule, this);
	answerSendBtn->Bind(wxEVT_BUTTON, &MainFrame::ReadAnswer, this);
	answerInputTextCtrl->Bind(wxEVT_TEXT_ENTER, &MainFrame::ReadAnswerOnEnter, this);
	langChoice->Bind(wxEVT_CHOICE, &MainFrame::ChangeLangSettings, this);
	themeChoice->Bind(wxEVT_CHOICE, &MainFrame::ChangeThemeSettings, this);


	// workaroung for setting wxChoice bg color
	if (userSettings["Theme"] == "dark")
	{
		langChoice->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {

			wxPaintDC dc(langChoice);
			wxRect rect(0, 0, dc.GetSize().GetWidth(), dc.GetSize().GetHeight());

			dc.SetBrush(DarkTheme::darkBrush);
			dc.SetPen(DarkTheme::darkPen);
			dc.DrawRectangle(rect);

			dc.DrawBitmap(wxArtProvider::GetBitmap(wxART_GO_DOWN, wxART_OTHER, wxSize(10, 10)), wxPoint(rect.GetWidth() - 15, (rect.GetHeight() / 2) - 5));
			const wxString sel = langChoice->GetStringSelection();

			if (!sel.IsEmpty())
			{
				dc.DrawLabel(sel, rect, wxALIGN_CENTER_VERTICAL);
			}
			});
	}
	else if (userSettings["Theme"] == "light")
	{
		langChoice->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {

			wxPaintDC dc(langChoice);
			wxRect rect(0, 0, dc.GetSize().GetWidth(), dc.GetSize().GetHeight());

			dc.SetBrush(LightTheme::lightBrush);
			dc.SetPen(LightTheme::lightPen);
			dc.DrawRectangle(rect);

			dc.DrawBitmap(wxArtProvider::GetBitmap(wxART_GO_DOWN, wxART_OTHER, wxSize(10, 10)), wxPoint(rect.GetWidth() - 15, (rect.GetHeight() / 2) - 5));
			const wxString sel = langChoice->GetStringSelection();

			if (!sel.IsEmpty())
			{
				dc.DrawLabel(sel, rect, wxALIGN_CENTER_VERTICAL);
			}
			});
	}

	if (userSettings["Theme"] == "dark")
	{
		themeChoice->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {

			wxPaintDC dc(themeChoice);
			wxRect rect(0, 0, dc.GetSize().GetWidth(), dc.GetSize().GetHeight());

			dc.SetBrush(DarkTheme::darkBrush);
			dc.SetPen(DarkTheme::darkPen);
			dc.DrawRectangle(rect);

			dc.DrawBitmap(wxArtProvider::GetBitmap(wxART_GO_DOWN, wxART_OTHER, wxSize(10, 10)), wxPoint(rect.GetWidth() - 15, (rect.GetHeight() / 2) - 5));
			const wxString sel = themeChoice->GetStringSelection();

			if (!sel.IsEmpty())
			{
				dc.DrawLabel(sel, rect, wxALIGN_CENTER_VERTICAL);
			}
			});
	}
	else if (userSettings["Theme"] == "light")
	{
		themeChoice->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {

			wxPaintDC dc(themeChoice);
			wxRect rect(0, 0, dc.GetSize().GetWidth(), dc.GetSize().GetHeight());

			dc.SetBrush(LightTheme::lightBrush);
			dc.SetPen(LightTheme::lightPen);
			dc.DrawRectangle(rect);

			dc.DrawBitmap(wxArtProvider::GetBitmap(wxART_GO_DOWN, wxART_OTHER, wxSize(10, 10)), wxPoint(rect.GetWidth() - 15, (rect.GetHeight() / 2) - 5));
			const wxString sel = themeChoice->GetStringSelection();

			if (!sel.IsEmpty())
			{
				dc.DrawLabel(sel, rect, wxALIGN_CENTER_VERTICAL);
			}
			});
	}
}

void MainFrame::ApplyTheme()
{
	wxString pathToFileIcons = wxGetCwd() + "\\Icons\\FileIcons\\";
	wxString pathToIcons = wxGetCwd() + "\\Icons\\";

	if (userSettings["Theme"] == "dark")
	{
		browseDialog->browseList->SetBackgroundColour(DarkTheme::dark);
		browseDialog->browseList->SetForegroundColour(DarkTheme::light);
	}
	else if (userSettings["Theme"] == "light")
	{
		browseDialog->browseList->SetBackgroundColour(LightTheme::cyan);
		browseDialog->browseList->SetForegroundColour(LightTheme::green);
	}

	if (userSettings["Theme"] == "dark")
	{
		leftPanel->SetBackgroundColour(DarkTheme::darkest);
		botBtn->SetBackgroundColour(DarkTheme::darkest);
		filesBtn->SetBackgroundColour(DarkTheme::darkest);
		settingsBtn->SetBackgroundColour(DarkTheme::darkest);
		genWorkingAreaBook->SetBackgroundColour(DarkTheme::darkest);
		chatWorkingAreaPanel->SetBackgroundColour(DarkTheme::darkest);
		chatHtmlWindow->SetBackgroundColour(DarkTheme::dark);
		answerSendBtn->SetBackgroundColour(DarkTheme::darkest);
		filesWorkingAreaPanel->SetBackgroundColour(DarkTheme::darkest);
		filesListCtrl->SetBackgroundColour(DarkTheme::dark);
		answerInputTextCtrl->SetBackgroundColour(DarkTheme::dark);
		settingsWorkingAreaPanel->SetBackgroundColour(DarkTheme::darkest);
		langChoice->SetBackgroundColour(DarkTheme::dark);
		themeChoice->SetBackgroundColour(DarkTheme::dark);
		langChoice->SetOwnBackgroundColour(DarkTheme::dark);

		filesTitleLabel->SetForegroundColour(DarkTheme::light);
		loadFileBtn->SetForegroundColour(DarkTheme::light);
		delFileButton->SetForegroundColour(DarkTheme::light);
		filesListCtrl->SetForegroundColour(DarkTheme::light);
		studyBtn->SetForegroundColour(DarkTheme::light);
		browseBtn->SetForegroundColour(DarkTheme::light);
		answerInputTextCtrl->SetForegroundColour(DarkTheme::light);
		languageOptionLabel->SetForegroundColour(DarkTheme::light);
		langChoice->SetForegroundColour(DarkTheme::light);
		themeOptionLabel->SetForegroundColour(DarkTheme::light);
		themeChoice->SetForegroundColour(DarkTheme::light);
		helpOptionLabel->SetForegroundColour(DarkTheme::light);
		aboutLabel->SetForegroundColour(DarkTheme::light);

		botBtn->SetBitmap(wxBitmap(pathToIcons + "darkBotBtn.png", wxBITMAP_TYPE_ANY));
		botBtn->SetBitmapDisabled(wxBitmap(pathToIcons + "darkBotBtnPressed.png", wxBITMAP_TYPE_ANY));

		filesBtn->SetBitmap(wxBitmap(pathToIcons + "darkFileBtn.png", wxBITMAP_TYPE_ANY));
		filesBtn->SetBitmapDisabled(wxBitmap(pathToIcons + "darkFileBtnPressed.png", wxBITMAP_TYPE_ANY));

		settingsBtn->SetBitmap(wxBitmap(pathToIcons + "darkSettingsBtn.png", wxBITMAP_TYPE_ANY));
		settingsBtn->SetBitmapDisabled(wxBitmap(pathToIcons + "darkSettingsBtnPressed.png", wxBITMAP_TYPE_ANY));

		answerSendBtn->SetBitmap(wxBitmap(pathToIcons + "darkSendBtn.png", wxBITMAP_TYPE_ANY));
		answerSendBtn->SetBitmapPressed(wxBitmap(pathToIcons + "darkSendBtnPressed.png", wxBITMAP_TYPE_ANY));

		helpOptionBtn->SetBitmap(wxBitmap(pathToIcons + "darkHelp.png", wxBITMAP_TYPE_ANY));
		helpOptionBtn->SetBitmapPressed(wxBitmap(pathToIcons + "darkHelpPressed.png", wxBITMAP_TYPE_ANY));
		helpOptionBtn->SetBackgroundColour(DarkTheme::darkest);

		if (userSettings["Language"] == "en")
		{
			loadFileBtn->SetBitmap(wxBitmap(pathToFileIcons + "ImportDarkEn.png", wxBITMAP_TYPE_ANY));
			loadFileBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "ImportDarkPressedEn.png", wxBITMAP_TYPE_ANY));

			delFileButton->SetBitmap(wxBitmap(pathToFileIcons + "DeleteDarkEn.png", wxBITMAP_TYPE_ANY));
			delFileButton->SetBitmapPressed(wxBitmap(pathToFileIcons + "DeleteDarkPressedEn.png", wxBITMAP_TYPE_ANY));

			studyBtn->SetBitmap(wxBitmap(pathToFileIcons + "StudyDarkEn.png", wxBITMAP_TYPE_ANY));
			studyBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "StudyDarkPressedEn.png", wxBITMAP_TYPE_ANY));

			browseBtn->SetBitmap(wxBitmap(pathToFileIcons + "BrowseDarkEn.png", wxBITMAP_TYPE_ANY));
			browseBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "BrowseDarkPressedEn.png", wxBITMAP_TYPE_ANY));
		}
		else if (userSettings["Language"] == "ru")
		{
			loadFileBtn->SetBitmap(wxBitmap(pathToFileIcons + "ImportDarkRu.png", wxBITMAP_TYPE_ANY));
			loadFileBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "ImportDarkPressedRu.png", wxBITMAP_TYPE_ANY));

			delFileButton->SetBitmap(wxBitmap(pathToFileIcons + "DeleteDarkRu.png", wxBITMAP_TYPE_ANY));
			delFileButton->SetBitmapPressed(wxBitmap(pathToFileIcons + "DeleteDarkPressedRu.png", wxBITMAP_TYPE_ANY));

			studyBtn->SetBitmap(wxBitmap(pathToFileIcons + "StudyDarkRu.png", wxBITMAP_TYPE_ANY));
			studyBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "StudyDarkPressedRu.png", wxBITMAP_TYPE_ANY));

			browseBtn->SetBitmap(wxBitmap(pathToFileIcons + "BrowseDarkRu.png", wxBITMAP_TYPE_ANY));
			browseBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "BrowseDarkPressedRu.png", wxBITMAP_TYPE_ANY));
		}

		htmlContents += "<BODY BGCOLOR=\"#151E3F\">";
		htmlContents += "<FONT COLOR=\"#F2F3D9\"";
	}
	else if (userSettings["Theme"] == "light")
	{
		leftPanel->SetBackgroundColour(LightTheme::cyan);
		botBtn->SetBackgroundColour(LightTheme::cyan);
		filesBtn->SetBackgroundColour(LightTheme::cyan);
		settingsBtn->SetBackgroundColour(LightTheme::cyan);
		genWorkingAreaBook->SetBackgroundColour(LightTheme::cyan);
		chatWorkingAreaPanel->SetBackgroundColour(LightTheme::cyan);
		chatHtmlWindow->SetBackgroundColour(LightTheme::cyan);
		answerSendBtn->SetBackgroundColour(LightTheme::cyan);
		filesWorkingAreaPanel->SetBackgroundColour(LightTheme::cyan);
		filesListCtrl->SetBackgroundColour(LightTheme::light);
		answerInputTextCtrl->SetBackgroundColour(LightTheme::light);
		settingsWorkingAreaPanel->SetBackgroundColour(LightTheme::cyan);
		langChoice->SetBackgroundColour(LightTheme::light);
		themeChoice->SetBackgroundColour(LightTheme::light);
		langChoice->SetOwnBackgroundColour(LightTheme::light);

		filesTitleLabel->SetForegroundColour(LightTheme::green);
		loadFileBtn->SetForegroundColour(LightTheme::green);
		delFileButton->SetForegroundColour(LightTheme::green);
		filesListCtrl->SetForegroundColour(LightTheme::green);
		studyBtn->SetForegroundColour(LightTheme::green);
		browseBtn->SetForegroundColour(LightTheme::green);
		answerInputTextCtrl->SetForegroundColour(LightTheme::green);
		languageOptionLabel->SetForegroundColour(LightTheme::green);
		langChoice->SetForegroundColour(LightTheme::green);
		themeOptionLabel->SetForegroundColour(LightTheme::green);
		themeChoice->SetForegroundColour(LightTheme::green);
		helpOptionLabel->SetForegroundColour(LightTheme::green);
		aboutLabel->SetForegroundColour(LightTheme::green);

		botBtn->SetBitmap(wxBitmap(pathToIcons + "lightBotBtn.png", wxBITMAP_TYPE_ANY));
		botBtn->SetBitmapDisabled(wxBitmap(pathToIcons + "lightBotBtnPressed.png", wxBITMAP_TYPE_ANY));

		filesBtn->SetBitmap(wxBitmap(pathToIcons + "lightFileBtn.png", wxBITMAP_TYPE_ANY));
		filesBtn->SetBitmapDisabled(wxBitmap(pathToIcons + "lightFileBtnPressed.png", wxBITMAP_TYPE_ANY));

		settingsBtn->SetBitmap(wxBitmap(pathToIcons + "lightSettingsBtn.png", wxBITMAP_TYPE_ANY));
		settingsBtn->SetBitmapDisabled(wxBitmap(pathToIcons + "lightSettingsBtnPressed.png", wxBITMAP_TYPE_ANY));

		answerSendBtn->SetBitmap(wxBitmap(pathToIcons + "lightSendBtn.png", wxBITMAP_TYPE_ANY));
		answerSendBtn->SetBitmapPressed(wxBitmap(pathToIcons + "lightSendBtnPressed.png", wxBITMAP_TYPE_ANY));

		helpOptionBtn->SetBitmap(wxBitmap(pathToIcons + "lightHelp.png", wxBITMAP_TYPE_ANY));
		helpOptionBtn->SetBitmapPressed(wxBitmap(pathToIcons + "lightHelpPressed.png", wxBITMAP_TYPE_ANY));
		helpOptionBtn->SetBackgroundColour(LightTheme::cyan);

		if (userSettings["Language"] == "en")
		{
			loadFileBtn->SetBitmap(wxBitmap(pathToFileIcons + "ImportLightEn.png", wxBITMAP_TYPE_ANY));
			loadFileBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "ImportLightPressedEn.png", wxBITMAP_TYPE_ANY));

			delFileButton->SetBitmap(wxBitmap(pathToFileIcons + "DeleteLightEn.png", wxBITMAP_TYPE_ANY));
			delFileButton->SetBitmapPressed(wxBitmap(pathToFileIcons + "DeleteLightPressedEn.png", wxBITMAP_TYPE_ANY));

			studyBtn->SetBitmap(wxBitmap(pathToFileIcons + "StudyLightEn.png", wxBITMAP_TYPE_ANY));
			studyBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "StudyLightPressedEn.png", wxBITMAP_TYPE_ANY));

			browseBtn->SetBitmap(wxBitmap(pathToFileIcons + "BrowseLightEn.png", wxBITMAP_TYPE_ANY));
			browseBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "BrowseLightPressedEn.png", wxBITMAP_TYPE_ANY));
		}
		else if (userSettings["Language"] == "ru")
		{
			loadFileBtn->SetBitmap(wxBitmap(pathToFileIcons + "ImportLightRu.png", wxBITMAP_TYPE_ANY));
			loadFileBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "ImportLightPressedRu.png", wxBITMAP_TYPE_ANY));

			delFileButton->SetBitmap(wxBitmap(pathToFileIcons + "DeleteLightRu.png", wxBITMAP_TYPE_ANY));
			delFileButton->SetBitmapPressed(wxBitmap(pathToFileIcons + "DeleteLightPressedRu.png", wxBITMAP_TYPE_ANY));

			studyBtn->SetBitmap(wxBitmap(pathToFileIcons + "StudyLightRu.png", wxBITMAP_TYPE_ANY));
			studyBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "StudyLightPressedRu.png", wxBITMAP_TYPE_ANY));

			browseBtn->SetBitmap(wxBitmap(pathToFileIcons + "BrowseLightRu.png", wxBITMAP_TYPE_ANY));
			browseBtn->SetBitmapPressed(wxBitmap(pathToFileIcons + "BrowseLightPressedRu.png", wxBITMAP_TYPE_ANY));
		}

		htmlContents += "<BODY BGCOLOR=\"#FFFFFF\">";
		htmlContents += "<FONT COLOR=\"#254441\"";
	}
}

void MainFrame::ChangePageToBot(wxCommandEvent& event)
{
	genWorkingAreaBook->ChangeSelection(0);

	botBtn->Disable();
	//profileBtn->Enable(true);
	filesBtn->Enable(true);
	settingsBtn->Enable(true);
}

//void MainFrame::ChangePageToProfile(wxCommandEvent& event)
//{
//	genWorkingAreaBook->ChangeSelection(1);
//
//	botBtn->Enable(true);;
//	//profileBtn->Disable();
//	filesBtn->Enable(true);
//	settingsBtn->Enable(true);
//}

void MainFrame::ChangePageToFiles(wxCommandEvent& event)
{
	genWorkingAreaBook->ChangeSelection(1);

	botBtn->Enable(true);
	//profileBtn->Enable(true);
	filesBtn->Disable();
	settingsBtn->Enable(true);
}

void MainFrame::ChangePageToSettings(wxCommandEvent& event)
{
	genWorkingAreaBook->ChangeSelection(2);

	botBtn->Enable(true);;
	//profileBtn->Enable(true);
	filesBtn->Enable(true);
	settingsBtn->Disable();
}

void MainFrame::FillModulesList(std::vector<Module> modules)
{
	filesListCtrl->InsertColumn(1, currentLang[L"ModuleForStats"], wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);

	int size = modules.size();
	for (size_t i = 0; i < size; i++)
	{
		filesListCtrl->SetItem(filesListCtrl->InsertItem(i, modules.at(i).GetModuleName()), 0, modules.at(i).GetModuleName());
	}

	//filesListCtrl->SetColumnWidth(0, wxLIST_AUTOSIZE);
	filesListCtrl->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
}

//void MainFrame::FillStatsList(std::vector<Module> modules)
//{
//	statsListCtrl->InsertColumn(0, currentLang[L"FileName"], wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
//	statsListCtrl->InsertColumn(1, currentLang[L"ModuleForStats"], wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
//	statsListCtrl->InsertColumn(2, currentLang[L"Stats"], wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
//
//	std::string stat;
//	int size = modules.size();
//	for (size_t i = 0; i < size; i++)
//	{
//		long index = statsListCtrl->InsertItem(i, modules[i].GetFileName());
//		statsListCtrl->SetItem(index, 1, modules[i].GetModuleName());
//		stat = std::to_string(modules[i].GetAnsweredCorrectly()) + '/' + std::to_string(modules[i].GetTimesAsked());
//		statsListCtrl->SetItem(index, 2, stat);
//	}
//
//	statsListCtrl->SetColumnWidth(0, wxLIST_AUTOSIZE);
//	statsListCtrl->SetColumnWidth(1, wxLIST_AUTOSIZE);
//	statsListCtrl->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
//}

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
		if (mod.GetModuleName() == filesListCtrl->GetItemText(item, 0))
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

	const wxString pathtoDest = wxGetCwd() + "\\Tables\\";

	wxFileDialog fileDialog(this, "Select file", "", "", "TSV Files (*.tsv;*.txt) | *.tsv;*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	if (fileDialog.ShowModal() == wxID_OK)
	{
		pathToFile = fileDialog.GetPath();
		
		wxCopyFile(pathToFile, pathtoDest + fileDialog.GetFilename(), false);
		UpdateModuleList(modules);
	}
	

	
}

void MainFrame::RemoveFile(wxCommandEvent& event)
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
	wxString modName;

	for (;;)
	{
		item = filesListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (item == -1)
			break;

		modName = filesListCtrl->GetItemText(item, 0);
	}


	std::filesystem::path pathToCwd = std::filesystem::current_path();
	std::filesystem::path pathToTables = pathToCwd / "Tables";
	for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(pathToTables))
	{
		std::filesystem::path filePath = dirEntry.path();
		std::string strFilePath = filePath.string();
		std::string baseFilename = strFilePath.substr(strFilePath.find_last_of("/\\") + 1);
		std::string::size_type const p(baseFilename.find_last_of('.'));
		std::string fileWithoutExtention = baseFilename.substr(0, p);

		if (fileWithoutExtention == modName)
		{
			wxRemoveFile(strFilePath);
			UpdateModuleList(modules);
			break;
		}
	}
}


void MainFrame::TransferModules(std::vector<Module> modules)
{
	localModules = modules;
}

void MainFrame::ChangeLangSettings(wxCommandEvent& event)
{
	if (langChoice->GetStringSelection() == currentLang[L"EN"])
	{
		FileHandler::UpdateUserSettingsMap("Language", "en", userSettings);
		FileHandler::UpdateUserSettingsFile(userSettings);
	}
	else if (langChoice->GetStringSelection() == currentLang[L"RU"])
	{
		FileHandler::UpdateUserSettingsMap("Language", "ru", userSettings);
		FileHandler::UpdateUserSettingsFile(userSettings);
	}
}

void MainFrame::ChangeThemeSettings(wxCommandEvent& event)
{
	if (themeChoice->GetStringSelection() == currentLang[L"Dark"])
	{
		FileHandler::UpdateUserSettingsMap("Theme", "dark", userSettings);
		FileHandler::UpdateUserSettingsFile(userSettings);
	}
	else if (themeChoice->GetStringSelection() == currentLang[L"Light"])
	{
		FileHandler::UpdateUserSettingsMap("Theme", "light", userSettings);
		FileHandler::UpdateUserSettingsFile(userSettings);
	}
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
		for (auto mod : localModules)
		{
			if (mod.GetModuleName() == filesListCtrl->GetItemText(item, 0))
			{
				currentModule = mod;
			}
		}
	}

	genWorkingAreaBook->ChangeSelection(0);

	botBtn->Disable();
	//profileBtn->Enable(true);
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


	wxString answ = answerInputTextCtrl->GetValue();

	if (answ.IsEmpty())
	{
		return;
	}

	htmlContents += "<br><html><body>";
	htmlContents += "<div ALIGN = \"RIGHT\">";
	htmlContents += answerInputTextCtrl->GetValue();
	htmlContents += "</div></body></html><br><br>";
	chatHtmlWindow->SetPage(htmlContents);
	ScrollToBottom();


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

	
	answerInputTextCtrl->Clear();
}

void MainFrame::ReadAnswerOnEnter(wxCommandEvent& event)
{
	if (userState == CHOOSING_MODULE)
	{
		return;
	}

	wxString answ = answerInputTextCtrl->GetValue();

	if (answ.IsEmpty())
	{
		return;
	}

	htmlContents += "<br><html><body>";
	htmlContents += "<div ALIGN = \"RIGHT\">";
	htmlContents += answerInputTextCtrl->GetValue();
	htmlContents += "</div></body></html><br><br>";
	chatHtmlWindow->SetPage(htmlContents);
	ScrollToBottom();


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
	htmlContents += "</body></html><br><br>";

	chatHtmlWindow->SetPage(htmlContents);
	ScrollToBottom();
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
	ScrollToBottom();
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
		userState = CHOOSING_MODE;
	}
	else if (CheckAnswerArrays(kanji, answer))
	{
		currentVocabOrKanji = KANJI;
		currentSymbols = currentModule.GetKanjiList();
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
		ScrollToBottom();
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
		ScrollToBottom();
	}

	if (currentVocabOrKanji != NOT_CHOSEN)
	{
		std::shuffle(std::begin(currentSymbols), std::end(currentSymbols), rng);
	}
	ScrollToBottom();

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
		ScrollToBottom();

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
		ScrollToBottom();

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
		ScrollToBottom();
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
		ScrollToBottom();

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
		ScrollToBottom();

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
		ScrollToBottom();

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
	if (CheckAnswerArrays(no, answer))
	{
		ResetStudy();
		userState = CHOOSING_MODULE;
		return;
	}

	if (answer.empty())
	{
		return;
	}
	if (CheckAnswerArrays(start, answer))
	{
		userState = STUDYING;
		questionsAsked = 0;

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

		ScrollToBottom();
	}
	else
	{
		DoNotUnderstandAnswer();
	}
}

void MainFrame::ProcessAnswerWhenStudy()
{
	//UpdateStats(localModules);
	
	AskQuestion();
	
}

void MainFrame::DoNotUnderstandAnswer()
{
	htmlContents += "<html><body>";
	htmlContents+= currentLang[L"DoNotUnderstand"];
	htmlContents += "</body></html>";
	chatHtmlWindow->SetPage(htmlContents);
	ScrollToBottom();
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
	ScrollToBottom();
	questionsAsked += 1;
	currentQuestion += 1;
	//UpdateStats(localModules);

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
			ScrollToBottom();
			userState = GETTING_READY;
		}
	}
}

void MainFrame::ScrollToBottom()
{
	int x;
	int y;
	int xUnit;
	int yUnit;

	chatHtmlWindow->GetVirtualSize(&x, &y);
	chatHtmlWindow->GetScrollPixelsPerUnit(&xUnit, &yUnit);
	chatHtmlWindow->Scroll(0, y / yUnit);
}

//void MainFrame::UpdateStats(std::vector<Module>& inModules)
//{
//	//currentModule.SetStats(questionsAsked, questionsAsked - currentMistakes.size());
//	/*inCurrentModule.timesAsked = questionsAsked;
//	inCurrentModule.answeredCorrectly = questionsAsked - currentMistakes.size();*/
//
//	for (auto mod : inModules)
//	{
//		if (mod.GetFileName() == currentModule.GetFileName() && mod.GetModuleName() == currentModule.GetModuleName())
//		{
//			mod.timesAsked = questionsAsked;
//			mod.answeredCorrectly = questionsAsked - currentMistakes.size();
//		}
//	}
//
//	SaveStatsToFile(inModules);
//}

//void MainFrame::SaveStatsToFile(std::vector<Module>& inModules)
//{
//	std::ofstream outfile;
//	outfile.open("./Settings/stats.tsv");
//
//	if (!outfile.fail())
//	{
//		for (auto iter = inModules.begin(); iter != inModules.end(); iter++)
//		{
//			outfile << iter->GetFileName() << '\t' << iter->GetModuleName() << '\t' << 
//				std::to_string(iter->timesAsked) << '\t' << std::to_string(iter->answeredCorrectly) << '\n';
//		}
//	}
//}

//void MainFrame::LoadStatsFromFile(std::vector<Module> inModules)
//{
//	std::ifstream infile("./Settings/stats.tsv");
//	std::string line;
//	std::vector<std::string> statsFileContents;
//
//	while (std::getline(infile, line))
//	{
//
//		FileHandler::Split(line, '\t', statsFileContents);
//
//	}
//
//	
//		
//	
//	for (auto mod : inModules)
//	{
//		int size = statsFileContents.size();
//		for (size_t i = 0; i < size; i += 4)
//		{
//			if (statsFileContents[i] == mod.GetFileName() &&
//				statsFileContents[i + 1] == mod.GetModuleName())
//			{
//				mod.timesAsked = stoi(statsFileContents[i + 2]);
//				mod.answeredCorrectly = stoi(statsFileContents[i + 3]);
//
//			}
//		}
//	}
//}


void MainFrame::UpdateModuleList(std::vector<Module>& inModules)
{
	filesListCtrl->ClearAll();
	//filesListCtrl->DeleteAllItems();
	//filesListCtrl->DeleteAllColumns();

	inModules.clear();

	FileHandler::ReadTsvFiles(inModules);
	TransferModules(inModules);

	FillModulesList(localModules);
	filesListCtrl->RefreshItems(filesListCtrl->GetTopItem(), filesListCtrl->GetItemCount() - 1);
}


MainFrame::MainFrame(const wxString& title)
	:
	wxFrame(nullptr, wxID_ANY, title)
{
	FileHandler::ReadTsvFiles(modules);
	FileHandler::ReadUserSettingsFile(userSettings);
	FileHandler::ReadLocFile(currentLang, userSettings);

	CreateControls();
	BindEventHandlers();

	
	TransferModules(modules);
	FillModulesList(localModules);


	
	ApplyTheme();
	
	this->Centre(wxBOTH);
	this->SetMinClientSize(this->FromDIP(wxSize(720, 480)));
	
	WriteInitialGreeting();
}


