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
	void logic(void);
	bool clicked(void);
	Button(const std::function<Rectangle(void)>& RectCallback, const std::function<float(void)>& FontSizeCallback, const std::string& Text);
private:
	float _FontSize;
	Rectangle _Rect;
	std::string _Text;
	std::function<Rectangle(void)> _RectCallback;
	std::function<float(void)> _FontSizeCallback;
	Vector2 _TextDims;
	Vector2 _TextPos;
};

#endif
