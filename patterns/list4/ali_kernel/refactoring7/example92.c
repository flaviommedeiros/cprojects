return (n == 0) ? DMAE0_IRQ :
#if defined(DMAE1_IRQ)
				DMAE1_IRQ;
