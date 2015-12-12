if (!__get_user(link, (unsigned long *)
					(UNW_FP(frame) + FRAME_LINK_OFFSET))
#if FRAME_RETADDR_OFFSET < 0
			    && link > bottom && link < UNW_FP(frame)
#else
			    && link > UNW_FP(frame) && link < bottom
#endif
			    && !(link & (sizeof(link) - 1))
			    && !__get_user(UNW_PC(frame),
					   (unsigned long *)(UNW_FP(frame)
						+ FRAME_RETADDR_OFFSET)))
			{
				UNW_SP(frame) =
				    UNW_FP(frame) + FRAME_RETADDR_OFFSET
#if FRAME_RETADDR_OFFSET < 0
				    -
#else
				    +
#endif
				    sizeof(UNW_PC(frame));
				UNW_FP(frame) = link;
				return 0;
			}
