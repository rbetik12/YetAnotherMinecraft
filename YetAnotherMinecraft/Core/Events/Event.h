#pragma once

#include <string>
#include <functional>

namespace REngine {

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    class Event {

        virtual EventType GetEventType() = 0;
    };

    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) : event(event) {}

        template<typename T>
        bool Dispatch(EventFn<T> func) {
            func(*(T*)&event);
            return false;
        }

    private:
        Event& event;
    };
}
