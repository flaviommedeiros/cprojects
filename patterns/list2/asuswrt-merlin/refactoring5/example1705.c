#ifdef HAVE_COMPRESSION
if (DB_IS_COMPRESSED(dbp)) {
			dbp->dup_compare = __bam_compress_dupcmp;
			t->compress_dup_compare = __bam_defcmp;
		} else
#endif
			dbp->dup_compare = __bam_defcmp;
