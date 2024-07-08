from bases.Screen import Screen
import customtkinter as ctk
import sys
from utils.fonts import getFont


class MenuScreen(Screen):
    def __init__(self, parent, controller):
        super().__init__(parent, controller)
        self.grid_columnconfigure(0, weight=1)
        self.grid_rowconfigure(0, weight=1)
    
    
    def paint(self):
        
        container = ctk.CTkFrame(self, fg_color="transparent")
        container.pack(expand=True)
        
        title = ctk.CTkLabel(container, text="TreeTrack Pro", font=getFont(size=50, weight="bold"  ))
        title.pack(anchor=ctk.N)
        
        containerButtons = ctk.CTkFrame(container, fg_color="transparent")
        containerButtons.pack(padx=40, anchor=ctk.N, pady=15)
        
        button_tree = ctk.CTkButton(containerButtons, text="Generar árbol", command=lambda: self.controller.show_screen("TreeScreen"), font=getFont(size=13), height=35)
        button_tree.pack(pady=10)

        button_instructions = ctk.CTkButton(containerButtons, text="Instrucciones", command=lambda: self.controller.show_screen("InstructionsScreen"), font=getFont(size=13), height=35)
        button_instructions.pack(pady=10)

        button_credits = ctk.CTkButton(containerButtons, text="Créditos", command=lambda: self.controller.show_screen("CreditsScreen"), font=getFont(size=13), height=35)
        button_credits.pack(pady=10)
        
        button_leave = ctk.CTkButton(containerButtons, text="Salir", command=lambda: sys.exit(),  font=getFont(size=13), height=35);
        button_leave.pack(pady=10)
    
