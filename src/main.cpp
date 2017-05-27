#include <include.h>
#include <Windows.h>
#include <array>
#include <Cardiogram.h>
#include <Image.h>

struct FileNames
{
	std::string absFileName;
	std::string fileName;
};

using Images = std::array<Image, Cardiogram::IMAGES_COUNT>;

enum ButtonCmds
{
	CARD_1 = 1, 
	CARD_2,
	CARD_3, 
	CARD_AVR, 
	CARD_AVL,
	CARD_AVF,
	CARD_V1,
	CARD_V2,
	CARD_V3,
	CARD_V4,
	CARD_V5,
	CARD_V6,
	ANALYZE = 150
};

FileNames Loading();

void createButtons(HINSTANCE hInstance, HWND hWnd);
void onButtonClick(HWND hWnd, WPARAM wParam, Images& images);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static Images images = { CARD_1, CARD_2, CARD_3, CARD_AVR, CARD_AVL, CARD_AVF,
					  CARD_V1, CARD_V2, CARD_V3, CARD_V4, CARD_V5, CARD_V6 };

	switch (msg)
	{
	case WM_COMMAND:
		onButtonClick(hWnd, wParam, images);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE h2, LPSTR cmd, int cmShow)
{
	WNDCLASS wc = { 0 };
	wc.lpszClassName = TEXT("Myclass");
	wc.lpfnWndProc = WndProc;
	RegisterClass(&wc);

	HWND hWnd = CreateWindow(wc.lpszClassName, TEXT("Cardiorgam"),
							 WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 100, 500, 500, 0, 0, hInstance, 0);

	createButtons(hInstance, hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

FileNames Loading()
{
	OPENFILENAME ofn = { 0 };

	char szDirect[260];
	char szFileName[260];

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szDirect;
	*(ofn.lpstrFile) = 0;

	ofn.nMaxFile = sizeof(szDirect);
	ofn.lpstrFilter = NULL;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = szFileName;
	*(ofn.lpstrFileTitle) = 0;

	ofn.nMaxFileTitle = sizeof(szFileName);
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER;

	GetOpenFileName(&ofn);

	FileNames fileNames = { szFileName, szDirect };

	return fileNames;
}

void createButtons(HINSTANCE hInstance, HWND hWnd)
{
#define CREATE_BUTTON(text, x, y, width, height, wParam)								\
CreateWindow(TEXT("button"), TEXT(text),												\
	WS_CHILD | WS_VISIBLE, x, y, width, height, hWnd, (HMENU)wParam, hInstance, 0);

#include "buttons.h"

#undef CREATE_BUTTON
}

void onButtonClick(HWND hWnd, WPARAM wParam, Images& images)
{
	std::string fileName, diagnosis;
	HDC hdc = GetDC(hWnd);

	switch (wParam)
	{
	case CARD_1:  case CARD_2:  case CARD_3:  case CARD_AVR: case CARD_AVL: case CARD_AVF:
	case CARD_V1: case CARD_V2: case CARD_V3: case CARD_V4:  case CARD_V5:  case CARD_V6:

		images[wParam - 1].loadFromFile((fileName = Loading().absFileName));
		TextOut(hdc, 250, (wParam - 1) * 30 + 6, fileName.c_str(), fileName.size());

		break;

	case ANALYZE:

		Cardiogram cardiogram(images);
		diagnosis = cardiogram.analyze();
		TextOut(hdc, 250, 406, diagnosis.c_str(), diagnosis.size());

		break;
	}
}