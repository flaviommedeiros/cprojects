#if !BB_MMU
if (!flg_read_only)
#endif
				bb_error_msg("%s: readonly variable", str);
