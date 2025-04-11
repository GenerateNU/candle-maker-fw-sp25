#include <ezButton.h>

class LimitSwitch {
  private:
    ezButton button;
    void (*onPressCallback)();

  public:
    LimitSwitch(uint8_t pin, void (*callback)() = nullptr)
      : button(pin), onPressCallback(callback) {
        button.setDebounceTime(50); // ms
    }

    void update() {
      button.loop();
      if (button.isPressed()) {
        if (onPressCallback) onPressCallback();
      }
    }

    void setCallback(void (*callback)()) {
      onPressCallback = callback;
    }

    bool isPressed() {
      return button.isPressed();
    }

    bool isReleased() {
      return button.isReleased();
    }

    bool getState() {
      return button.getState();
    }
};
