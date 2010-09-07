
#include <troll.h>

#include "logo_screen.h"
#include "light_grid.h"
#include "lights_app.h"


#ifdef _WIN32

#include <windows.h>
extern "C" int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)

#else

extern "C" int main(int argc, char *argv[])

#endif
{
	LightsApp game;  // App object

	if(!game.Init()) // Initialize, images, sounds, etc.
		return 0;

	game.Run();      // Run game main loop

    return 0;
}

