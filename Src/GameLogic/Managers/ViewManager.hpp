#pragma once

#include "../Eventable.hpp"

struct ViewManager {
    virtual void pushToLogic(const Event* event) = 0;
};