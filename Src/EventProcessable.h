#pragma once

class EventProcessable
{
public:
    virtual bool onClick(int x, int y) = 0;
    virtual void onTick() = 0;
    virtual ~EventProcessable() = default;
};
