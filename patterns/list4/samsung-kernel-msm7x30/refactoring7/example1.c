return (!RB_EMPTY_ROOT(&bfqd->queue_weights_tree) &&
		(bfqd->queue_weights_tree.rb_node->rb_left ||
		 bfqd->queue_weights_tree.rb_node->rb_right)
#ifdef CONFIG_CGROUP_BFQIO
	       ) ||
	       (!RB_EMPTY_ROOT(&bfqd->group_weights_tree) &&
		(bfqd->group_weights_tree.rb_node->rb_left ||
		 bfqd->group_weights_tree.rb_node->rb_right)
#endif
	       );
