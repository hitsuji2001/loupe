#ifndef __KEYBOARD_AND_MOUSE_HPP__
#define __KEYBOARD_AND_MOUSE_HPP__

namespace oglt {
  // This was stolen from here:
  // If I miss something please notify me
  // https://www.glfw.org/docs/3.3/group__keys.html
  enum class Keyboard {
    KeyUnknown,
    KeySpace,
    KeyApostrophe, /* ' */
    KeyComma, /* , */
    KeyMinus,  /* - */
    KeyPeriod, /* . */
    KeySlash,  /* / */
    Key0,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    KeySemicolon, /* ; */
    KeyEqual, /* = */
    KeyA,
    KeyB,
    KeyC,
    KeyD,
    KeyE,
    KeyF,
    KeyG,
    KeyH,
    KeyI,
    KeyJ,
    KeyK,
    KeyL,
    KeyM,
    KeyN,
    KeyO,
    KeyP,
    KeyQ,
    KeyR,
    KeyS,
    KeyT,
    KeyU,
    KeyV,
    KeyW,
    KeyX,
    KeyY,
    KeyZ,
    KeyLeftBracket, /* [ */
    KeyBackslash,  /* \ */
    KeyRightBracket, /* ] */
    KeyGraveAccent, /* ` */
    KeyWorld1,
    KeyWorld2,
    KeyEscape,
    KeyEnter,
    KeyTab,
    KeyBackspace,
    KeyInsert,
    KeyDelete,
    KeyRight,
    KeyLeft,
    KeyDown,
    KeyUp,
    KeyPageUp,
    KeyPageDown,
    KeyHome,
    KeyEnd,
    KeyCaps,
    KeyScroll,
    KeyNum,
    KeyPrint,
    KeyPause,
    KeyF1,
    KeyF2,
    KeyF3,
    KeyF4,
    KeyF5,
    KeyF6,
    KeyF7,
    KeyF8,
    KeyF9,
    KeyF10,
    KeyF11,
    KeyF12,
    KeyF13,
    KeyF14,
    KeyF15,
    KeyF16,
    KeyF17,
    KeyF18,
    KeyF19,
    KeyF20,
    KeyF21,
    KeyF22,
    KeyF23,
    KeyF24,
    KeyF25,
    KeyKp0,
    KeyKp1,
    KeyKp2,
    KeyKp3,
    KeyKp4,
    KeyKp5,
    KeyKp6,
    KeyKp7,
    KeyKp8,
    KeyKp9,
    KeyKpDecimal,
    KeyKpDivide,
    KeyKpMultiply,
    KeyKpSubtract,
    KeyKpAdd,
    KeyKpEnter,
    KeyKpEqual,
    KeyLeftShift,
    KeyLeftControl,
    KeyLeftAlt,
    KeyLeftSuper,
    KeyRightShift,
    KeyRightControl,
    KeyRightAlt,
    KeyRightSuper,
    KeyMenu,
  };

  // This was stolen from here:
  // If I miss something please notify me
  // https://www.glfw.org/docs/3.3/input_guide.html#input_key
  enum class InputType {
    Press,
    Repeat,
    Release,
  };

  enum class MouseKey {
    MouseButton1,
    MouseButton2,
    MouseButton3,
    MouseButton4,
    MouseButton5,
    MouseButton6,
    MouseButton7,
    MouseButton8,
  };
}

#endif // __KEYBOARD_AND_MOUSE_HPP__
