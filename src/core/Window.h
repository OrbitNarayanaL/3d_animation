#pragma once

#include <string>

struct GLFWwindow;

class Window
{
public:
    Window();
    ~Window();

    bool Init(int width, int height, const std::string& title);
    bool ShouldClose() const;
    void SwapBuffers();
    void PollEvents();
    void Shutdown();
    GLFWwindow* GetHandle() const { return m_window; }

private:
    GLFWwindow* m_window;
};
