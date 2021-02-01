#pragma once

#include "Event.h"

namespace REngine {
    class WindowCloseEvent : public Event {
        virtual EventType GetEventType() {
            return EventType::WindowClose;
        }
    };
}