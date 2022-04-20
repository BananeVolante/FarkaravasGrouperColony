#include "PheromonesTeamHandler.h"
#include "GrouperBase.h"
#include "MathUtils.h"

const float PheromonesTeamHandler::PHEROMONES_SENSE_ANGLE = MathUtils::pi /3;

PheromonesTeamHandler::PheromonesTeamHandler(GrouperBase* grouper) : AbstractPheromonesHandler(grouper)
{}

void PheromonesTeamHandler::putPheromones(float amount) const
{
    //check for nearby pheromones pile
    //if there are piles, add amount to ALL piles
    //else create a new pile
    std::vector<PheromonesTeam*> pheromonesPiles =  getGrouper()->perceive<PheromonesTeam>();
    if(pheromonesPiles.empty())
        new PheromonesTeam(getGrouper()->getEnvironment(), getGrouper()->getPosition(), amount, getGrouper()->getHQ());
    else
    {
        for(PheromonesTeam *f : pheromonesPiles)
            f->addQuantity(amount);
        
    }
}

PheromonesTeam* PheromonesTeamHandler::choosePheromone(GrouperHQ* team, bool searchForAlly) const
{
    //get nearby pheromones
    std::vector<PheromonesTeam*> nearbyPheromones = getGrouper()->perceive<PheromonesTeam>(getGrouper()->getMvDirection(), PHEROMONES_SENSE_ANGLE, PHEROMONES_SENSE_DISTANCE);
    std::vector<PheromonesTeam*> nearbyValidPheromones;
    for(PheromonesTeam* phe : nearbyPheromones)
    {
        if((phe->getTeam() == team) == searchForAlly)
            nearbyValidPheromones.push_back(phe);
    }
    size_t listSize = nearbyValidPheromones.size();
    if(listSize == 0) // if there are no pheromone,s useless to continue
        return nullptr;
    std::vector<float> weights(listSize);
    for (size_t i = 0; i < listSize; i++) // create a vector with the weights of all pheromones
        weights[i] = nearbyValidPheromones[i]->getQuantity();

    return nearbyValidPheromones[MathUtils::randomChoose(weights)];//choose one pheromone and returns it
}

PheromonesTeam* PheromonesTeamHandler::choosePheromone() const
{
    return choosePheromone(getGrouper()->getHQ());
}