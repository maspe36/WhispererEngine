from Whisperer import Creature, Mana


class Azar(Creature):
    def __init__(self):
        name = "Azar"
        text = "The first Whisperer card!"
        mana = Mana(red=1)
        attack = 1
        defense = 1
        super().__init__(name, text, mana, attack, defense)
