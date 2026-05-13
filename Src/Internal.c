// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Implementation of game's internal API.
#include "Internal.h"

#define USE_RUNTIME_ENVIRONMENT true

PRIVATE SDL_Environment *env            = NULL;
PRIVATE const char      *physfs_archive = NULL;

PUBLIC
SDL_Environment *Environment(void) {
    SDL_assert(env);

    return env;
}

PRIVATE
bool InitEnvironment(void) {
    env = SDL_CreateEnvironment(USE_RUNTIME_ENVIRONMENT);
    if(!env) {
        return false;
    }

    physfs_archive = SDL_GetEnvironmentVariable(env, GAME_PHYSFS_ARCHIVE_NAME);

    return true;
}

PRIVATE
void QuitEnvironment(void) {
    SDL_DestroyEnvironment(env);
}

PRIVATE
bool InitFontInternal(void) {
    bool status = false;

    status = TTF_Init();
    if(!status) {
        return false;
    }

    return status;
}

PRIVATE
void QuitFontInternal(void) {
    TTF_Quit();
}

PUBLIC
bool InitInternal(mrb_state    *mrb,
                  SDL_Window   *window,
                  SDL_Renderer *renderer,
                  SDL_Event    *event) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT event;
    UNUSED_ARGUMENT window;
    UNUSED_ARGUMENT renderer;

    bool status = false;

    status = InitEnvironment();
    if(!status) {
        return false;
    }

    IGNORE_RETURN InitFileInternal(mrb);

    status = InitFontInternal();
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
void QuitInternal(void) {
    QuitFontInternal();
    QuitFileInternal();
    QuitEnvironment();
}
