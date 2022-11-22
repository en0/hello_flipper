#pragma once

#include <input/input.h>

#define TAG "Hello"

typedef enum {
    EventTypeKey,
    // Other event types here
} EventType;

typedef struct {
    EventType type;
    InputEvent input;
} PluginEvent;

typedef struct {
    FuriMutex* mutex;
    FuriMessageQueue* event_queue;
    // Other plugin state here
} HelloState;
