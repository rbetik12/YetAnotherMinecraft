#pragma once
#include "Event.h"

namespace REngine {
    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : mouseX(x), mouseY(y) {}

        inline float GetX() const { return mouseX; }

        inline float GetY() const { return mouseY; }

        virtual EventType GetEventType() override {
            return EventType::MouseMoved;
        }

        EVENT_CLASS_TYPE(MouseMoved);

    private:
        float mouseX, mouseY;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}

        inline float GetXOffset() const { return xOffset; }

        inline float GetYOffset() const { return yOffset; }

        virtual EventType GetEventType() override {
            return EventType::MouseScrolled;
        }

        EVENT_CLASS_TYPE(MouseScrolled);

    private:
        float xOffset, yOffset;
    };

    class MouseButtonEvent : public Event {
    public:

        inline int GetMouseButton() const { return button; }

    protected:

        MouseButtonEvent(int button) : button(button) {}

        int button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        virtual EventType GetEventType() override {
            return EventType::MouseButtonPressed;
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:

        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        virtual EventType GetEventType() override {
            return EventType::MouseButtonReleased;
        }

        EVENT_CLASS_TYPE(MouseButtonReleased);
    };
}
