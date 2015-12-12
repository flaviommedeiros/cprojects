# if defined(__alpha__) && (__GNUC__ == 4)
if (!AO_compare_and_swap_release(list, first, next))
# else
    if (AO_EXPECT_FALSE(!AO_compare_and_swap_release(list, first, next)))
# endif
  {
    AO_store_release(a->AO_stack_bl+i, 0);
    goto retry;
  }
