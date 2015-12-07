#ifdef HNDCTF
if (!manip_pkt(target.dst.protonum, skb, 0, &target, mtype))
                        return NF_DROP;
