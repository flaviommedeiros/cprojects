switch (ctx->val_bytes) {
		case 1:
			*(u8 *)val = readb(ctx->regs + offset);
			break;
		case 2:
			*(u16 *)val = readw(ctx->regs + offset);
			break;
		case 4:
			*(u32 *)val = readl(ctx->regs + offset);
			break;
#ifdef CONFIG_64BIT
		case 8:
			*(u64 *)val = readq(ctx->regs + offset);
			break;
#endif
		default:
			/* Should be caught by regmap_mmio_check_config */
			BUG();
		}
