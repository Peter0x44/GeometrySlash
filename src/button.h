#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include <functional>
#include <raylib.h>

//typedef Rectangle (*)(void);

class Button
{
public:
	void draw(void);
	bool clicked(void);
//	Button(Rectangle (*_RectCallback)(void));
	Button(const std::function<Rectangle(void)>& RectCallback);
private:
	float _fontSize;
	std::string _text;
//	Rectangle (*_RectCallback)(void);
	
	std::function<Rectangle(void)> _RectCallback;
//	std::function<Vector2(void)> _TextPosCallback;
//	std::function<float(void)> _FontSizeCallback;
};

#endif
