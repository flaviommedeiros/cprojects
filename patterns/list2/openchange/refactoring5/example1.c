#ifdef HAVE_SUBUNIT
if (mt->subunit_output) {
		if (ret == true) {
			subunit_test_pass(name);
		} else {
			subunit_test_fail(name, "failed");
		}
	} else
#endif
	{
	mapitest_print(mt, MODULE_TEST_RESULT, name, (ret == true) ? 
		       MODULE_TEST_SUCCESS : MODULE_TEST_FAILURE);
	mapitest_print_tab(mt);
	mapitest_print_line(mt, MODULE_TEST_LINELEN, MODULE_TEST_DELIM2);
	mapitest_print_newline(mt, MODULE_TEST_NEWLINE);
	}
