from Whisperer import Creature, Mana


class testCreature(Creature):
    def __init__(self):
        name = "testCreature"
        text = "An empty test creature"
        mana = Mana(black=1)
        attackStat = 2
        defenseStat = 1
        super().__init__(name, text, mana, attackStat, defenseStat)
