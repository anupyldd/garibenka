#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include "FileLoader.h"


class BrowseDialog : public wxDialog
{
private:

protected:

public:
	wxListCtrl* browseList;

	BrowseDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Module Browser"), 
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
		long style = wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxMAXIMIZE_BOX | wxMINIMIZE_BOX | wxRESIZE_BORDER);

	void AddToList(std::wstring inSymbol, std::wstring inReading, std::wstring inMeaning, int iter);
	void AdjustSize();
	void ClearList();
	void AddColumns();

	~BrowseDialog();

};