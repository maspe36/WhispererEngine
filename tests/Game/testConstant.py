from Whisperer import Constant, Mana


class testConstant(Constant):
    def __init__(self):
        name = "testConstant"
        text = "An empty test constant"
        mana = Mana(black=1)
        super().__init__(name, text, mana)
