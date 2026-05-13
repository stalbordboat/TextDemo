// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Procedures for helping initialize and dispose Image based classes.
#include "Image.h"
#include "Internal.h"

PUBLIC
SDL_Surface *CreateSurfaceForImage(const char *path,
                                   const char *text,
                                   float       ptsize) {
    SDL_Surface  *surface = NULL;
    BufferSize    size    = 0;
    char         *buf     = NULL;
    SDL_IOStream *io      = NULL;
    bool          status  = false;
    TTF_Font     *font    = NULL;
    SDL_Color     fg      = {
                              OPAQUE_COLOR_VALUE,
                              OPAQUE_COLOR_VALUE,
                              OPAQUE_COLOR_VALUE,
                              OPAQUE_COLOR_VALUE
                            };

    buf = GetFileBuffer(path, &size);
    if(!buf) {
        return NULL;
    }

    io = SDL_IOFromMem(buf, size);
    if(!io) {
        FreeBuffer(buf);
        return NULL;
    }

    font = TTF_OpenFontIO(io, false, ptsize);
    if(!font) {
        IGNORE_RETURN SDL_CloseIO(io);
        FreeBuffer(buf);
        return NULL;
    }

    surface = TTF_RenderText_Solid(font, text, 0, fg);
    if(!surface) {
        TTF_CloseFont(font);
        IGNORE_RETURN SDL_CloseIO(io);
        FreeBuffer(buf);
        return NULL;
    }

    TTF_CloseFont(font);

    status = SDL_CloseIO(io);
    if(!status) {
        FreeBuffer(buf);
        return NULL;
    }

    FreeBuffer(buf);

    return surface;
}

PUBLIC
Image *CreateImage(SDL_Surface *surface, SDL_Renderer *renderer) {
    Image *image = NULL;

    image = CallocBuffer(1, sizeof(Image));
    if(!image) {
        return NULL;
    }

    image->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!image->texture) {
        DestroyImage(image);
        return NULL;
    }

    image->blend = SDL_BLENDMODE_BLEND;
    image->flip  = SDL_FLIP_NONE;
    image->angle = 0.0;

    return image;
}

PUBLIC
void DestroyImage(Image *image) {
    if(!image) {
        return;
    }

    if(image->texture) {
        SDL_DestroyTexture(image->texture);
    }

    FreeBuffer(image);
}
