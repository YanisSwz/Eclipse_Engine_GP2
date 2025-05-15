#include "GLFWWindow.hpp"
#include "GLFWInputs.inl"
#include "Logger.inl"

namespace Windowing
{
    float GLFWWindow::s_mouseScrollDelta = 0.f;
    bool GLFWWindow::s_mouseScrollDeltaReset = false;

    void GLFWWindow::CreateWindow(const char* _name, int _width, int _height)
    {
        name = _name;
        width = _width;
        height = _height;

        if (!glfwInit())
        {
            return;
        }

        // GLFW Hints Setup
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

        m_window = glfwCreateWindow(width, height, name, NULL, NULL);
        glfwSetWindowSizeLimits(m_window, 800, 400, GLFW_DONT_CARE, GLFW_DONT_CARE);

        if (m_window == nullptr)
        {
            return;
        }

        glfwMakeContextCurrent(m_window);

        // Set mouse scroll callback
        glfwSetScrollCallback(m_window, scroll_callback);
        glfwGetWindowSize(m_window, &width, &height);
    }

    void GLFWWindow::SetIcon(int _width, int _height, unsigned char* _pixels)
    {
        GLFWimage logo;
        logo.width = 800;
        logo.height = 800;
        logo.pixels = _pixels;
        glfwSetWindowIcon(m_window, 1, &logo);
    }

    float GLFWWindow::GetTime()
    {
        return static_cast<float>(glfwGetTime());
    }

    bool GLFWWindow::WindowShouldClose()
    {
        return glfwWindowShouldClose(m_window);
    }

    void GLFWWindow::SetWindowShouldClose(bool _bShouldClose)
    {
        glfwSetWindowShouldClose(m_window, _bShouldClose);
    }

    void GLFWWindow::SwapBuffers()
    {
        glfwSwapBuffers(m_window);
    }

    void GLFWWindow::PollEvents()
    {
        glfwPollEvents();
    }

    void GLFWWindow::DestroyWindow()
    {
        if (m_window == nullptr)
            return;

        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void GLFWWindow::UpdateInputs()
    {
        if (s_mouseScrollDelta != 0.f && !s_mouseScrollDeltaReset)
        {
            s_mouseScrollDeltaReset = true;
        }
        else if (s_mouseScrollDelta != 0.f && s_mouseScrollDeltaReset)
        {
            s_mouseScrollDeltaReset = false;
            s_mouseScrollDelta = 0.f;
        }

        std::map<KEY_CODE, INPUT_ACTION>::iterator it;
        for (it = m_keys.begin(); it != m_keys.end(); it++)
        {
            int action = glfwGetKey(m_window, CastGlfwKeyCode(it->first));
            if (action == GLFW_PRESS)
            {
                if (it->second == INPUT_ACTION::INPUT_PRESS || it->second == INPUT_ACTION::INPUT_DOWN)
                    it->second = INPUT_ACTION::INPUT_DOWN;
                else
                    it->second = INPUT_ACTION::INPUT_PRESS;
            }
            else if (action == GLFW_RELEASE)
            {
                if (it->second == INPUT_ACTION::INPUT_RELEASE || it->second == INPUT_ACTION::INPUT_UP)
                    it->second = INPUT_ACTION::INPUT_UP;
                else
                    it->second = INPUT_ACTION::INPUT_RELEASE;
            }
        }

        std::map<MOUSE_CODE, INPUT_ACTION>::iterator it2;
        for (it2 = m_mouseButtons.begin(); it2 != m_mouseButtons.end(); it2++)
        {
            int action = glfwGetMouseButton(m_window, CastGlfwMouseCode(it2->first));
            if (action == GLFW_PRESS)
            {
                if (it2->second == INPUT_ACTION::INPUT_PRESS || it2->second == INPUT_ACTION::INPUT_DOWN)
                    it2->second = INPUT_ACTION::INPUT_DOWN;
                else
                    it2->second = INPUT_ACTION::INPUT_PRESS;
            }
            else if (action == GLFW_RELEASE)
            {
                if (it2->second == INPUT_ACTION::INPUT_RELEASE || it2->second == INPUT_ACTION::INPUT_UP)
                    it2->second = INPUT_ACTION::INPUT_UP;
                else
                    it2->second = INPUT_ACTION::INPUT_RELEASE;
            }
        }
    }

    bool GLFWWindow::GetKey(KEY_CODE _code, INPUT_ACTION _action)
    {
        if (_action == INPUT_ACTION::INPUT_UP)
            return m_keys[_code] == _action || m_keys[_code] == INPUT_ACTION::INPUT_RELEASE;
        else if (_action == INPUT_ACTION::INPUT_DOWN)
            return m_keys[_code] == _action || m_keys[_code] == INPUT_ACTION::INPUT_PRESS;
        return m_keys[_code] == _action;
    }

    bool GLFWWindow::GetMouseButton(MOUSE_CODE _code, INPUT_ACTION _action)
    {
        if (_action == INPUT_ACTION::INPUT_UP)
            return m_mouseButtons[_code] == _action || m_mouseButtons[_code] == INPUT_ACTION::INPUT_RELEASE;
        else if (_action == INPUT_ACTION::INPUT_DOWN)
            return m_mouseButtons[_code] == _action || m_mouseButtons[_code] == INPUT_ACTION::INPUT_PRESS;
        return m_mouseButtons[_code] == _action;
    }

    Math::Vec2 GLFWWindow::GetCursorPos()
    {
        double x, y;
        glfwGetCursorPos(m_window, &x, &y);
        return Math::Vec2(static_cast<float>(x), static_cast<float>(y));
    }

    void GLFWWindow::SetCursorPos(Math::Vec2 _pos)
    {
        glfwSetCursorPos(m_window, static_cast<double>(_pos.x), static_cast<double>(_pos.y));
    }

    void GLFWWindow::SetCursorMode(CURSOR_MODE _mode)
    {
        if (m_window == nullptr)
            return;

        glfwSetInputMode(m_window, GLFW_CURSOR, CastGlfwCursorMode(_mode));
    }

    float GLFWWindow::GetMouseScrollValue()
    {
        return s_mouseScrollDelta;
    }

    Math::Vec2 GLFWWindow::GetWindowPos()
    {
        int x, y;
        glfwGetWindowPos(m_window, &x, &y);
        return Math::Vec2(static_cast<float>(x), static_cast<float>(y));
    }

    void GLFWWindow::MakeContextCurrent()
    {
        glfwMakeContextCurrent(m_window);
    }

    void GLFWWindow::UpdateWindowSize()
    {
        glfwGetWindowSize(m_window, &width, &height);
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        window = window;
        xoffset = xoffset;
        GLFWWindow::s_mouseScrollDelta = static_cast<float>(yoffset);
    }
}