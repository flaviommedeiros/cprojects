#ifdef HAVE_FSTATAT
if (fstatat(tree_current_dir_fd(t),
		    tree_current_access_path(t), &t->lst,
		    AT_SYMLINK_NOFOLLOW) != 0)
#else
		if (tree_enter_working_dir(t) != 0)
			return NULL;
