#include <functional>
#include <string>
#include <raylib.h>
#include "button.h"

bool Button::clicked(void)
{
	if (CheckCollisionPointRec(GetMousePosition(), _RectCallback()) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		return true;
	else
		return false;
}

void Button::draw(void)
{
	DrawRectangleRounded(_RectCallback(), 0.5f, 0, LIGHTGRAY);

//	MeasureTextEx(

//	DrawTextEx(GetFontDefault(), _text.c_str(), TextPosCallback, _fontSize, _fontSize/10, BLACK);
//	DrawTextV
}

//Button::Button(Rectangle (*RectCallback)(void))
//{
//	_RectCallback = RectCallback;
//}
//Button::Button(std::function<Rectangle(void)> RectCallback)
Button::Button(const std::function<Rectangle(void)>& RectCallback)
{
	_RectCallback = RectCallback;
}

//Button::Button(float fontSize, std::string& text, std::function<Rectangle(void)> _RectCallback, std::function<Vector2(void)> _TextPosCallback, std::function<float(void)> FontSizeCallback)
//{
//	_RectCallback = RectCallback;
//	_TextPosCallback = TextPosCallback;
//	_FontSizeCallback = FontSizeCallback;
//	_text = text;
//}
