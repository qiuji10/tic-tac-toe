#pragma once
#include <functional>

class Input{
public:
    void setOnUpPress(const std::function<void()>& callback);
    void setOnDownPress(const std::function<void()>& callback);
    void setOnLeftPress(const std::function<void()>& callback);
    void setOnRightPress(const std::function<void()>& callback);
    void setOnEnterPress(const std::function<void()>& callback);
    void setOnEscapePress(const std::function<void()>& callback);
    void setOnRPress(const std::function<void()>& callback);
    void processInput();
    #if defined(__APPLE__) || defined(__linux__)
    bool hasInput();
    int getChar();
    #endif
private:
    std::function<void()> onUpPress;
    std::function<void()> onDownPress;
    std::function<void()> onLeftPress;
    std::function<void()> onRightPress;
    std::function<void()> onEnterPress;
    std::function<void()> onEscapePress;
    std::function<void()>onRPress;

};