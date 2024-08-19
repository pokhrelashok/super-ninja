#include "./Ball.h"
#include <string>

Ball::Ball(std::string name, float weight, float bounciness, float friction)
    : weight(weight), bounciness(bounciness), friction(friction), name(name){};
