#pragma once

#include <Utilify/Action/ActionBase.h>

class ToggleBooleanAction : public ActionBase<void> {
 public:
  ToggleBooleanAction(bool& target) : m_target(target) {}

  void execute() override { m_target = !m_target; }

 private:
  bool& m_target;
};
