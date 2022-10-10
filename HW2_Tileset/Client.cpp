#include "Editor.h"

int main()
{
	// Aspect ratio is ugly, but it's for the level...
	Editor editor("Tileset Editor", 1280, 768);

	// Load a default empty level if the user hasn't loaded.
	editor.makeLevel(20, 12, 64, "Assets/Platformer-70x70.png", 70);

	editor.setStep(17);
	editor.setPath("Saved/Level.txt");

	// START THE ENGINE!
	editor.start();

	return 0;
}
