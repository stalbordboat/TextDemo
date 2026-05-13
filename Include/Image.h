// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: 
#ifndef IMAGE_H
#define IMAGE_H

#include "Native/Common.h"

#define OPAQUE_COLOR_VALUE    255
#define TOP_LEFT_CENTER_VALUE 0.0

typedef struct {
    double       angle;
    SDL_Texture *texture;
    int          flip;
    int          blend;
}Image;

PUBLIC
SDL_Surface *CreateSurfaceForImage(const char *path, const char *text, float ptsize);

PUBLIC
Image *CreateImage(SDL_Surface *surface, SDL_Renderer *renderer);

PUBLIC
void DestroyImage(Image *image);

#endif // IMAGE_H
