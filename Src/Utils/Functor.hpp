#pragma once

//=======================================FUNCTOR================================

class BasicFunctor
{
public:
    virtual void operator()() = 0;

    virtual BasicFunctor* clone() = 0;

    virtual ~BasicFunctor() = default;
};

template<class Params>
class Functor : public BasicFunctor
{
    typedef void (*Function)(Params);

public:
    Functor(Function function, Params params) :
    params (params)
    { }

    BasicFunctor* clone()
    {
        return static_cast<BasicFunctor*>(new Functor<Params>(func, params));
    }

    void operator()()
    {
        func(params);
    }

protected:
    Function func;
    Params   params;
};
