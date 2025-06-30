#pragma once

#include <Utilify/Action/ActionBase.h>

class SetFalseAction : public ActionBase<void> {
 public:
  SetFalseAction(bool& target) : m_target(target) {}

  void execute() override { m_target = false; }

 private:
  bool& m_target;
};
