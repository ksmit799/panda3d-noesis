# include built pyd file
import sys

sys.path.append('../')

from panda3d.core import loadPrcFileData
from direct.showbase.ShowBase import ShowBase

loadPrcFileData("", "load-display pandagl")
loadPrcFileData("", "gl-version 3 2")
loadPrcFileData("", "gl-debug true")
loadPrcFileData("", "model-path resources")
loadPrcFileData("", "notify-level-noesis spam")
loadPrcFileData("", "show-frame-rate-meter true")
loadPrcFileData("", "sync-video false")

from noesis import NoesisRegion, NoesisInputHandler


class MyApp(ShowBase):
    def __init__(self):
        ShowBase.__init__(self)

        self.region = NoesisRegion.make("pandaNoesis", base.win, "Theme/NoesisTheme.DarkBlue.xaml", "HelloWorld.xaml")
        self.region.setActive(True)

        self.handler = NoesisInputHandler()
        base.mouseWatcher.attach_new_node(self.handler)
        self.region.set_input_handler(self.handler)


app = MyApp()
app.run()
