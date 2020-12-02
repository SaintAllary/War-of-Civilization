#include "WindowManager.h"

int main(void) {
	std::srand(static_cast<unsigned int>(time(NULL)));
	WindowManager WM;
	WM.mainMenu(WM.getWindow());

	return WN_SUCCESS;
}