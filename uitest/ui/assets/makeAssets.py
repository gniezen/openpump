import Image
import gameduino2 as gd2

class Spinner(gd2.prep.AssetBin):

    def addall(self):
        spinner = gd2.prep.split(90, 30, Image.open("720.png"))
        self.load_handle("SPINNER", spinner, gd2.ARGB1555)

        self.load_handle("SYRINGE",Image.open("syringe.png"),gd2.ARGB4)

if __name__ == '__main__':
    Spinner().make()