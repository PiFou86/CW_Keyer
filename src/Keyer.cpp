#include "Keyer.h"

#include <Utilify/DigitalInput/PushButton.h>

#include <Utilify/AnalogInput/Potentiometer.h>

#include "Action/ToogleBooleanAction.h"
#include "Action/SetFalseAction.h"
#include "Action/SetTrueAction.h"
#include "Action/WPMAction.h"

Keyer::Keyer()
    : m_dot(nullptr),
      m_dash(nullptr),
      m_modeA(nullptr),

      m_wpmSelector(nullptr),

      m_isModeA(true),

      m_wpm(15),

      m_dotPressed(false),
      m_dashPressed(false)
{
  this->m_dot = new PushButton(2);
  this->m_dash = new PushButton(3);
  this->m_modeA = new PushButton(4);

  this->m_dot->callbackKeyUp(new SetFalseAction(m_dotPressed));
  this->m_dot->callbackKeyDown(new SetTrueAction(m_dotPressed));

  this->m_dash->callbackKeyUp(new SetFalseAction(m_dashPressed));
  this->m_dash->callbackKeyDown(new SetTrueAction(m_dashPressed));

  ActionBase<void>* modeAAction = new ToggleBooleanAction(m_isModeA);
  this->m_modeA->callbackKeyUp(modeAAction);
  this->m_modeA->callbackKeyDown(modeAAction);

  this->m_wpmSelector = new Potentiometer(A0, new WPMAction(*this));
}

Keyer::~Keyer() {
  delete m_dot;
  delete m_dash;
  delete m_modeA;
  delete m_wpmSelector;

  m_dot = nullptr;
  m_dash = nullptr;
  m_modeA = nullptr;
  m_wpmSelector = nullptr;

  noTone(this->m_pinBuzzer);
  m_state = State::Idle;
}

void Keyer::loop() {
  m_dot->tick();
  m_dash->tick();
  m_modeA->tick();
  m_wpmSelector->tick();

  unsigned long now = millis();

  switch (m_state) {
    case State::Idle:
      if (m_dotPressed && m_dashPressed) {
        if (m_sendDotNext) {
          tone(this->m_pinBuzzer, 800); // buzzer on
          m_state = State::PlayingDot;
          m_stateStartTime = now;
        } else {
          tone(this->m_pinBuzzer, 800);
          m_state = State::PlayingDash;
          m_stateStartTime = now;
        }

        if (!m_isModeA) {
          m_sendDotNext = !m_sendDotNext;
        }
      } else if (m_dotPressed) {
        tone(this->m_pinBuzzer, 800);
        m_state = State::PlayingDot;
        m_stateStartTime = now;
      } else if (m_dashPressed) {
        tone(this->m_pinBuzzer, 800);
        m_state = State::PlayingDash;
        m_stateStartTime = now;
      }
      break;

    case State::PlayingDot:
      if (now - m_stateStartTime >= dotDuration()) {
        noTone(this->m_pinBuzzer);
        m_state = State::InterElementSpace;
        m_stateStartTime = now;
      }
      break;

    case State::PlayingDash:
      if (now - m_stateStartTime >= dashDuration()) {
        noTone(this->m_pinBuzzer);
        m_state = State::InterElementSpace;
        m_stateStartTime = now;
      }
      break;

    case State::InterElementSpace:
      if (now - m_stateStartTime >= dotDuration()) { // inter-element space = 1 dot
        m_state = State::Idle;
      }
      break;
  }
}

void Keyer::wpm(uint8_t speed) { Serial.println(speed);  m_wpm = speed; }

uint8_t Keyer::wpm() const { return m_wpm; }

void Keyer::modeA() { m_isModeA = true; }

void Keyer::modeB() { m_isModeA = false; }
