#include <functional>
#include <string>
#include <raylib.h>
#include "button.h"

bool Button::clicked(void)
{
	if (CheckCollisionPointRec(GetMousePosition(), _Rect) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		return true;
	else
		return false;
}

void Button::draw(void)
{
	DrawRectangleRounded(_Rect, 0.5f, 0, LIGHTGRAY);
	DrawTextEx(GetFontDefault(), _Text.c_str(), _TextPos, _FontSize, _FontSize/10, BLACK);
}

void Button::logic(void)
{
	if (IsWindowResized())
	{
		_Rect = _RectCallback();
		_FontSize = _FontSizeCallback();
		_TextDims = MeasureTextEx(GetFontDefault(), _Text.c_str(), _FontSize, _FontSize/10);
		_TextPos.x = _Rect.x + _Rect.width/2 - _TextDims.x/2;
		_TextPos.y = _Rect.y + _Rect.height/2 - _TextDims.y/2;
	}
}

Button::Button(const std::function<Rectangle(void)>& RectCallback, const std::function<float(void)>& FontSizeCallback, const std::string& Text)
{
	// Callback funtion that calculates the rectangle the button is drawn as
	_RectCallback = RectCallback;
	_Rect = _RectCallback();
	// Callback function that calculates the size of the font
	_FontSizeCallback = FontSizeCallback;
	_FontSize = _FontSizeCallback();

	_Text = Text;


	_TextDims = MeasureTextEx(GetFontDefault(), _Text.c_str(), _FontSize, _FontSize/10);
	_TextPos.x = _Rect.x + _Rect.width/2 - _TextDims.x/2;
	_TextPos.y = _Rect.y + _Rect.height/2 - _TextDims.y/2;
}
