#include "Engine/Core/CoreEngine.h"
#include"Game/Game1.h"

Window* window;

int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new Game1);

	if (!CoreEngine::GetInstance()->OnCreate("Game", 500, 500)) {
	
		return 1;
	}
	CoreEngine::GetInstance()->Run();

	
	return 0;
}