#pragma once
#include <wx/colour.h>
#include <wx/pen.h>

namespace DarkTheme
{
	static wxColor dark(21, 30, 63);
	static wxColor darkest(3, 0, 39);
	static wxColor light(242, 243, 217);
	static wxColor orange(220, 158, 130);
	static wxColor red(193, 110, 112);

	static wxBrush darkBrush(dark, wxBRUSHSTYLE_SOLID);
	static wxPen darkPen(dark, wxPENSTYLE_SOLID);
	static wxPen darkestPen(darkest, wxPENSTYLE_SOLID);
}

namespace LightTheme
{
	static wxColor red(219, 80, 74);
	static wxColor orange(255, 111, 89);
	static wxColor green(37, 68, 65);
	static wxColor cyan(67, 170, 139);
	//static wxColor light(178, 176, 155);
	static wxColor light(255, 255, 255);

	static wxBrush lightBrush(light, wxBRUSHSTYLE_SOLID);
	static wxPen lightPen(light, wxPENSTYLE_SOLID);
}