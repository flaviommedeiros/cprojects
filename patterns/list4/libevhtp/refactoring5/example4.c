#ifdef USE_BACKREF_WITH_LEVEL
if (IS_BACKREF_NEST_LEVEL(br)) {
        r = SIZE_OPCODE + SIZE_OPTION + SIZE_LENGTH +
            SIZE_LENGTH + (SIZE_MEMNUM * br->back_num);
      }
      else
#endif
      if (br->back_num == 1) {
	r = ((!IS_IGNORECASE(reg->options) && br->back_static[0] <= 2)
	     ? SIZE_OPCODE : (SIZE_OPCODE + SIZE_MEMNUM));
      }
      else {
	r = SIZE_OPCODE + SIZE_LENGTH + (SIZE_MEMNUM * br->back_num);
      }
