from opt_module import OptFourier

# Use project root as working directory
OptFourier.output_path = "buch/papers/opt/images"

exp_slit = OptFourier()
exp_slit.add_slit(500, 50, 3)
exp_slit.show("Dreifachspalt, Hochpass", vmax=1e7, omega=20, highpass=True)
exp_slit.show("Dreifachspalt, Tiefpass", vmax=1e7, omega=20, highpass=False)

exp_grid = OptFourier()
exp_grid.add_grid(50, 100)
exp_grid.show("Gitter, Hochpass", vmax=8e6, omega=30, highpass=True)
exp_grid.show("Gitter, Tiefpass", vmax=8e6, omega=30, highpass=False)

# OptFourier.show_all() # Enable to show all figures
