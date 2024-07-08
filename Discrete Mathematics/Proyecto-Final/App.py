import customtkinter as ctk

ctk.set_default_color_theme("src/theme/custom.json")
ctk.set_appearance_mode("dark")

class App(ctk.CTk):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.width = 500
        self.height = 500
        self.screens = {}
        self.geometry(f"{self.width}x{self.height}")
        self.title("TreeTrack Pro 🌲")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)
        self.iconbitmap("src/assets/logo.ico", "src/assets/logo.ico")
        
        
    def show_screen(self, container):
        for s in self.screens.values():
            s.grid_remove()
            
        screen = self.screens[container]
        
        screen.show()
        

    def default_screen(self, Screen): 
      self.add_screen(Screen)
      self.show_screen(Screen.__name__)

    def add_screen(self, Screen):
        screen = Screen(self, self)
        self.screens[Screen.__name__] = screen
