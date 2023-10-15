#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <windows.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_sdl.h"
#include "ImGui/imgui_impl_sdl.h"

#include "src/debugDrawer.h"
#include "src/enemyManager.h"
#include "src/gameEngine.h"
#include "src/ImGuiManager.h"
#include "src/lesserEnemy.h"
#include "src/playerCharacter.h"
#include "src/projectileManager.h"
#include "src/sprite.h"
#include "src/spriteSheet.h"
#include "src/textSprite.h"
#include "src/vector2.h"

int main(int argc, char* argv[]) {
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(1);

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	enemyManager = new EnemyManager();
	debugDrawer = std::make_shared<DebugDrawer>();
	imGuiHandler = std::make_shared<ImGuiHandler>();
	projectileManager = new ProjectileManager();
	playerCharacter = new PlayerCharacter("res/sprites/CoralineDadKing.png", 
		0.f, Vector2<float>(windowWidth * 0.5f, windowHeight * 0.5f));

	imGuiHandler->Init();
	projectileManager->Init();
	enemyManager->Init();

	enemyManager->CreateEnemy(EnemyType::LesserEnemy, new LesserEnemy("res/sprites/CoralineDadFigher.png", 0.f, Vector2<float>(300.f, 300.f)));

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


		SDL_Event eventType;
		while (SDL_PollEvent(&eventType)) {
			ImGui_ImplSDL2_ProcessEvent(&eventType);
			switch (eventType.type) {
				case SDL_QUIT: {
					running = false;
					break;
				}
				case SDL_KEYDOWN: {
					const int scanCode = eventType.key.keysym.scancode;
					if (eventType.key.repeat) {
						break;
					}
					if (scanCode == SDL_SCANCODE_ESCAPE) {
						running = false;
					}
			
					keys[scanCode].changeFrame = frameNumber;
					keys[scanCode].state = true;
					break;
				}
				case SDL_KEYUP: {
					const int scanCode = eventType.key.keysym.scancode;
					keys[scanCode].changeFrame = frameNumber;
					keys[scanCode].state = false;
					break;
				}
				case SDL_MOUSEBUTTONDOWN: {
					if (eventType.key.repeat) {
						break;
					}
					mouseButtons[eventType.button.button].changeFrame = frameNumber;
					mouseButtons[eventType.button.button].state = true;
					break;
				}
				case SDL_MOUSEBUTTONUP: {
					mouseButtons[eventType.button.button].changeFrame = frameNumber;
					mouseButtons[eventType.button.button].state = false;
				}
			}
		}
		enemyManager->Update();
		playerCharacter->Update();
		projectileManager->Update();

		SDL_SetRenderDrawColor(renderer, 0, 125, 0, 255);
		SDL_RenderClear(renderer);

		//Render here
		enemyManager->Render();
		playerCharacter->Render();
		projectileManager->Render();
		
		debugDrawer->DrawBoxes();
		debugDrawer->DrawCircles();
		debugDrawer->DrawLines();

		imGuiHandler->Render();

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	playerCharacter = nullptr;
	delete playerCharacter;

	projectileManager = nullptr;
	delete projectileManager;
	
	imGuiHandler->ShutDown();
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::exit(0);
	
	return 0;
}