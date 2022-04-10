#include "Rules.h"
#include "GrouperBasePheromones.h"

OrRule::OrRule(std::initializer_list<AbstractRule*> rules) : allRules(rules)
{    
}


bool OrRule::condition() const
{
    bool res = false;
    for(AbstractRule* rule : allRules)
    {
        if(rule->condition())
        {
            res = true;
            break;
        }
    }
    return res;
}

void OrRule::action() const
{
    for(AbstractRule* rule : allRules)
    {
        if(rule->condition())
        {
            rule->action();
            break;
        }
    }
}

AbstractGrouperRule::AbstractGrouperRule(GrouperBasePheromones* grouper) : target(grouper)
{

}
