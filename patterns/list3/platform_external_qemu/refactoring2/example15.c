#ifndef NO_LOGICAL_JOYSTICKS
if (!LogicalJoystickButton(joystick,
				           joystick->hwdata->key_map[code],
					   events[i].value))
#endif
					SDL_PrivateJoystickButton(joystick,
				           joystick->hwdata->key_map[code],
					   events[i].value);
