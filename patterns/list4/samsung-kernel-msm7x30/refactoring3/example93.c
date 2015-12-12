switch (type) {
#ifdef CONFIG_SPI_MASTER
	case MCP_TYPE_S08:
		mcp->ops = &mcp23s08_ops;
		mcp->chip.ngpio = 8;
		mcp->chip.label = "mcp23s08";
		break;

	case MCP_TYPE_S17:
		mcp->ops = &mcp23s17_ops;
		mcp->chip.ngpio = 16;
		mcp->chip.label = "mcp23s17";
		break;
#endif /* CONFIG_SPI_MASTER */

#ifdef CONFIG_I2C
	case MCP_TYPE_008:
		mcp->ops = &mcp23008_ops;
		mcp->chip.ngpio = 8;
		mcp->chip.label = "mcp23008";
		break;

	case MCP_TYPE_017:
		mcp->ops = &mcp23017_ops;
		mcp->chip.ngpio = 16;
		mcp->chip.label = "mcp23017";
		break;
#endif /* CONFIG_I2C */

	default:
		dev_err(dev, "invalid device type (%d)\n", type);
		return -EINVAL;
	}
