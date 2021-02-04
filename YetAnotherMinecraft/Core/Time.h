#pragma once
namespace REngine {
    class Time {
    public:
        static float deltaTime;

        static void OnUpdate();
    private:
        static float lastFrame;
        static float currentFrame;
    };
}