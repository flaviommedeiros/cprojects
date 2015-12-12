static u32 bpf_net_convert_ctx_access(enum bpf_access_type type, int dst_reg,
				      int src_reg, int ctx_off,
				      struct bpf_insn *insn_buf,
				      struct bpf_prog *prog)
{
	struct bpf_insn *insn = insn_buf;

	switch (ctx_off) {
	case offsetof(struct __sk_buff, len):
		BUILD_BUG_ON(FIELD_SIZEOF(struct sk_buff, len) != 4);

		*insn++ = BPF_LDX_MEM(BPF_W, dst_reg, src_reg,
				      offsetof(struct sk_buff, len));
		break;

	case offsetof(struct __sk_buff, protocol):
		BUILD_BUG_ON(FIELD_SIZEOF(struct sk_buff, protocol) != 2);

		*insn++ = BPF_LDX_MEM(BPF_H, dst_reg, src_reg,
				      offsetof(struct sk_buff, protocol));
		break;

	case offsetof(struct __sk_buff, vlan_proto):
		BUILD_BUG_ON(FIELD_SIZEOF(struct sk_buff, vlan_proto) != 2);

		*insn++ = BPF_LDX_MEM(BPF_H, dst_reg, src_reg,
				      offsetof(struct sk_buff, vlan_proto));
		break;

	case offsetof(struct __sk_buff, priority):
		BUILD_BUG_ON(FIELD_SIZEOF(struct sk_buff, priority) != 4);

		if (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_W, dst_reg, src_reg,
					      offsetof(struct sk_buff, priority));
		else
			*insn++ = BPF_LDX_MEM(BPF_W, dst_reg, src_reg,
					      offsetof(struct sk_buff, priority));
		break;

	case offsetof(struct __sk_buff, ingress_ifindex):
		BUILD_BUG_ON(FIELD_SIZEOF(struct sk_buff, skb_iif) != 4);

		*insn++ = BPF_LDX_MEM(BPF_W, dst_reg, src_reg,
				      offsetof(struct sk_buff, skb_iif));
		break;

	case offsetof(struct __sk_buff, ifindex):
		BUILD_BUG_ON(FIELD_SIZEOF(struct net_device, ifindex) != 4);

		*insn++ = BPF_LDX_MEM(bytes_to_bpf_size(FIELD_SIZEOF(struct sk_buff, dev)),
				      dst_reg, src_reg,
				      offsetof(struct sk_buff, dev));
		*insn++ = BPF_JMP_IMM(BPF_JEQ, dst_reg, 0, 1);
		*insn++ = BPF_LDX_MEM(BPF_W, dst_reg, dst_reg,
				      offsetof(struct net_device, ifindex));
		break;

	case offsetof(struct __sk_buff, hash):
		BUILD_BUG_ON(FIELD_SIZEOF(struct sk_buff, hash) != 4);

		*insn++ = BPF_LDX_MEM(BPF_W, dst_reg, src_reg,
				      offsetof(struct sk_buff, hash));
		break;

	case offsetof(struct __sk_buff, mark):
		BUILD_BUG_ON(FIELD_SIZEOF(struct sk_buff, mark) != 4);

		if (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_W, dst_reg, src_reg,
					      offsetof(struct sk_buff, mark));
		else
			*insn++ = BPF_LDX_MEM(BPF_W, dst_reg, src_reg,
					      offsetof(struct sk_buff, mark));
		break;

	case offsetof(struct __sk_buff, pkt_type):
		return convert_skb_access(SKF_AD_PKTTYPE, dst_reg, src_reg, insn);

	case offsetof(struct __sk_buff, queue_mapping):
		return convert_skb_access(SKF_AD_QUEUE, dst_reg, src_reg, insn);

	case offsetof(struct __sk_buff, vlan_present):
		return convert_skb_access(SKF_AD_VLAN_TAG_PRESENT,
					  dst_reg, src_reg, insn);

	case offsetof(struct __sk_buff, vlan_tci):
		return convert_skb_access(SKF_AD_VLAN_TAG,
					  dst_reg, src_reg, insn);

	case offsetof(struct __sk_buff, cb[0]) ...
		offsetof(struct __sk_buff, cb[4]):
		BUILD_BUG_ON(FIELD_SIZEOF(struct qdisc_skb_cb, data) < 20);

		prog->cb_access = 1;
		ctx_off -= offsetof(struct __sk_buff, cb[0]);
		ctx_off += offsetof(struct sk_buff, cb);
		ctx_off += offsetof(struct qdisc_skb_cb, data);
		if (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_W, dst_reg, src_reg, ctx_off);
		else
			*insn++ = BPF_LDX_MEM(BPF_W, dst_reg, src_reg, ctx_off);
		break;

	case offsetof(struct __sk_buff, tc_classid):
		ctx_off -= offsetof(struct __sk_buff, tc_classid);
		ctx_off += offsetof(struct sk_buff, cb);
		ctx_off += offsetof(struct qdisc_skb_cb, tc_classid);
		WARN_ON(type != BPF_WRITE);
		*insn++ = BPF_STX_MEM(BPF_H, dst_reg, src_reg, ctx_off);
		break;

	case offsetof(struct __sk_buff, tc_index):
#ifdef CONFIG_NET_SCHED
		BUILD_BUG_ON(FIELD_SIZEOF(struct sk_buff, tc_index) != 2);

		if (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_H, dst_reg, src_reg,
					      offsetof(struct sk_buff, tc_index));
		else
			*insn++ = BPF_LDX_MEM(BPF_H, dst_reg, src_reg,
					      offsetof(struct sk_buff, tc_index));
		break;
#else
		if (type == BPF_WRITE)
			*insn++ = BPF_MOV64_REG(dst_reg, dst_reg);
		else
			*insn++ = BPF_MOV64_IMM(dst_reg, 0);
		break;
#endif
	}

	return insn - insn_buf;
}
