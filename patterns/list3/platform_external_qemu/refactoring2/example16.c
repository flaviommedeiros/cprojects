#ifndef NO_LOGICAL_JOYSTICKS
if (!LogicalJoystickAxis(joystick,
				           joystick->hwdata->abs_map[code],
					   events[i].value))
#endif
					SDL_PrivateJoystickAxis(joystick,
				           joystick->hwdata->abs_map[code],
					   events[i].value);
