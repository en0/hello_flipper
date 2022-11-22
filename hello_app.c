#include <furi.h>
#include <furi_hal.h>

#include <gui/gui.h>
#include <gui/elements.h>

#include "hello_app.h"

static void hello_input_callback(InputEvent* input_event, FuriMessageQueue* event_queue) {
    furi_assert(event_queue);
    PluginEvent event = {.type = EventTypeKey, .input = *input_event};
    furi_message_queue_put(event_queue, &event, FuriWaitForever);
}

static void hello_render_callback(Canvas* const canvas, void* ctx) {
    UNUSED(ctx);
    canvas_draw_str_aligned(canvas, 64, 20, AlignCenter, AlignTop, "Hello, World!");
}

int32_t hello_app(void* p) {
    UNUSED(p);
    HelloState* plugin_state = malloc(sizeof(HelloState));

    plugin_state->event_queue = furi_message_queue_alloc(8, sizeof(PluginEvent));
    if(plugin_state->event_queue == NULL) {
        FURI_LOG_E(TAG, "Cannot create event queue");
        free(plugin_state);
        return 255;
    }

    plugin_state->mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    if(plugin_state->mutex == NULL) {
        FURI_LOG_E(TAG, "Cannot create mutex");
        furi_message_queue_free(plugin_state->event_queue);
        free(plugin_state);
        return 255;
    }

    // Set system callbacks
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, hello_render_callback, plugin_state);
    view_port_input_callback_set(view_port, hello_input_callback, plugin_state->event_queue);

    // Open GUI and register view_port
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);


    // Main loop
    PluginEvent event;
    for(bool processing = true; processing;) {
        FuriStatus event_status = furi_message_queue_get(plugin_state->event_queue, &event, 100);

        if(event_status != FuriStatusOk) continue;

        if(furi_mutex_acquire(plugin_state->mutex, FuriWaitForever) != FuriStatusOk) continue;
        // press events
        if(event.type == EventTypeKey) {
            if(event.input.type == InputTypeShort || event.input.type == InputTypeRepeat) {
                switch(event.input.key) {
                case InputKeyUp:
                case InputKeyDown:
                case InputKeyRight:
                case InputKeyLeft:
                case InputKeyOk:;
                    break;
                case InputKeyBack:
                    // Exit the plugin
                    processing = false;
                    break;
                default:
                    break;
                }
            }
        }

        view_port_update(view_port);
        furi_mutex_release(plugin_state->mutex);
    }

    // Clean up resources
    view_port_enabled_set(view_port, false);
    gui_remove_view_port(gui, view_port);
    furi_record_close(RECORD_GUI);
    view_port_free(view_port);
    furi_message_queue_free(plugin_state->event_queue);
    furi_mutex_free(plugin_state->mutex);
    free(plugin_state);

    return 0;
}
