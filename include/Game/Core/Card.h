//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CARD_H
#define WHISPERERENGINE_CARD_H


#include <string>

class Mana;


class Card
{
public:
    std::string name;
    std::string text;
    Mana *mana;

    Card();
    ~Card();
};


#endif //WHISPERERENGINE_CARD_H
