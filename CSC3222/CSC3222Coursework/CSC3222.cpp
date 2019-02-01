#include "../../Common/Window.h"
#include "RobotRescueGame.h"

#include "../../Common/Vector3.h"

using namespace NCL;
using namespace CSC3222;

int main() {
	Window*w = Window::CreateGameWindow("CSC3222 - Robot Rescue!", 1120, 768);

	if (!w->HasInitialised()) {
		return -1;
	}

	RobotRescueGame* robotGame = new RobotRescueGame();

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();

		robotGame->Update(time / 1000.0f);

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}

		w->SetTitle(std::to_string(time));
	}

	delete robotGame;

	Window::DestroyGameWindow();
}