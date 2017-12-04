from Whisperer import Card, Mana


class testCard(Card):
    def __init__(self):
        name = "testCard"
        text = "An empty test card"
        mana = Mana(red=1)
        super().__init__(name, text, mana)
