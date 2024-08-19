#include "./Ball.h"
#include <string>

Ball::Ball(std::string name, float weight, float bounciness, float friction, Texture &t)
    : weight(weight), bounciness(bounciness), friction(friction), name(name), texture(t) {};
