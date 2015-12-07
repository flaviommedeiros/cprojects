#ifdef CONFIG_VGA_CONSOLE
if (vgacon_text_force())
			nouveau_modeset = 0;
		else
#endif
			nouveau_modeset = 1;
