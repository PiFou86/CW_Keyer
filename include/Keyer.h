#pragma once

#include <Arduino.h>

class PushButton;
class Potentiometer;
class Keyer {
 public:
  Keyer();
  virtual ~Keyer();

  void loop();

  void wpm(uint8_t speed);
  uint8_t wpm() const;

  void modeA();
  void modeB();

 private:
  PushButton *m_dot;
  PushButton *m_dash;
  PushButton *m_modeA;

  Potentiometer *m_wpmSelector;

  bool m_isModeA;
  uint8_t m_wpm = 5;
  // Based on PARIS (.--. .- .-. .. ...), PARIS takes 10 dots and 4 dashes  (.--. .- .. -.) (.- ..-) (-.-. .... --- -.-. --- .-.. .- -)
  // . . ... . ... . . ... = 14
  // . . ... ... = 8
  // . . ... . . ... = 10
  // . . . ... = 6
  // . . . . . = 5
  // 14 + 8 + 10 + 6 + 6 + 7 = 50
  // 50 dots / word
  const uint8_t m_dotsPerWord = 50;

  bool m_dotPressed = false;
  bool m_dashPressed = false;

  enum class State { Idle, PlayingDot, PlayingDash, InterElementSpace };

  State m_state = State::Idle;
  unsigned long m_stateStartTime = 0;
  bool m_sendDotNext = true;  // pour alternance iambique B

  uint8_t m_pinBuzzer = 11;

  // dot duration in milliseconds = (60 * 1000) / (m_wpm * m_dotsPerWord)
  inline uint16_t dotDuration() const { return (((uint16_t)60 * 1000) / (m_wpm * m_dotsPerWord)); }

  inline uint16_t dashDuration() const {
    return dotDuration() * 3;  // Dash is 3 times the dot duration
  }

  inline uint16_t interCharacterSpaceDuration() const { return dotDuration(); }

  inline uint16_t interWordSpaceDuration() const { return dotDuration() * 7; }
  inline uint16_t interLetterSpaceDuration() const { return dotDuration() * 3; }
};
