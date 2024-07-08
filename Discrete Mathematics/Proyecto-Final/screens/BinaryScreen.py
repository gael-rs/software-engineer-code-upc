from PIL import Image
import customtkinter as ctk
from anytree.exporter import UniqueDotExporter
from libs.trees import n_tree_binary, tree_for_extension
from utils.fonts import getFont

class BinaryScreen(ctk.CTkToplevel):
  def __init__(self, parent, treeOriginal):
    super().__init__(parent)
    self.parent = parent
    self.title("Árbol binario")
    self.geometry("500x500")
    self.attributes("-topmost", True)
    self.tree = treeOriginal
    self.paint()
    self.iconbitmap("src/assets/logo.ico", "src/assets/logo.ico")
  
  def paint(self):
    container = ctk.CTkFrame(self, fg_color="transparent")
    
    self.label_t = ctk.CTkLabel(container, text="Árbol binario", font=getFont(size=25, weight="bold"))
    self.label_t.pack(pady=5, padx=10)
    
    self.path_tree = f"./tree-pro/binary.png"
    self.binary = n_tree_binary(self.tree)
    
    for_extension = tree_for_extension(self.binary)
    
    self.label_info = ctk.CTkLabel(container, text=for_extension,font=getFont(size=20, weight="bold"), wraplength=430)
    self.label_info.pack(pady=10, padx=10)
    UniqueDotExporter(self.binary).to_picture(self.path_tree)
  
    image = Image.open(self.path_tree)
    
    self.image_tree = ctk.CTkImage(light_image=Image.open(self.path_tree), dark_image=Image.open(self.path_tree), size=(image.width * 1 / 2.6, image.height * 1 / 2.6))
        
    self.image = ctk.CTkLabel(container, image=self.image_tree, text="")
    self.image.pack(padx=20, pady=0)
    
    container.pack(expand=True, pady= 20)
  
    