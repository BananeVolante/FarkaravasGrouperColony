#ifndef _StaticRules_H
#define _StaticRules_H

#include <vector>
#include <initializer_list>
#include "iostream"
#include <set>

///\brief rule class that requires a pointer to determine the target of a condition or an action
///, which allows the class to be static to save memory
///Uses void* instead of a template like in the templated version of this class to allow a proper polymorphism
class AbstractStaticRule
{
public:
    AbstractStaticRule()
    {

    }

    ///\brief condition of the rule
    ///\param target concerned by the rule
    virtual bool condition(void* target) const = 0;
    ///\brief action of the rule
    ///\param target concerned by the rule
    virtual void action(void* target) const = 0;
};


///\brief static rule that uses function pointers passed as parameters as conditions and action
class PersonalisableStaticRule : public AbstractStaticRule
{
public: 
    typedef bool (*conditionFunction)(void* target);
    typedef void (*actionFunction)(void* target);
private: 
    ///\brief pointer to the condition function
    const conditionFunction condFunctPtr;
    ///\brief pointer to the action function
    const actionFunction actionFuncPtr;

public:
    ///\param cond condition function
    ///\param act action function
    PersonalisableStaticRule(conditionFunction cond, actionFunction act) : condFunctPtr(cond), actionFuncPtr(act)
    {}

    ///\copydoc AbstractStaticRule::condition
    virtual bool condition(void* target) const
    {return condFunctPtr(target);}
    ///\copydoc AbstractStaticRule::action
    virtual void action(void* target) const
    {actionFuncPtr(target);}
};


///\brief class taht stores multiple rules, and act based on a OR
class StaticOrRule : public AbstractStaticRule
{
private: 
    ///\brief vector that stores all the rules
    const std::vector<const AbstractStaticRule*> rules;

public:
    ///\param rules bracket list of all the rules that the class wil act on
    StaticOrRule(std::initializer_list<const AbstractStaticRule*> rules) : rules(rules)
    {}
    ///\copydoc AbstractStaticRule::condition
    ///\brief return true if one of the rules have condition = true
    virtual bool condition(void* target) const
    {
        bool res = false;
        for(const AbstractStaticRule* rule : rules )
        {
            if(rule->condition(target))
            {
                res = true;
                break;
            }
        }
        return res;
    }
    ///\copydoc AbstractStaticRule::action
    ///\brief do the action of the first rule that is true
    virtual void action(void* target) const
    {
        for(const AbstractStaticRule* rule : rules)
        {
            if(rule->condition(target))
            {
                rule->action(target);
                break;
            }
        }
    }
};
#endif