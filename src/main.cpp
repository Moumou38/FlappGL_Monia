#include <Screen.hpp>

int main()
{
    int width = 1280, height = 720;
	Screen screen(width, height, "Monia Arrada - FlappGL");
	screen.init();
	screen.run();

	return EXIT_SUCCESS;
}
