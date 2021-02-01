#pragma once
#include "Event.h"

namespace REngine {

    class KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return keyCode; }

    protected:
        KeyEvent(int keycode)
            : keyCode(keycode) {}

        int keyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), repeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return repeatCount; }

        virtual EventType GetEventType() override {
            return EventType::KeyPressed;
        }

        EVENT_CLASS_TYPE(KeyPressed);

    private:
        int repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        virtual EventType GetEventType() override {
            return EventType::KeyReleased;
        }

        EVENT_CLASS_TYPE(KeyReleased);
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(int keycode)
            : KeyEvent(keycode) {}

        virtual EventType GetEventType() override {
            return EventType::KeyTyped;
        }

        EVENT_CLASS_TYPE(KeyTyped);
    };
}
