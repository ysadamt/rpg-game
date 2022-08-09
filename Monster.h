#ifndef MONSTER_H
#define MONSTER_H

#include "Creature.h"
#include "cMain.h"
#include "Random.h"
#include <iostream>
#include <array>
#include <random>

class Monster : public Creature
{
public:
    enum class Type
    {
        dragon,
        orc,
        slime,
        max_types
    };

    Monster(Type type)
        : Creature{ getDefaultCreature(type) }
    {
    }

    static Type getRandomMonster()
    {
        int randNum{ Random::getRandomNumber(0, static_cast<int>(Type::max_types) - 1) };
        Type m{ static_cast<Type>(randNum) };

        return m;
    }

private:
    static const Creature& getDefaultCreature(Type type)
    {
        static const std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData{
            { { "dragon", 'D', 20, 4, 100 },
            { "orc", 'o', 4, 2, 25 },
            { "slime", 's', 1, 1, 10 } }
        };

        return monsterData.at(static_cast<std::size_t>(type));
    }
};

#endif