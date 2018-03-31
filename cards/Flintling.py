from Whisperer import Creature, Mana


class Flintling(Creature):
    def __init__(self):
        name = "Flintling"
        text = ""
        mana = Mana(brown=1)
        attack = 1
        defense = 2
        super().__init__(name, text, mana, attack, defense)
