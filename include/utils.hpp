#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <iostream>
#include "DataStructLib.hpp"

struct Point{
    int x, y;

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }

    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};

int random(int min, int max);

sf::Color getColorFromID(int id);
