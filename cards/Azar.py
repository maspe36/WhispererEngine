from Whisperer import Card, Mana


class Azar(Card):
    def __init__(self):
        name = "Azar"
        text = "The first Whisperer card!"
        mana = Mana(red=1, black=1, blue=1)
        super().__init__(name, text, mana)
