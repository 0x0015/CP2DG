#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_mouse.h>
#include <unordered_map>

class InputHandler{
public:
	std::unordered_map<SDL_Scancode, bool> keys;
	std::pair<int, int> mousePos;
	std::pair<int, int> mouseScroll;
	std::unordered_map<Uint8, bool> mouse;
	void handleKeyboardEvent(SDL_Event* event);
	bool isKeyPressed(SDL_Scancode key);
	bool isKeyReleased(SDL_Scancode key);
	void handleMouseEvent(SDL_Event* event);
	bool isMouseButtonPressed(Uint8 button);
	bool isMouseButtonReleased(Uint8 button);
};
