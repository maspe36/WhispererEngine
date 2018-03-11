//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_MANA_H
#define WHISPERERENGINE_MANA_H


#include "../../Network/Message.h"

class Mana
{
public:
    int black;
    int blue;
    int brown;
    int green;
    int red;
    int white;

    bool operator == (const Mana& other) const;

    void payMana(Mana mana);
    bool canPay(Mana mana);

    json getJSON();

    Mana(int black, int blue, int brown, int green, int red, int white);
    ~Mana();
};


#endif //WHISPERERENGINE_MANA_H
