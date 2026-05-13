// MIT LICENSE - Copyright (c) 2025 Ralph Desir
// Description: Native Entry Point
#include "Internal.h"

#define WINDOW_ENABLED(env) !SDL_GetEnvironmentVariable(env, GAME_NO_WINDOW_NAME)

PUBLIC
bool NativeEntryPoint(mrb_state *mrb, SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event) {
    bool             initialized = false;
    SDL_Environment *env         = NULL;

    initialized = InitInternal(mrb, window, renderer, event);
    if(initialized) {
        env = Environment();

        if(WINDOW_ENABLED(env)) {
            DefineTextClass(mrb, renderer);
        }
    }

    return true;
}

PUBLIC
void NativeExitPoint(mrb_state *mrb) {
    UNUSED_ARGUMENT mrb;

    QuitInternal();
}
