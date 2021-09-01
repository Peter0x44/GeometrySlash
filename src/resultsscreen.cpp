#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION


#include "resultsscreen.h"

char bruh[90] = "deez nuts                                         ";


void ResultsScreen::logic(void)
{

}

void ResultsScreen::render(void)
{
	GuiTextBox(Rectangle{ GetScreenHeight()/2, GetScreenWidth()/2, 250, 50 }, bruh, 15, true);
}
