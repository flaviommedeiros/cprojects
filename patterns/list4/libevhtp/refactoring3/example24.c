switch (type) {
  case NT_LIST:
    {
      Node* prev = NULL_NODE;
      do {
	r = setup_comb_exp_check(NCAR(node), r, env);
	prev = NCAR(node);
      } while (r >= 0 && IS_NOT_NULL(node = NCDR(node)));
    }
    break;

  case NT_ALT:
    {
      int ret;
      do {
	ret = setup_comb_exp_check(NCAR(node), state, env);
	r |= ret;
      } while (ret >= 0 && IS_NOT_NULL(node = NCDR(node)));
    }
    break;

  case NT_QTFR:
    {
      int child_state = state;
      int add_state = 0;
      QtfrNode* qn = NQTFR(node);
      Node* target = qn->target;
      int var_num;

      if (! IS_REPEAT_INFINITE(qn->upper)) {
	if (qn->upper > 1) {
	  /* {0,1}, {1,1} are allowed */
	  child_state |= CEC_IN_FINITE_REPEAT;

	  /* check (a*){n,m}, (a+){n,m} => (a*){n,n}, (a+){n,n} */
	  if (env->backrefed_mem == 0) {
	    if (NTYPE(qn->target) == NT_ENCLOSE) {
	      EncloseNode* en = NENCLOSE(qn->target);
	      if (en->type == ENCLOSE_MEMORY) {
		if (NTYPE(en->target) == NT_QTFR) {
		  QtfrNode* q = NQTFR(en->target);
		  if (IS_REPEAT_INFINITE(q->upper)
		      && q->greedy == qn->greedy) {
		    qn->upper = (qn->lower == 0 ? 1 : qn->lower);
		    if (qn->upper == 1)
		      child_state = state;
		  }
		}
	      }
	    }
	  }
	}
      }

      if (state & CEC_IN_FINITE_REPEAT) {
	qn->comb_exp_check_num = -1;
      }
      else {
	if (IS_REPEAT_INFINITE(qn->upper)) {
	  var_num = CEC_INFINITE_NUM;
	  child_state |= CEC_IN_INFINITE_REPEAT;
	}
	else {
	  var_num = qn->upper - qn->lower;
	}

	if (var_num >= CEC_THRES_NUM_BIG_REPEAT)
	  add_state |= CEC_CONT_BIG_REPEAT;

	if (((state & CEC_IN_INFINITE_REPEAT) != 0 && var_num != 0) ||
	    ((state & CEC_CONT_BIG_REPEAT) != 0 &&
	     var_num >= CEC_THRES_NUM_BIG_REPEAT)) {
	  if (qn->comb_exp_check_num == 0) {
	    env->num_comb_exp_check++;
	    qn->comb_exp_check_num = env->num_comb_exp_check;
	    if (env->curr_max_regnum > env->comb_exp_max_regnum)
	      env->comb_exp_max_regnum = env->curr_max_regnum;
	  }
	}
      }

      r = setup_comb_exp_check(target, child_state, env);
      r |= add_state;
    }
    break;

  case NT_ENCLOSE:
    {
      EncloseNode* en = NENCLOSE(node);

      switch (en->type) {
      case ENCLOSE_MEMORY:
	{
	  if (env->curr_max_regnum < en->regnum)
	    env->curr_max_regnum = en->regnum;

	  r = setup_comb_exp_check(en->target, state, env);
	}
	break;

      default:
	r = setup_comb_exp_check(en->target, state, env);
	break;
      }
    }
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    if (IS_CALL_RECURSION(NCALL(node)))
      env->has_recursion = 1;
    else
      r = setup_comb_exp_check(NCALL(node)->target, state, env);
    break;
#endif

  default:
    break;
  }
