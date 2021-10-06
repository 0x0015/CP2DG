#include "InputHandler.hpp"

void InputHandler::handleKeyboardEvent(SDL_Event* event){
	if(event->type != SDL_KEYDOWN && event->type != SDL_KEYUP){
		return;
	}
	keys[event->key.keysym.scancode] = (event->key.state == SDL_PRESSED);
}

bool InputHandler::isKeyPressed(SDL_Scancode key){
	if(keys.contains(key)){
		return(keys[key]);
	}else{
		return(false);
	}
}

bool InputHandler::isKeyReleased(SDL_Scancode key){
	if(keys.contains(key)){
		return(!keys[key]);
	}else{
		return(true);
	}
}

void InputHandler::handleMouseEvent(SDL_Event* event){
	if(event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEBUTTONDOWN){
		mouse[event->button.button] = (event->button.state == SDL_PRESSED);
		mousePos.first = event->button.x;
		mousePos.second = event->button.y;
	}
	if(event->type == SDL_MOUSEMOTION){
		mousePos.first = event->motion.x;
		mousePos.second = event->motion.y;
	}
	if(event->type == SDL_MOUSEWHEEL){
		if(event->wheel.direction == SDL_MOUSEWHEEL_NORMAL){
			mouseScroll.first = event->wheel.x;
			mouseScroll.second = event->wheel.y;
		}else if(event->wheel.direction == SDL_MOUSEWHEEL_FLIPPED){
			mouseScroll.first = event->wheel.x * -1;
			mouseScroll.second = event->wheel.y * -1;
		}
	}
}

bool InputHandler::isMouseButtonPressed(Uint8 button){
	if(mouse.contains(button)){
		return(mouse[button]);
	}else{
		return(false);
	}
}

bool InputHandler::isMouseButtonReleased(Uint8 button){
	if(mouse.contains(button)){
		return(!mouse[button]);
	}else{
		return(true);
	}
}


