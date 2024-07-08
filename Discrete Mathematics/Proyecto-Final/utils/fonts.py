import customtkinter as ctk

def load_fonts():
  ctk.FontManager.load_font("src/fonts/Rubik/Rubik-VariableFont_wght.ttf")
  ctk.FontManager.load_font("src/fonts/Rubik/Rubik-Italic-VariableFont_wght.ttf")
  
def getFont(family="Rubik", weight="normal", size=20):
  return ctk.CTkFont(family=family, size=size, weight=weight)
