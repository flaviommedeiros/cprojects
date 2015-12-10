#ifndef NO_LOGICAL_JOYSTICKS
if (!LogicalJoystickAxis(joystick,
				           events[i].number, events[i].value))
#endif
					SDL_PrivateJoystickAxis(joystick,
				           events[i].number, events[i].value);
