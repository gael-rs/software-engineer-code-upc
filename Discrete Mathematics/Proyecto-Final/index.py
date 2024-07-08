from App import App

from screens.MenuScreen import MenuScreen
from screens.InstructionsScreen import InstructionsScreen
from screens.CreditsScreen import CreditsScreen
from screens.TreeScreen import TreeScreen
from libs.Reloader import run_with_reloader
from utils.fonts import load_fonts

load_fonts()

app = App()
app.default_screen(MenuScreen)
app.add_screen(InstructionsScreen)
app.add_screen(CreditsScreen)
app.add_screen(TreeScreen)

run_with_reloader(app, "<Control-R>", "<Control-r>", "<F5>")