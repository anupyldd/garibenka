#include "BrowseDialog.h"

BrowseDialog::BrowseDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(this->FromDIP(wxSize(720, 480)), wxDefaultSize);

	wxBoxSizer* browseSizer;
	browseSizer = new wxBoxSizer(wxVERTICAL);

	browseList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES | wxLC_ICON | wxLC_REPORT | wxLC_SINGLE_SEL);
	browseSizer->Add(browseList, 1, wxALL | wxEXPAND, this->FromDIP(5));
	browseList->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	

	this->SetSizer(browseSizer);
	this->Layout();
	browseSizer->Fit(this);

	this->Centre(wxBOTH);
}

void BrowseDialog::AddToList(std::wstring inSymbol, std::wstring inReading, std::wstring inMeaning, int iter)
{
	long index = browseList->InsertItem(iter, inSymbol);
	browseList->SetItem(index, 1, inReading);
	browseList->SetItem(index, 2, inMeaning);
}

void BrowseDialog::AdjustSize()
{
	browseList->SetColumnWidth(0, wxLIST_AUTOSIZE);
	browseList->SetColumnWidth(1, wxLIST_AUTOSIZE);
	browseList->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
}

void BrowseDialog::ClearList()
{
	browseList->ClearAll();
}

void BrowseDialog::AddColumns()
{
	browseList->InsertColumn(0, currentLang[L"Symbol"], wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
	browseList->InsertColumn(1, currentLang[L"Reading"], wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
	browseList->InsertColumn(2, currentLang[L"Meaning"], wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE);
}

BrowseDialog::~BrowseDialog()
{
}
