#include "GLFWWindow.hpp"

void GLFWWindow::CreateWindow(const char* _name, int _width, int _height)
{
    name = _name;
    width = _width;
    height = _height;

    if (!glfwInit())
    {
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);

    if (m_window == nullptr)
    {
        return;
    }

    glfwMakeContextCurrent(m_window);
}

void GLFWWindow::SetFrameBufferSizeCallback()
{
    // TODO
    return;
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
    std::map<KEY_CODE, INPUT_ACTION>::iterator it;
    for (it = m_keys.begin(); it != m_keys.end(); it++)
    {
        int action = glfwGetKey(m_window, CastGlfwKeyCode(it->first));
        if (action == GLFW_PRESS)
        {
            if (it->second == INPUT_PRESS || it->second == INPUT_DOWN)
                it->second = INPUT_DOWN;
            else
                it->second = INPUT_PRESS;
        }
        else if (action == GLFW_RELEASE)
        {
            if (it->second == INPUT_RELEASE || it->second == INPUT_UP)
                it->second = INPUT_UP;
            else
                it->second = INPUT_RELEASE;
        }
    }

    std::map<MOUSE_CODE, INPUT_ACTION>::iterator it2;
    for (it2 = m_mouseButtons.begin(); it2 != m_mouseButtons.end(); it2++)
    {
        int action = glfwGetMouseButton(m_window, CastGlfwMouseCode(it2->first));
        if (action == GLFW_PRESS)
        {
            if (it2->second == INPUT_PRESS || it2->second == INPUT_DOWN)
                it2->second = INPUT_DOWN;
            else
                it2->second = INPUT_PRESS;
        }
        else if (action == GLFW_RELEASE)
        {
            if (it2->second == INPUT_RELEASE || it2->second == INPUT_UP)
                it2->second = INPUT_UP;
            else
                it2->second = INPUT_RELEASE;
        }
    }
}

bool GLFWWindow::GetKey(KEY_CODE _code, INPUT_ACTION _action)
{
    if (_action == INPUT_UP)
        return m_keys[_code] == _action || m_keys[_code] == INPUT_RELEASE;
    else if (_action == INPUT_DOWN)
        return m_keys[_code] == _action || m_keys[_code] == INPUT_PRESS;
    return m_keys[_code] == _action;
}

bool GLFWWindow::GetMouseButton(MOUSE_CODE _code, INPUT_ACTION _action)
{
    if (_action == INPUT_UP)
        return m_mouseButtons[_code] == _action || m_mouseButtons[_code] == INPUT_RELEASE;
    else if (_action == INPUT_DOWN)
        return m_mouseButtons[_code] == _action || m_mouseButtons[_code] == INPUT_PRESS;
    return m_mouseButtons[_code] == _action;
}

Math::Vec2 GLFWWindow::GetCursorPos()
{
    // TODO
    return Math::Vec2();
}

void GLFWWindow::SetCursorPos(Math::Vec2 _pos)
{
    // TODO
    Math::Vec2 v = _pos;
    return;
}

void GLFWWindow::SetCursorMode(CURSOR_MODE _mode)
{
    if (m_window == nullptr)
        return;

    glfwSetInputMode(m_window, GLFW_CURSOR, CastGlfwCursorMode(_mode));
}