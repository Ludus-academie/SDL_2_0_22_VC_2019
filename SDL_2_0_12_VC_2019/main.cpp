
#include <stdio.h>
#include <stdlib.h>
#include "SDL_Manager.h"

void DrawFilledSquare(SDL_Renderer* pRenderer, SDL_Rect* rect, Uint8 colorR, Uint8 colorG, Uint8 colorB, Uint8 colorA);
void DrawFilledSquare(SDL_Renderer* pRenderer, SDL_Surface* pSurface, SDL_Rect* rect, Uint8 colorR, Uint8 colorG, Uint8 colorB);
void DrawSquare(SDL_Renderer* pRenderer, SDL_Rect* pRect);
void DrawCircle(SDL_Renderer* pRenderer, int origin_x, int origin_y, int radius);
void DrawFilledCircle(SDL_Renderer* pRenderer, int origin_x, int origin_y, int radius);
void DrawBmp(char* cBmpPatch, SDL_Renderer* pRenderer, SDL_Surface* pSurface, SDL_Texture* pTexture);


int main(int argc, char** argv)
{
    printf_s("Compteur d'argument : %d\n", argc);
    printf_s("Argument %s", argv[0]);
   
    //Init SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    }
    
    sdl_manager *pSdl=(sdl_manager*)malloc(sizeof(sdl_manager));
    
    //Init SDL_Manager
    int nSdlMangagerInitValue= SDL_Manager_INIT(pSdl);

    SDL_Rect rect = { 500,300,200,200 };
    SDL_Rect rect2 = { 0,0,200,200 };
    SDL_Rect rect3 = { 575,375,50,50 };
    

    if (pSdl) {
        SDL_SetRenderDrawColor(pSdl->pRenderer, 255, 0, 0, 0);

        SDL_RenderClear(pSdl->pRenderer);

        DrawFilledSquare(pSdl->pRenderer, &rect, 0, 255, 0, 0);

        DrawFilledSquare(pSdl->pRenderer, pSdl->pSurface, &rect2, 0, 0, 255);

        SDL_SetRenderDrawColor(pSdl->pRenderer, 0, 0, 0, 0);

        DrawSquare(pSdl->pRenderer, &rect3);

        SDL_SetRenderDrawColor(pSdl->pRenderer, 255, 255, 255, 255);

        DrawCircle(pSdl->pRenderer, 900, 400, 100);

        DrawFilledCircle(pSdl->pRenderer, 200, 200, 100);

        char path[255]="./assets/rider.bmp";


        DrawBmp(path, pSdl->pRenderer, pSdl->pSurface, pSdl->pTexture);





        SDL_RenderPresent(pSdl->pRenderer);
    }
    else {

        exit(EXIT_FAILURE);
    }

    SDL_Delay(3000);

    SDL_Manager_FREE(pSdl);

    free(pSdl);

    SDL_Quit();

    return 0;
}

//Draw renderer
void DrawFilledSquare(SDL_Renderer* pRenderer, SDL_Rect* pRect, Uint8 colorR, Uint8 colorG, Uint8 colorB, Uint8 colorA)
{
    SDL_SetRenderDrawColor(pRenderer, colorR, colorG,colorB, colorA);
    SDL_RenderFillRect(pRenderer, pRect);
    
}

//Draw texture to renderer
void DrawFilledSquare(SDL_Renderer* pRenderer,SDL_Surface *pSurface, SDL_Rect* pRect, Uint8 colorR, Uint8 colorG, Uint8 colorB)
{
    
    SDL_Texture* pTexture = nullptr;
    
    SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, colorR, colorG,colorB));

    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);

    SDL_RenderCopy(pRenderer, pTexture, NULL, pRect);

    SDL_DestroyTexture(pTexture);

}
//Draw to renderer
void DrawSquare(SDL_Renderer *pRenderer,SDL_Rect *pRect) {

     SDL_RenderDrawRect(pRenderer, pRect);
}

//Draw circle to renderer
void DrawCircle(SDL_Renderer* pRenderer, int origin_x, int origin_y, int radius)
{
    int new_x = 0;
    int new_y = 0;
    int old_x = origin_x + radius;
    int old_y = origin_y;
    double step = (M_PI * 2) / 50;


    for (double theta = 0; theta <= (M_PI * 2); theta += step) {
        new_x = int(origin_x + (radius * cos(theta)));
        new_y = int(origin_y - (radius * sin(theta)));

        SDL_RenderDrawLine(pRenderer, old_x, old_y, new_x, new_y);
       

        old_x = new_x;
        old_y = new_y;
    }

    new_x = origin_x + radius;
    new_y = origin_y;
    SDL_RenderDrawLine(pRenderer, old_x, old_y, new_x, new_y);
   
    
}

//Draw filled circle to renderer
void DrawFilledCircle(SDL_Renderer* pRenderer, int origin_x, int origin_y, int radius)
{
    for (int dy = 1; dy <= radius; dy++) {

        int dx = int(floor(sqrt((2 * radius * dy) - (dy * dy))));

        SDL_RenderDrawLine(pRenderer, origin_x - dx, origin_y + dy - radius, origin_x + dx, origin_y + dy - radius);
        SDL_RenderDrawLine(pRenderer, origin_x - dx, origin_y - dy + radius, origin_x + dx, origin_y - dy + radius);

    }
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
}

void DrawBmp(char* cBmpPatch, SDL_Renderer* pRenderer, SDL_Surface* pSurface, SDL_Texture* pTexture) {

    pSurface = SDL_LoadBMP(cBmpPatch);
    int nHeight=pSurface->h;
    int nWidth = pSurface->w;

    if (!pSurface) {
        printf_s("Failed to load image at %s: %s\n", cBmpPatch, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);

    SDL_Rect rectDest = {5, 5, nWidth, nHeight };
    SDL_RenderCopy(pRenderer, pTexture, NULL, &rectDest);


}