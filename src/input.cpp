#include <input.h>
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#elif defined(__APPLE__) || defined(__linux__)
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/select.h>
#endif


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

void Input::setOnRPress(const std::function<void()>& callback) {
    onRPress = callback;
}

#ifdef _WIN32
// Windows implementation using conio.h
bool Input::hasInput() {
    return _kbhit();
}

int Input::getChar() {
    return _getch();
}

void Input::processInput() {
    if (hasInput()) {
        int ch = getChar();
        
        if (ch == 224 || ch == 0) {  // Extended key
            ch = getChar();
            switch (ch) {
                case 72: // Up arrow
                    if (onUpPress) onUpPress();
                    break;
                case 80: // Down arrow
                    if (onDownPress) onDownPress();
                    break;
                case 75: // Left arrow
                    if (onLeftPress) onLeftPress();
                    break;
                case 77: // Right arrow
                    if (onRightPress) onRightPress();
                    break;
            }
        } else {
            switch (ch) {
                case 13: // Enter
                    if (onEnterPress) onEnterPress();
                    break;
                case 27: // Escape
                    if (onEscapePress) onEscapePress();
                    break;
                case 'w': case 'W':
                    if (onUpPress) onUpPress();
                    break;
                case 's': case 'S':
                    if (onDownPress) onDownPress();
                    break;
                case 'a': case 'A':
                    if (onLeftPress) onLeftPress();
                    break;
                case 'd': case 'D':
                    if (onRightPress) onRightPress();
                    break;
                case 'r': case 'R':
                    if (onRPress) onRPress();
                    break;         
            }
        }
    }
}

#elif defined(__APPLE__) || defined(__linux__)
// macOS/Linux implementation using termios

// Terminal state management
static struct termios oldTermios, newTermios;
static bool terminalConfigured = false;

static void enableRawMode() {
    if (!terminalConfigured) {
        tcgetattr(STDIN_FILENO, &oldTermios);
        newTermios = oldTermios;
        newTermios.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
        terminalConfigured = true;
    }
}

static void disableRawMode() {
    if (terminalConfigured) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
        terminalConfigured = false;
    }
}

bool Input::hasInput() {
    enableRawMode();
    
    fd_set readfds;
    struct timeval timeout;
    
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    
    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout) > 0;
}

int Input::getChar() {
    enableRawMode();
    return getchar();
}

void Input::processInput() {
    if (hasInput()) {
        int ch = getChar();
        
        if (ch == 27) {  // Escape sequence (arrow keys)
            if (hasInput() && getChar() == '[') {  // CSI sequence
                if (hasInput()) {
                    int arrow = getChar();
                    switch (arrow) {
                        case 'A': // Up arrow
                            if (onUpPress) onUpPress();
                            break;
                        case 'B': // Down arrow
                            if (onDownPress) onDownPress();
                            break;
                        case 'D': // Left arrow
                            if (onLeftPress) onLeftPress();
                            break;
                        case 'C': // Right arrow
                            if (onRightPress) onRightPress();
                            break;
                    }
                }
            } else {
                // Just escape key
                if (onEscapePress) onEscapePress();
            }
        } else {
            // Regular keys
            switch (ch) {
                case '\n': case '\r': // Enter
                    if (onEnterPress) onEnterPress();
                    break;
                case 'w': case 'W':
                    if (onUpPress) onUpPress();
                    break;
                case 's': case 'S':
                    if (onDownPress) onDownPress();
                    break;
                case 'a': case 'A':
                    if (onLeftPress) onLeftPress();
                    break;
                case 'd': case 'D':
                    if (onRightPress) onRightPress();
                    break;
                case 'r': case 'R':
                    if (onRPress) onRPress();
                    break;
            }
        }
    }
}

#endif
