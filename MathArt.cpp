#include <Windows.h>
#include <cmath>
#include <random>
#include <iostream>
using namespace std;

class Graphics
{
	int x;
	int y;
	int WIDTH;
	int HEIGHT;
public: Graphics(int xIn, int yIn, int widIn, int heiIn)
	{
	x = xIn;
	y = yIn;
	WIDTH = widIn;
	HEIGHT = heiIn;
	}
    HWND makeWin()
	{
		COLORREF c = RGB(255, 255, 255);
		WNDCLASS wc = {};
		wc.lpfnWndProc = DefWindowProc;
		wc.lpszClassName = L"winClass";
		wc.hbrBackground = CreateSolidBrush(c);
		RegisterClass(&wc);
		HWND hwnd = CreateWindow(L"winClass", L"ArtWin", WS_OVERLAPPEDWINDOW, 
		x, y, WIDTH, HEIGHT, NULL, NULL, NULL, NULL);
		ShowWindow(hwnd, SW_SHOW);
		return hwnd;
	}
	void closeConsole()
	{
		HWND wnd = GetConsoleWindow();
		ShowWindow(wnd, SW_HIDE);
	}
};
class vec4
{
public:
	int x1, y1, x2, y2;
vec4(int x1In, int y1In, int x2In, int y2In)
{
	x1 = x1In;
	y1 = y1In;
	x2 = x2In;
	y2 = y2In;
}
};
class spinner
{
public:
	float rad, speed, dir, angle;
	int x, y, x2, y2;
spinner(float radius, float spinSpeed, float spinDir, int xIn, int yIn, float ang)
{
	rad = radius;
	speed = spinSpeed;
	dir = spinDir;
	x = xIn;
	y = yIn;
	angle = ang;
	x2 = (cos(ang) * rad) + x;
	y2 = (sin(ang) * rad) + y;
}
	void updateSpin()
    {
		if (dir > 0) angle += speed;
		if (dir < 0) angle -= speed;
	}
	void setXY(int xIn, int yIn)
	{
		x = xIn;
		y = yIn;
	}
	vec4 getPos()
	{
		x2 = (cos(angle) * rad) + x;
		y2 = (sin(angle) * rad) + y;
		vec4 vec(x, y, x2, y2);
		return vec;
	}
};

int main()
{
	float radOne, radTwo, radThree;
	float spinOne, spinTwo, spinThree;
	cout << "First Radius: ";
	cin >> radOne;
	cout << "Second Radius: ";
	cin >> radTwo;
	cout << "Third Radius: ";
	cin >> radThree;
	cout << "Spin speed 01: ";
	cin >> spinOne;
	cout << "Spin speed 02: ";
	cin >> spinTwo;
	cout << "Spin speed 03: ";
	cin >> spinThree;
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	Graphics g(200, 200, 500, 500);
	HWND wnd = g.makeWin();
	g.closeConsole();
	srand((unsigned)time(NULL));
	spinner first(radOne, spinOne, 1.0f, 250, 250, 90.0f);
	spinner second(radTwo, spinTwo, -1.0f, first.x2, first.y2, 90.0f);
	spinner third(radThree, spinThree, -1.0f, second.x2, second.y2, -90.0f);	MSG msg = {};
	while (true) 
	{
		if (PeekMessage(&msg, wnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		HDC dc = GetDC(wnd);
		first.updateSpin();
		vec4 vec = first.getPos();
		second.setXY(vec.x2, vec.y2);
		second.updateSpin();
		vec4 vec02 = second.getPos();
		third.setXY(vec02.x2, vec02.y2);
		third.updateSpin();
		vec4 vec03 = third.getPos();
		SetPixel(dc, vec03.x2, vec03.y2, RGB(0, 0, 0));
	}
    return 0;
}
