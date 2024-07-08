from bases.Screen import Screen
import customtkinter as ctk

class CreditsScreen(Screen):

    def __init__(self, parent, controller):
        super().__init__(parent, controller)
        
    def paint(self):
        longtext = """
Grupo: 5

Sección: SI39

Profesor: Jonathan Abrahan Sueros Zarate 

Integrantes:
Chi Cruzatt, Kevin Jorge - u202313655
Hallasi Saravia, Miguel Angel -  u202312391
Oroncoy Almeyda Alejandro Daniel  - u202313397
Parraga Piñin, Camilo Alonso  - u202323939
Rivera Sosa Eduardo Gael - u202312222

        """
        
        container = ctk.CTkFrame(self, fg_color="transparent")
        container.pack(expand=True)
        

        title_label = ctk.CTkLabel(container, text="Créditos", font=ctk.CTkFont(size=30, weight="bold"))
        title_label.pack(padx=10, pady=(40, 20))


        scroll_frame = ctk.CTkScrollableFrame(container, width=200, height=300)
        scroll_frame.pack(padx=10, pady=10)

        label_1 = ctk.CTkLabel(scroll_frame, text=longtext, wraplength=self.winfo_reqwidth() - 0,  font=ctk.CTkFont(size=15))
        label_1.pack()

        button_back = ctk.CTkButton(container,text="Volver", command=lambda: self.controller.show_screen("MenuScreen"));
        button_back.pack(padx=10, pady=10)