if (bt_has_addi_sp(&bundle, &adjust)
#if TILE_CHIP >= 10
			    || bt_has_add_sp(&bundle, &adjust, moveli_args)
#endif
				) {
				location->sp_location = SP_LOC_OFFSET;

				if (adjust <= 0) {
					/* We are in prolog about to adjust
					 * SP. */
					location->sp_offset = 0;
				} else {
					/* We are in epilog restoring SP. */
					location->sp_offset = adjust;
				}

				sp_determined = true;
			} else {
				if (bt_has_move_r52_sp(&bundle)) {
					/* Maybe in prolog, creating an
					 * alloca-style frame.  But maybe in
					 * the middle of a fixed-size frame
					 * clobbering r52 with SP.
					 */
					sp_moved_to_r52 = true;
				}

				if (bt_modifies_sp(&bundle)) {
					if (sp_moved_to_r52) {
						/* We saw SP get saved into
						 * r52 earlier (or now), which
						 * must have been in the
						 * prolog, so we now know that
						 * SP is still holding the
						 * caller's sp value.
						 */
						location->sp_location =
							SP_LOC_OFFSET;
						location->sp_offset = 0;
					} else {
						/* Someone must have saved
						 * aside the caller's SP value
						 * into r52, so r52 holds the
						 * current value.
						 */
						location->sp_location =
							SP_LOC_IN_R52;
					}
					sp_determined = true;
				}
			}
