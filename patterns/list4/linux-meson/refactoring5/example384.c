#ifndef CONFIG_PROVE_LOCKING
if (expected == FAILURE && debug_locks) {
		expected_testcase_failures++;
		printk("failed|");
	}
	else
#endif
	if (debug_locks != expected) {
		unexpected_testcase_failures++;
		printk("FAILED|");

		dump_stack();
	} else {
		testcase_successes++;
		printk("  ok  |");
	}
