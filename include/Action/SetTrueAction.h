#pragma once

#include <Utilify/Action/ActionBase.h>

class SetTrueAction : public ActionBase<void> {
 public:
  SetTrueAction(bool& target) : m_target(target) {}

  void execute() override { m_target = true; }

 private:
  bool& m_target;
};
