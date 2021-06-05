#include <iostream>
#include <ctime>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

using namespace std;

int main(int argc, char *argv[]) {
  cout << "hi\n";
  
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window = SDL_CreateWindow("hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
  SDL_Renderer *rend = SDL_CreateRenderer(window, -1, 0);
  
  int playerSpeed = 6;
  int p1score = 0;
  int p2score = 0;
  int noClose = 1;
  
  while (noClose) {
    SDL_Rect ra;
    SDL_Rect rb;
    SDL_Rect rc;
    
    ra.x = 40;
    ra.w = 15;
    ra.h = 80;
    
    rb.x = 745;
    rb.w = 15;
    rb.h = 80;
    
    rc.w = 10;
    rc.h = 10;
    
    bool wp = false;
    bool sp = false;
    bool upp = false;
    bool downp = false;
    
    srand(time(0));
    
    int p1 = 375;
    int p2 = 375;
    double x = 395;
    double y = 395;
    double xvel;
    if (rand() < RAND_MAX / 2) {
      xvel = -4;
    } else {
      xvel = 4;
    }
    double yvel = (double) rand() / RAND_MAX * 4 - 2;
    
    
    //main loop
    
    while (noClose) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          noClose = 0;
        }
        
        if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.scancode == SDL_SCANCODE_W) {
            wp = true;
          } else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
            sp = true;
          } else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
            upp = true;
          } else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            downp = true;
          }
        }
        
        if (event.type == SDL_KEYUP) {
          if (event.key.keysym.scancode == SDL_SCANCODE_W) {
            wp = false;
          } else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
            sp = false;
          } else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
            upp = false;
          } else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            downp = false;
          }
        }
      }
      
      if (wp) {p1 -= playerSpeed;}
      if (sp) {p1 += playerSpeed;}
      if (upp) {p2 -= playerSpeed;}
      if (downp) {p2 += playerSpeed;}
      x += xvel;
      y += yvel;
      
      if (y > 790 || y < 0) {yvel *= -1;}
      if (x < 0) {
        //p2 win
        p2score += 1;
        cout << "Score: " + to_string(p1score) + " - " + to_string(p2score) + "\n";
        SDL_Delay(1000);
        break;
      } else if (x > 790) {
        //p1 win
        p1score += 1;
        cout << "Score: " + to_string(p1score) + " - " + to_string(p2score) + "\n";
        SDL_Delay(1000);
        break;
      }
      
      if (x < 55 && x > 30 && y + 10 > p1 && y < p1 + 80) {
        xvel *= -1.1;
        yvel += (p1 + 35 - y) * -0.1;
      }
      
      if (x > 735 && x < 760 && y + 10 > p2 && y < p2 + 80) {
        xvel *= -1.1;
        yvel += (p2 + 35 - y) * -0.07;
      }
      
      ra.y = (int) p1;
      rb.y = (int) p2;
      rc.x = (int) x;
      rc.y = (int) y;
      SDL_SetRenderDrawColor(rend, 240,240,240,255);
      SDL_RenderClear(rend);
      SDL_SetRenderDrawColor(rend, 0,0,0,255);
      
      SDL_RenderFillRect(rend, &ra);
      SDL_RenderFillRect(rend, &rb);
      SDL_RenderFillRect(rend, &rc);
      
      SDL_RenderPresent(rend);
      SDL_Delay(1000/60);
    }
    
  }
  //clean exit
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(window);
  SDL_Quit();
 
  return 0;
}
