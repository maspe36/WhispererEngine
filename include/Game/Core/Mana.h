//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_MANA_H
#define WHISPERERENGINE_MANA_H


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

    void payMana(Mana *mana);

    Mana(int black, int blue, int brown, int green, int red, int white);
    ~Mana();
};


#endif //WHISPERERENGINE_MANA_H
