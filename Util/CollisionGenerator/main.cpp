#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "openFile.hpp"
#include "reportError.hpp"
#include "SimpleCppTextFileHandler/file.hpp"
#include "json.hpp"

using json = nlohmann::json;

void exportJsonPoints(std::vector<std::pair<float, float>>& points, std::string filename){
	std::string output = "[\n";
	for(int i=0;i<points.size();i++){
		output.append("[" + std::to_string(points[i].first) + ", " + std::to_string(points[i].second) + "]");
		if(i+1 < points.size()){
			output.append(",");
		}
		output.append("\n");
	}
	output.append("]");
	writeFile(filename, output);
}

void importJsonPoints(std::vector<std::pair<float, float>>* points, std::string filename){
	points->clear();
	std::string text = readFile(filename);
	auto j = json::parse(text);
	for(int i=0;i<j.size();i++){
		std::pair<float, float> point;
		if(j[i].size() == 2){
			point.first = j[i][0].get<float>();
			point.second = j[i][1].get<float>();
		}
		(*points).push_back(point);
	}
}

void openImage(std::vector<std::pair<float, float>>* points){
	std::string maskName = openFile();
	//SDL_FreeSurface(*mask);
	//*mask =  IMG_Load(maskName.c_str());
	importJsonPoints(points, maskName);
}
void saveImage(std::vector<std::pair<float, float>>& points, std::string imageName){
	std::string actualFilename = saveFile(imageName);
	//SDL_SaveBMP(mask, actualFilename.c_str());
	exportJsonPoints(points, actualFilename);
}


int main()
{
	std::string imageName = openFile();
	
	if(imageName == ""){
		std::cout<<"Please select an image and try again."<<std::endl;
		tinyfd_messageBox("Warning", "Please select an image and try again.", "ok", "warning" , 1);
		return(-1);
	}else{
		std::cout<<"Opening image "<<imageName<<std::endl;
	}
	
	SDL_SetMainReady();
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library"<<std::endl;
	reportError("Failed to initialize the SDL2 library");
        return -1;
    }
    IMG_Init(IMG_INIT_PNG);

	SDL_Window *window = SDL_CreateWindow("SDL2 Window1",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          680, 480,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!window)
    {
        std::cout << "Failed to create window\n";
	reportError("Failed to create window");
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1 ,0);
	
    if(!renderer){
	    std::cout<< "Failed to create renderer" <<std::endl;
	    reportError("Failed to create renderer");
	    return(-1);
    }
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_Surface* Image = IMG_Load(imageName.c_str());

    if(!Image){
	    std::cout<<"Failed to load image"<<std::endl;
	    reportError("Failed to load image");
	    return(-1);
    }

    SDL_Texture* ImageTex = SDL_CreateTextureFromSurface(renderer, Image);

    if(!ImageTex){
	    std::cout<<"Failed to create texture from image"<<std::endl;
	    reportError("Failed to create texture from image");
	    return(-1);
    }

    
    int imageMultiplier = 1;

    std::cout<<"Image size is "<<Image->w<<" x "<<Image->h<<std::endl;

    SDL_SetWindowSize(window, Image->w * imageMultiplier, Image->h * imageMultiplier);
    
    std::vector<std::pair<float, float>> collisionPoints;

    bool mouseLDown = false;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    bool quit = false;

    int fillAmount = 30;

	SDL_Event event;
    while(!quit){
	while (SDL_PollEvent(&event))
	{
		//std::cout<<"Polling event"<<std::endl;
	    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
	    {
	        quit = true;
	    }else if(event.type == SDL_MOUSEWHEEL){
		if(event.wheel.y > 0){
			imageMultiplier++;
			//SDL_SetWindowSize(window, Image->w * imageMultiplier, Image->h * imageMultiplier);
		}else if(event.wheel.y < 0){
			imageMultiplier--;
			if(imageMultiplier < 1){
				imageMultiplier = 1;
			}
			//SDL_SetWindowSize(window, Image->w * imageMultiplier, Image->h * imageMultiplier);
		}
	    }
	}
	
	const Uint8* kb = SDL_GetKeyboardState(NULL);

	if(kb[SDL_SCANCODE_O]){
		//to open mask file;
		openImage(&collisionPoints);
	}
	if(kb[SDL_SCANCODE_S]){
		//to save mask file;
		saveImage(collisionPoints, imageName);
	}
	if(kb[SDL_SCANCODE_ESCAPE]){
		quit = true;
	}
	
	int mouseX;
	int mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	
	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
		if(!mouseLDown){
		std::pair<float, float> clickPoint = std::pair<float, float>((float)mouseX/(float)Image->w, (float)mouseY/(float)Image->h);
		collisionPoints.push_back(clickPoint);
		}
		mouseLDown = true;
	}else{
		mouseLDown = false;
	}

	if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)){
		std::pair<float, float> clickPoint = std::pair<float, float>((float)mouseX/(float)Image->w, (float)mouseY/(float)Image->h);
		for(int i=0;i<collisionPoints.size();i++){
			if(sqrt(((collisionPoints[i].first - clickPoint.first)*(collisionPoints[i].first - clickPoint.first))+( (collisionPoints[i].second - clickPoint.second)* (collisionPoints[i].second - clickPoint.second))) <=  imageMultiplier){
				collisionPoints.erase(collisionPoints.begin() + i);
				break;
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);
	

	SDL_RenderCopy(renderer, ImageTex, NULL, NULL);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);

	for(int i=0;i<collisionPoints.size();i++){
		SDL_RenderDrawLine(renderer, collisionPoints[i].first * Image->w, 0, collisionPoints[i].first * Image->w, Image->h);
		SDL_RenderDrawLine(renderer, 0, collisionPoints[i].second * Image->h, Image->w, collisionPoints[i].second * Image->h);

	}
	
	
	SDL_RenderPresent(renderer);

    }


    SDL_FreeSurface(Image);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return(0);
}
