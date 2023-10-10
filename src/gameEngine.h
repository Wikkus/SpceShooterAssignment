#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_scancode.h>

#include <random>
#include <vector>

#define PI 3.14159265358979
#define eulersNumber 2.71828

class DebugDrawer;
class ImGuiHandler;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern std::shared_ptr<DebugDrawer> debugDrawer;
extern std::shared_ptr<ImGuiHandler> imGuiHandler;

extern float windowHeight;
extern float windowWidth;

struct KeyState {
	bool state = false;
	int changeFrame = 0;
};

extern KeyState keys[SDL_NUM_SCANCODES];
extern bool GetKey(SDL_Scancode key);
extern bool GetKeyPressed(SDL_Scancode key);
extern bool GetKeyReleased(SDL_Scancode key);

void DrawText(SDL_Texture* textTexture, SDL_Rect* textSrcrect, SDL_Rect textDst);
void ClearText(SDL_Surface* textSurface, SDL_Texture* textTexture);


extern float deltaTime;
extern int frameNumber;

extern std::random_device randomDevice;
extern std::mt19937 randomEngine;