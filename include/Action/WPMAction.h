#pragma once

#include <Arduino.h>

#include <Utilify/Action/ActionBase.h>
#include <Utilify/AnalogInput/Potentiometer.h>

class Keyer;
class WPMAction : public ActionBase<int> {
private:
    Keyer &keyer;
public:
    WPMAction(Keyer &keyer);
    void execute(const int &wpm) override;
};
