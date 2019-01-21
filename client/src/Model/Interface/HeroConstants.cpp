#include "HeroConstants.h"


HeroName HeroConstants::get_Name() const {
    return name;
}

HeroConstants::~HeroConstants() {//TODO clear the AbilityNames vector

}

void HeroConstants::set_Name(HeroName name) {
    HeroConstants::name = name;
}

HeroName &HeroConstants::Name() {
    return name;
}

HeroName HeroConstants::Name() const {
    return name;
}

const std::vector<AbilityName *> &HeroConstants::get_AbilityNames() const {
    return AbilityNames;
}

void HeroConstants::set_AbilityNames(const std::vector<AbilityName *> &AbilityNames) {
    HeroConstants::AbilityNames = AbilityNames;
}

int HeroConstants::get_MaxHP() const {
    return maxHP;
}

void HeroConstants::set_MaxHP(int maxHP) {
    HeroConstants::maxHP = maxHP;
}

int &HeroConstants::MaxHP() {
    return maxHP;
}

int HeroConstants::MaxHP() const {
    return maxHP;
}

int HeroConstants::get_MoveAPCost() const {
    return moveAPCost;
}

void HeroConstants::set_MoveAPCost(int moveAPCost) {
    HeroConstants::moveAPCost = moveAPCost;
}

int &HeroConstants::MoveAPCost() {
    return moveAPCost;
}

int HeroConstants::MoveAPCost() const {
    return moveAPCost;
}
