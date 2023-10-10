#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <vector>

#include "ImGui/imgui.h"
#include "ImGui/imgui_sdl.h"
#include "ImGui/imgui_impl_sdl.h"

#include "src/debugDrawer.h"
#include "src/gameEngine.h"
#include "src/ImGuiManager.h"
#include "src/sprite.h"
#include "src/spriteSheet.h"
#include "src/textSprite.h"
#include "src/vector2.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(1);

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	debugDrawer = std::make_shared<DebugDrawer>();
	imGuiHandler = std::make_shared<ImGuiHandler>();


	imGuiHandler->Init();

	Uint64 previous_ticks = SDL_GetPerformanceCounter();
	bool running = true;
	while (running) {
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		frameNumber++;
		const Uint64 ticks = SDL_GetPerformanceCounter();
		const Uint64 delta_ticks = ticks - previous_ticks;
		previous_ticks = ticks;
		deltaTime = (float)delta_ticks / (float)SDL_GetPerformanceFrequency();


		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			switch (event.type) {
				case SDL_QUIT: {
					running = false;
					break;
				}
				case SDL_KEYDOWN: {
					if (event.key.repeat) {
						break;
					}
					const int scancode = event.key.keysym.scancode;
					if (scancode == SDL_SCANCODE_ESCAPE) {
						running = false;
					}
					keys[scancode].state = true;
					keys[scancode].changeFrame = frameNumber;
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 125, 0, 255);
		SDL_RenderClear(renderer);

		//Render here

		debugDrawer->DrawBoxes();
		debugDrawer->DrawCircles();
		debugDrawer->DrawLines();

		imGuiHandler->Render();

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	imGuiHandler->ShutDown();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}