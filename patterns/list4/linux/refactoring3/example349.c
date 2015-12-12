switch (ctx->val_bytes) {
		case 1:
			writeb(*(u8 *)val, ctx->regs + offset);
			break;
		case 2:
			writew(*(u16 *)val, ctx->regs + offset);
			break;
		case 4:
			writel(*(u32 *)val, ctx->regs + offset);
			break;
#ifdef CONFIG_64BIT
		case 8:
			writeq(*(u64 *)val, ctx->regs + offset);
			break;
#endif
		default:
			/* Should be caught by regmap_mmio_check_config */
			BUG();
		}
