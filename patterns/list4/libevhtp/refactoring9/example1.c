static Node*
node_new_backref(int back_num, int* backrefs, int by_name,
#ifdef USE_BACKREF_WITH_LEVEL
		 int exist_level, int nest_level,
#endif
		 ScanEnv* env)
{
  int i;
  Node* node = node_new();

  CHECK_NULL_RETURN(node);

  SET_NTYPE(node, NT_BREF);
  NBREF(node)->state    = 0;
  NBREF(node)->back_num = back_num;
  NBREF(node)->back_dynamic = (int* )NULL;
  if (by_name != 0)
    NBREF(node)->state |= NST_NAME_REF;

#ifdef USE_BACKREF_WITH_LEVEL
  if (exist_level != 0) {
    NBREF(node)->state |= NST_NEST_LEVEL;
    NBREF(node)->nest_level  = nest_level;
  }
#endif

  for (i = 0; i < back_num; i++) {
    if (backrefs[i] <= env->num_mem &&
	IS_NULL(SCANENV_MEM_NODES(env)[backrefs[i]])) {
      NBREF(node)->state |= NST_RECURSION;   /* /...(\1).../ */
      break;
    }
  }

  if (back_num <= NODE_BACKREFS_SIZE) {
    for (i = 0; i < back_num; i++)
      NBREF(node)->back_static[i] = backrefs[i];
  }
  else {
    int* p = (int* )xmalloc(sizeof(int) * back_num);
    if (IS_NULL(p)) {
      onig_node_free(node);
      return NULL;
    }
    NBREF(node)->back_dynamic = p;
    for (i = 0; i < back_num; i++)
      p[i] = backrefs[i];
  }
  return node;
}
