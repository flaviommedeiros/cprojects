#     ifndef ALL_INTERIOR_POINTERS
if (!TEST_FAIL_COUNT(1))
#      else
        if (!TEST_FAIL_COUNT(GC_get_all_interior_pointers() ? 1 : 2))
#      endif
        {
          GC_printf(
              "GC_is_valid_displacement produced wrong failure indication\n");
          FAIL;
        }
