#ifndef NO_LOGICAL_JOYSTICKS
if (SDL_joylist[joystick->index].fname != NULL)
#endif
		close(joystick->hwdata->fd);
