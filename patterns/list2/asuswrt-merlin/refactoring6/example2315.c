if (card->irq
#ifndef CONFIG_CYZ_INTR
				&& !IS_CYC_Z(*card)
#endif /* CONFIG_CYZ_INTR */
				)
				free_irq(card->irq, card);
