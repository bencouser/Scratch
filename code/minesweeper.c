#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <stdbool.h>
#include <stdio.h>

// Screen dimensions
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;

// Image dimensions
const int IMAGE_WIDTH = 32;
const int IMAGE_HEIGHT = 32;

bool initialize(SDL_Window **win, SDL_Renderer **renderer) {
  // Initialize SDL
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return false;
  }

  // Initialize SDL_image
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    printf("IMG_Init Error: %s\n", IMG_GetError());
    SDL_Quit();
    return false;
  }

  // Create window
  *win = SDL_CreateWindow("Scratch", SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                          SDL_WINDOW_SHOWN);
  if (*win == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    return false;
  }

  // Create renderer
  *renderer = SDL_CreateRenderer(
      *win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (*renderer == NULL) {
    SDL_DestroyWindow(*win);
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    return false;
  }

  return true;
}

SDL_Texture *loadTexture(const char *filePath, SDL_Renderer *renderer) {
  // Load the image
  SDL_Surface *image = IMG_Load(filePath);
  if (image == NULL) {
    printf("IMG_Load Error: %s\n", IMG_GetError());
    return NULL;
  }

  // Create a texture from the surface
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if (texture == NULL) {
    printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    return NULL;
  }

  return texture;
}

void render_window(SDL_Renderer *renderer, int x_pos, int y_pos,
                   SDL_Texture *texture) {
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

void calculateFPS(Uint32 *startTime, int *frameCount) {
  (*frameCount)++;
  if (*frameCount == 60) {
    Uint32 timeElapsed = SDL_GetTicks() - *startTime;
    float fps = *frameCount / (timeElapsed / 1000.0f);
    printf("FPS: %.2f\n", fps);
    *frameCount = 0;
    *startTime = SDL_GetTicks();
  }
}

void cleanUp(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Window *win) {
  // Cleanup
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  IMG_Quit();
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  // SDL Init
  SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;

  if (!initialize(&win, &renderer)) {
    return 1;
  }

  // Load texture
  SDL_Texture *texture =
      loadTexture("../data/MineSweeper/images/Unclicked.png", renderer);
  if (texture == NULL) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 1;
  }

  // Image position
  float x_pos = 0;
  float y_pos = 0;

  // Get the starting time
  Uint32 startTime = SDL_GetTicks();
  Uint32 lastTime = startTime;
  int frameCount = 0;

  // Main loop flag
  int running = 1;

  // Event handler
  SDL_Event e;

  while (running) {
    while (SDL_PollEvent(&e) != 0) {
      // Calculate elapsed time in seconds
      // User requests quit
      if (e.type == SDL_QUIT) {
        running = 0;
      }
    }
    Uint32 currentTime = SDL_GetTicks();
    float elapsedTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    render_window(renderer, x_pos, y_pos, texture);
    calculateFPS(&startTime, &frameCount);
  }

  cleanUp(texture, renderer, win);
  return 0;
}
