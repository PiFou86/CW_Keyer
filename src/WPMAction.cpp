#include "Action/WPMAction.h"

#include "Keyer.h"

WPMAction::WPMAction(Keyer &keyer) : ActionBase<int>(), keyer(keyer) {
    ;
}

void WPMAction::execute(const int &wpm) {
    int wpmValue = map(wpm, 0, 1024, 5, 20);
    keyer.wpm(wpmValue);
}
