#pragma once

#include "Event.h"

namespace REngine {
    class WindowCloseEvent : public Event {
    public:
        virtual EventType GetEventType() override {
            return EventType::WindowClose;
        }

        EVENT_CLASS_TYPE(WindowClose);
    };
}