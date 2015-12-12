switch (lp->type) {

	case lapShortDDP:
		if (length < ddpSSize) {
			ND_PRINT((ndo, " [|sddp %u]", length));
			return (length);
		}
		sdp = (const struct atShortDDP *)bp;
		ND_PRINT((ndo, "%s.%s",
		    ataddr_string(ndo, 0, lp->src), ddpskt_string(ndo, sdp->srcSkt)));
		ND_PRINT((ndo, " > %s.%s:",
		    ataddr_string(ndo, 0, lp->dst), ddpskt_string(ndo, sdp->dstSkt)));
		bp += ddpSSize;
		length -= ddpSSize;
		hdrlen += ddpSSize;
		ddp_print(ndo, bp, length, sdp->type, 0, lp->src, sdp->srcSkt);
		break;

	case lapDDP:
		if (length < ddpSize) {
			ND_PRINT((ndo, " [|ddp %u]", length));
			return (length);
		}
		dp = (const struct atDDP *)bp;
		snet = EXTRACT_16BITS(&dp->srcNet);
		ND_PRINT((ndo, "%s.%s", ataddr_string(ndo, snet, dp->srcNode),
		    ddpskt_string(ndo, dp->srcSkt)));
		ND_PRINT((ndo, " > %s.%s:",
		    ataddr_string(ndo, EXTRACT_16BITS(&dp->dstNet), dp->dstNode),
		    ddpskt_string(ndo, dp->dstSkt)));
		bp += ddpSize;
		length -= ddpSize;
		hdrlen += ddpSize;
		ddp_print(ndo, bp, length, dp->type, snet, dp->srcNode, dp->srcSkt);
		break;

#ifdef notdef
	case lapKLAP:
		klap_print(bp, length);
		break;
#endif

	default:
		ND_PRINT((ndo, "%d > %d at-lap#%d %u",
		    lp->src, lp->dst, lp->type, length));
		break;
	}
