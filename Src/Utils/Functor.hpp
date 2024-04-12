#pragma once

//=======================================FUNCTOR================================

class BasicFunctor
{
public:
    virtual void operator()() = 0;
};

template<class Params>
class Functor : public BasicFunctor
{
    typedef void (*Function)(Params);

public:
    Functor(Function function, Params params) :
    params (params)
    { }

    void operator()()
    {
        func(params);
    }

protected:
    Function func;
    Params   params;
};
