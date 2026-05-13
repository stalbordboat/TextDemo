// MIT LICENSE - Copyright (c) 2025 Ralph Desir
// Description: Master Header for the functions implement in the Native API.
#ifndef INTERNAL_H
#define INTERNAL_H

#include "Native/Native.h"
#include <SDL3_ttf/SDL_ttf.h>

// =============================================
// Initialization and Deinitialization Functions
// =============================================

PUBLIC
bool InitInternal(mrb_state    *mrb,
                  SDL_Window   *window,
                  SDL_Renderer *renderer,
                  SDL_Event    *event);

PUBLIC
void QuitInternal(void);

PUBLIC
bool InitFileInternal(mrb_state *mrb);

PUBLIC
void QuitFileInternal(void);

// =================
// General Functions
// =================

PUBLIC
SDL_Environment *Environment(void);

// The following are defined in Src/InternalFile.c.

PUBLIC
bool GetMountStatus(void);

PUBLIC
Buffer *GetFileBuffer(const char *path, BufferSize *get_size);

// ================
// Window Subsystem
// ================

PUBLIC
void DefineTextClass(mrb_state *mrb, SDL_Renderer *renderer);

#endif /*INTERNAL_H*/
