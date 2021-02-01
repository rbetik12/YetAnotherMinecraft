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
    public:
        virtual EventType GetEventType() = 0;
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }


    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) : event(event) {}

        template<typename T>
        bool Dispatch(EventFn<T> func) {
            if (event.GetEventType() == T::GetStaticType()) {
                func(*(T*)&event);
            }
            return false;
        }

    private:
        Event& event;
    };
}
