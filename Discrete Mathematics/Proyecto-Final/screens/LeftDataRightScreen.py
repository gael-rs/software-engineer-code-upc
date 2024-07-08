import customtkinter as ctk
from CTkTable import * 
from libs.trees import generate_ldr

class LeftDataRightScreen(ctk.CTkToplevel):
  def __init__(self, parent, treeOriginal):
    super().__init__(parent)
    self.parent = parent
    self.title("Left - Data - Right")
    self.geometry("500x500")
    self.attributes("-topmost", True)
    self.tree = treeOriginal
    self.paint()
    self.iconbitmap("src/assets/logo.ico", "src/assets/logo.ico")
  
  def paint(self):
    headers = ["Indice", "Left", "Data", "Right"]
    ldr = generate_ldr(self.tree)
    
    ldr.insert(0, headers)
    
    table = CTkTable(master=self, row=len(ldr), column=len(ldr[0]), values=ldr)
    
    table.pack(expand=True, fill="both", padx=20, pady=20)