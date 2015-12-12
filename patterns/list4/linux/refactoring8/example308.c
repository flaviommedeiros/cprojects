static const struct prot_bits section_bits[] = {
#ifdef CONFIG_ARM_LPAE
	{
		.mask	= PMD_SECT_USER,
		.val	= PMD_SECT_USER,
		.set	= "USR",
	}, {
		.mask	= L_PMD_SECT_RDONLY,
		.val	= L_PMD_SECT_RDONLY,
		.set	= "ro",
		.clear	= "RW",
#elif __LINUX_ARM_ARCH__ >= 6
	{
		.mask	= PMD_SECT_APX | PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val	= PMD_SECT_APX | PMD_SECT_AP_WRITE,
		.set	= "    ro",
	}, {
		.mask	= PMD_SECT_APX | PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val	= PMD_SECT_AP_WRITE,
		.set	= "    RW",
	}, {
		.mask	= PMD_SECT_APX | PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val	= PMD_SECT_AP_READ,
		.set	= "USR ro",
	}, {
		.mask	= PMD_SECT_APX | PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val	= PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.set	= "USR RW",
#else /* ARMv4/ARMv5  */
	/* These are approximate */
	{
		.mask   = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val    = 0,
		.set    = "    ro",
	}, {
		.mask   = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val    = PMD_SECT_AP_WRITE,
		.set    = "    RW",
	}, {
		.mask   = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val    = PMD_SECT_AP_READ,
		.set    = "USR ro",
	}, {
		.mask   = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.val    = PMD_SECT_AP_READ | PMD_SECT_AP_WRITE,
		.set    = "USR RW",
#endif
	}, {
		.mask	= PMD_SECT_XN,
		.val	= PMD_SECT_XN,
		.set	= "NX",
		.clear	= "x ",
	}, {
		.mask	= PMD_SECT_S,
		.val	= PMD_SECT_S,
		.set	= "SHD",
		.clear	= "   ",
	},
};

struct pg_level {
	const struct prot_bits *bits;
	size_t num;
	u64 mask;
};

static struct pg_level pg_level[] = {
	{
	}, { /* pgd */
	}, { /* pud */
	}, { /* pmd */
		.bits	= section_bits,
		.num	= ARRAY_SIZE(section_bits),
	}, { /* pte */
		.bits	= pte_bits,
		.num	= ARRAY_SIZE(pte_bits),
	},
};

static void dump_prot(struct pg_state *st, const struct prot_bits *bits, size_t num)
{
	unsigned i;

	for (i = 0; i < num; i++, bits++) {
		const char *s;

		if ((st->current_prot & bits->mask) == bits->val)
			s = bits->set;
		else
			s = bits->clear;

		if (s)
			seq_printf(st->seq, " %s", s);
	}
}

static void note_page(struct pg_state *st, unsigned long addr, unsigned level, u64 val)
{
	static const char units[] = "KMGTPE";
	u64 prot = val & pg_level[level].mask;

	if (!st->level) {
		st->level = level;
		st->current_prot = prot;
		seq_printf(st->seq, "---[ %s ]---\n", st->marker->name);
	} else if (prot != st->current_prot || level != st->level ||
		   addr >= st->marker[1].start_address) {
		const char *unit = units;
		unsigned long delta;

		if (st->current_prot) {
			seq_printf(st->seq, "0x%08lx-0x%08lx   ",
				   st->start_address, addr);

			delta = (addr - st->start_address) >> 10;
			while (!(delta & 1023) && unit[1]) {
				delta >>= 10;
				unit++;
			}
			seq_printf(st->seq, "%9lu%c", delta, *unit);
			if (pg_level[st->level].bits)
				dump_prot(st, pg_level[st->level].bits, pg_level[st->level].num);
			seq_printf(st->seq, "\n");
		}

		if (addr >= st->marker[1].start_address) {
			st->marker++;
			seq_printf(st->seq, "---[ %s ]---\n", st->marker->name);
		}
		st->start_address = addr;
		st->current_prot = prot;
		st->level = level;
	}
}

static void walk_pte(struct pg_state *st, pmd_t *pmd, unsigned long start)
{
	pte_t *pte = pte_offset_kernel(pmd, 0);
	unsigned long addr;
	unsigned i;

	for (i = 0; i < PTRS_PER_PTE; i++, pte++) {
		addr = start + i * PAGE_SIZE;
		note_page(st, addr, 4, pte_val(*pte));
	}
}

static void walk_pmd(struct pg_state *st, pud_t *pud, unsigned long start)
{
	pmd_t *pmd = pmd_offset(pud, 0);
	unsigned long addr;
	unsigned i;

	for (i = 0; i < PTRS_PER_PMD; i++, pmd++) {
		addr = start + i * PMD_SIZE;
		if (pmd_none(*pmd) || pmd_large(*pmd) || !pmd_present(*pmd))
			note_page(st, addr, 3, pmd_val(*pmd));
		else
			walk_pte(st, pmd, addr);

		if (SECTION_SIZE < PMD_SIZE && pmd_large(pmd[1]))
			note_page(st, addr + SECTION_SIZE, 3, pmd_val(pmd[1]));
	}
}

static void walk_pud(struct pg_state *st, pgd_t *pgd, unsigned long start)
{
	pud_t *pud = pud_offset(pgd, 0);
	unsigned long addr;
	unsigned i;

	for (i = 0; i < PTRS_PER_PUD; i++, pud++) {
		addr = start + i * PUD_SIZE;
		if (!pud_none(*pud)) {
			walk_pmd(st, pud, addr);
		} else {
			note_page(st, addr, 2, pud_val(*pud));
		}
	}
}

static void walk_pgd(struct seq_file *m)
{
	pgd_t *pgd = swapper_pg_dir;
	struct pg_state st;
	unsigned long addr;
	unsigned i;

	memset(&st, 0, sizeof(st));
	st.seq = m;
	st.marker = address_markers;

	for (i = 0; i < PTRS_PER_PGD; i++, pgd++) {
		addr = i * PGDIR_SIZE;
		if (!pgd_none(*pgd)) {
			walk_pud(&st, pgd, addr);
		} else {
			note_page(&st, addr, 1, pgd_val(*pgd));
		}
	}

	note_page(&st, 0, 0, 0);
}

static int ptdump_show(struct seq_file *m, void *v)
{
	walk_pgd(m);
	return 0;
}

static int ptdump_open(struct inode *inode, struct file *file)
{
	return single_open(file, ptdump_show, NULL);
}

static const struct file_operations ptdump_fops = {
	.open		= ptdump_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int ptdump_init(void)
{
	struct dentry *pe;
	unsigned i, j;

	for (i = 0; i < ARRAY_SIZE(pg_level); i++)
		if (pg_level[i].bits)
			for (j = 0; j < pg_level[i].num; j++)
				pg_level[i].mask |= pg_level[i].bits[j].mask;

	address_markers[2].start_address = VMALLOC_START;

	pe = debugfs_create_file("kernel_page_tables", 0400, NULL, NULL,
				 &ptdump_fops);
	return pe ? 0 : -ENOMEM;
}
__initcall(ptdump_init);
