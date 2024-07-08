import customtkinter as ctk
from App import App

class Screen(ctk.CTkFrame):
    def __init__(self, parent, controller: App):
        super().__init__(parent, corner_radius=0, fg_color="transparent")
        self.controller = controller
        self.painted = False

    def load(self):
        pass
    
    def paint(self):
        pass
    
    def update(self):
        pass
    
    def show(self):
        self.load()
        if not self.painted: self.paint()
        if self.painted: self.update()
        
        self.grid(row=0, column=0, sticky="nsew")
        self.painted = True