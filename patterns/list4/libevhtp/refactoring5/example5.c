#ifdef USE_BACKREF_WITH_LEVEL
if (IS_BACKREF_NEST_LEVEL(br)) {
	r = add_opcode(reg, OP_BACKREF_WITH_LEVEL);
	if (r) return r;
	r = add_option(reg, (reg->options & ONIG_OPTION_IGNORECASE));
	if (r) return r;
	r = add_length(reg, br->nest_level);
	if (r) return r;

	goto add_bacref_mems;
      }
      else
#endif
      if (br->back_num == 1) {
	n = br->back_static[0];
	if (IS_IGNORECASE(reg->options)) {
	  r = add_opcode(reg, OP_BACKREFN_IC);
	  if (r) return r;
	  r = add_mem_num(reg, n);
	}
	else {
	  switch (n) {
	  case 1:  r = add_opcode(reg, OP_BACKREF1); break;
	  case 2:  r = add_opcode(reg, OP_BACKREF2); break;
	  default:
	    r = add_opcode(reg, OP_BACKREFN);
	    if (r) return r;
	    r = add_mem_num(reg, n);
	    break;
	  }
	}
      }
      else {
	int i;
	int* p;

        if (IS_IGNORECASE(reg->options)) {
          r = add_opcode(reg, OP_BACKREF_MULTI_IC);
        }
        else {
          r = add_opcode(reg, OP_BACKREF_MULTI);
        }
	if (r) return r;

#ifdef USE_BACKREF_WITH_LEVEL
      add_bacref_mems:
#endif
	r = add_length(reg, br->back_num);
	if (r) return r;
	p = BACKREFS_P(br);
	for (i = br->back_num - 1; i >= 0; i--) {
	  r = add_mem_num(reg, p[i]);
	  if (r) return r;
	}
      }
