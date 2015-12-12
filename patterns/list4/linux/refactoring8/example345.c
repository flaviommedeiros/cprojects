static char irq_tab[13][5] __initdata = {
		/*INT    INTA   INTB   INTC   INTD */
		{    45,    45,    45,    45,    45}, /* IdSel 3 21143 PCI1 */
		{    -1,    -1,    -1,    -1,    -1}, /* IdSel 4 unused */
		{    -1,    -1,    -1,    -1,    -1}, /* IdSel 5 unused */
		{    47,    47,    47,    47,    47}, /* IdSel 6 SCSI PCI1 */
		{    -1,    -1,    -1,    -1,    -1}, /* IdSel 7 ISA Bridge */
		{    -1,    -1,    -1,    -1,    -1}, /* IdSel 8 P2P PCI1 */
#if 1
		{    28,    28,    29,    30,    31}, /* IdSel 14 slot 4 PCI2*/
		{    24,    24,    25,    26,    27}, /* IdSel 15 slot 5 PCI2*/
#else
		{    -1,    -1,    -1,    -1,    -1}, /* IdSel 9 unused */
		{    -1,    -1,    -1,    -1,    -1}, /* IdSel 10 unused */
#endif
		{    40,    40,    41,    42,    43}, /* IdSel 11 slot 1 PCI0*/
		{    36,    36,    37,    38,    39}, /* IdSel 12 slot 2 PCI0*/
		{    32,    32,    33,    34,    35}, /* IdSel 13 slot 3 PCI0*/
		{    28,    28,    29,    30,    31}, /* IdSel 14 slot 4 PCI2*/
		{    24,    24,    25,    26,    27}  /* IdSel 15 slot 5 PCI2*/
	};
