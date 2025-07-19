#include <input.h>

void Input::setOnUpPress(const std::function<void()>& callback) {
    onUpPress = callback;
}

void Input::setOnDownPress(const std::function<void()>& callback) {
    onDownPress = callback;
}

void Input::setOnLeftPress(const std::function<void()>& callback) {
    onLeftPress = callback;
}

void Input::setOnRightPress(const std::function<void()>& callback) {
    onRightPress = callback;
}

void Input::setOnEnterPress(const std::function<void()>& callback) {
    onEnterPress = callback;
}

void Input::setOnEscapePress(const std::function<void()>& callback) {
    onEscapePress = callback;
}

void Input::processInput() {
    if (_kbhit()) {  // Only process if key is pressed
        int ch = _getch();

        if (ch == 224 || ch == 0) {  // Extended key prefix on Windows
            ch = _getch();  // Get the actual key code
            
            switch (ch) {
                case 72:  // Up arrow
                    if (onUpPress) {
                        onUpPress();
                    }
                    break;
                case 80:  // Down arrow
                    if (onDownPress) {
                        onDownPress();
                    }
                    break;
                case 75:  // Left arrow
                    if (onLeftPress) {
                        onLeftPress();
                    }
                    break;
                case 77:  // Right arrow
                    if (onRightPress) {
                        onRightPress();
                    }
                    break;
            }
        } else {
            // Handle regular keys
            switch (ch) {
                case 13:  // Enter
                    if (onEnterPress) {
                        onEnterPress();
                    }
                    break;
                case 27:  // Escape
                    if (onEscapePress) {
                        onEscapePress();
                    }
                    break;
                case 'w':
                case 'W':
                    if (onUpPress) {
                        onUpPress();
                    }
                    break;
                case 's':
                case 'S':
                    if (onDownPress) {
                        onDownPress();
                    }
                    break;
                case 'a':
                case 'A':
                    if (onLeftPress) {
                        onLeftPress();
                    }
                    break;
                case 'd':
                case 'D':
                    if (onRightPress) {
                        onRightPress();
                    }
                    break;
                // case 'q':
                // case 'Q':
                //     exit(0);
                //     break;
            }
        }
    }
}