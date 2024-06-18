#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Image dimension constants
const int IMAGE_WIDTH = 100;
const int IMAGE_HEIGHT = 100;

int main(int argc, char *argv[]) {
  // Initialize
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    printf("IMG_Init Error: %s\n", IMG_GetError());
    SDL_Quit();
    return 1;
  }

  // Create Window
  SDL_Window *win = SDL_CreateWindow("Hello, Window!", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                     SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  // Catch Window Error
  if (win == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    SDL_DestroyWindow(win);
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    return 1;
  }

  // Load the image
  SDL_Surface *image = IMG_Load("../data/box.png");
  if (image == NULL) {
    printf("IMG_Load Error: %s\n", IMG_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 1;
  }

  // Create a texture from the surface
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (texture == NULL) {
    printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 1;
  }

  // Image position and velocity
  float x_pos = 0;
  float y_pos = (SCREEN_HEIGHT - IMAGE_HEIGHT) / 2;
  float x_vel = 5; // pixels per frame

  // Main loop flag
  int running = 1;

  // Event handler
  SDL_Event e;
  // While application is running
  while (running) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        running = 0;
      }
    }

    // Update position
    x_pos += x_vel;
    if (x_pos > SCREEN_WIDTH) {
      x_pos = -IMAGE_WIDTH; // Reset position to start from left again
    }

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xC0, 0xCB, 0xFF);
    SDL_RenderClear(renderer);

    // Define the destination rectangle for rendering the image
    SDL_Rect destRect = {(int)x_pos, (int)y_pos, IMAGE_WIDTH, IMAGE_HEIGHT};

    // Render texture to screen
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    // Update screen
    SDL_RenderPresent(renderer);
  }

  // Cleanup
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  IMG_Quit();
  SDL_Quit();

  return 0;
}
