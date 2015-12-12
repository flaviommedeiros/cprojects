#include "toa.h"

/*
 *	TOA: Address is a new TCP Option
 *	Address include ip+port, Now support IPv4/IPv6
 */


/*
 * Statistics of toa in proc /proc/net/toa_stats
 */

struct toa_stats_entry toa_stats[] = {
	TOA_STAT_ITEM("syn_recv_sock_toa", SYN_RECV_SOCK_TOA_CNT),
	TOA_STAT_ITEM("syn_recv_sock_no_toa", SYN_RECV_SOCK_NO_TOA_CNT),
	TOA_STAT_ITEM("getname_toa_ok_v4", GETNAME_TOA_OK_CNT_V4),
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	TOA_STAT_ITEM("getname_toa_ok_v6", GETNAME_TOA_OK_CNT_V6),
	TOA_STAT_ITEM("getname_toa_ok_mapped", GETNAME_TOA_OK_CNT_MAPPED),
#endif
	TOA_STAT_ITEM("getname_toa_mismatch", GETNAME_TOA_MISMATCH_CNT),
	TOA_STAT_ITEM("getname_toa_bypass", GETNAME_TOA_BYPASS_CNT),
	TOA_STAT_ITEM("getname_toa_empty", GETNAME_TOA_EMPTY_CNT),
	TOA_STAT_END
};

struct toa_stat_mib *ext_stats;
/*
 * Funcs for toa hooks
 */

/* Parse TCP options in skb, try to get client ip, port
 * @param skb [in] received skb, it should be a ack/get-ack packet.
 * @return NULL if we don't get client ip/port;
 *         value of toa_data in ret_ptr if we get client ip/port.
 */
static int get_toa_data(struct sk_buff *skb, void *sk_toa_data)
{
	struct tcphdr *th;
	int length;
	unsigned char *ptr;

	struct toa_data *tdata;

	TOA_DBG("get_toa_data called\n");

	if (NULL != skb) {
		th = tcp_hdr(skb);
		length = (th->doff * 4) - sizeof(struct tcphdr);
		ptr = (unsigned char *) (th + 1);

		while (length > 0) {
			int opcode = *ptr++;
			int opsize;
			switch (opcode) {
			case TCPOPT_EOL:
				return 0;
			case TCPOPT_NOP:	/* Ref: RFC 793 section 3.1 */
				length--;
				continue;
			default:
				opsize = *ptr++;
				if (opsize < 2)	/* "silly options" */
					return 0;
				if (opsize > length)
					/* don't parse partial options */
					return 0;
				if ((TCPOPT_TOA == opcode &&
						TCPOLEN_TOA == opsize)) {
					memset(sk_toa_data, 0,
							sizeof(struct toa_data));
					memcpy(sk_toa_data, ptr - 2,
							TCPOLEN_TOA);
					tdata = (struct toa_data*)sk_toa_data;
					TOA_DBG("find toa data: ip = " \
						"%u.%u.%u.%u, port = %u\n",
						NIPQUAD(tdata->ip),
						ntohs(tdata->port));
					return 1;
				}
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
				else if (TCPOPT_TOA_V6 == opcode &&
						TCPOLEN_TOA_V6 == opsize){
					memset(sk_toa_data, 0,
							sizeof(struct toa_data));
					memcpy(sk_toa_data, ptr - 2,
							TCPOLEN_TOA_V6);
					tdata = (struct toa_data*)sk_toa_data;
					TOA_DBG("find toa data: ipv6 = " \
						"%pI6, port = %u\n",
						&tdata->in6,
						ntohs(tdata->port));
					return 1;
				}
#endif
				ptr += opsize - 2;
				length -= opsize;
			}
		}
	}
	return 0;
}

/* get client ip from socket
 * @param sock [in] the socket to getpeername() or getsockname()
 * @param uaddr [out] the place to put client ip, port
 * @param uaddr_len [out] lenth of @uaddr
 * @peer [in] if(peer), try to get remote address; if(!peer),
 *  try to get local address
 * @return return what the original inet_getname() returns.
 */
static int
inet_getname_toa(struct socket *sock, struct sockaddr *uaddr,
		int *uaddr_len, int peer, int *p_retval)
{
	int retval = *p_retval;
	struct sock *sk = sock->sk;
	struct sockaddr_in *sin = (struct sockaddr_in *) uaddr;
	struct toa_data tdata;

	TOA_DBG("inet_getname_toa called\n");

	/* set our value if need */
	if (retval == 0 && peer) {
		memcpy(&tdata, sk->sk_toa_data, sizeof(tdata));
		if (TCPOPT_TOA == tdata.opcode &&
		    TCPOLEN_TOA == tdata.opsize) {
			TOA_INC_STATS(ext_stats, GETNAME_TOA_OK_CNT_V4);
			TOA_DBG("inet_getname_toa: set new sockaddr, " \
				"ip %u.%u.%u.%u -> %u.%u.%u.%u, port "
				"%u -> %u\n",
				NIPQUAD(sin->sin_addr.s_addr),
				NIPQUAD(tdata.ip), ntohs(sin->sin_port),
				ntohs(tdata.port));
				sin->sin_port = tdata.port;
				sin->sin_addr.s_addr = tdata.ip;
		} else { /* doesn't belong to us */
			TOA_INC_STATS(ext_stats, GETNAME_TOA_MISMATCH_CNT);
			TOA_DBG("inet_getname_toa: invalid toa data, " \
				"ip %u.%u.%u.%u port %u opcode %u "
				"opsize %u\n",
				NIPQUAD(tdata.ip), ntohs(tdata.port),
				tdata.opcode, tdata.opsize);
		}
	} else { /* no need to get client ip */
		TOA_INC_STATS(ext_stats, GETNAME_TOA_EMPTY_CNT);
	}

	return retval;
}

#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
static int
inet6_getname_toa(struct socket *sock, struct sockaddr *uaddr,
		  int *uaddr_len, int peer, int *p_retval)
{
	int retval = *p_retval;
	struct sock *sk = sock->sk;
	struct sockaddr_in6 *sin = (struct sockaddr_in6 *) uaddr;
	struct toa_data tdata;

	TOA_DBG("inet6_getname_toa called\n");

	/* set our value if need */
	if (retval == 0 && peer) {
		memcpy(&tdata, sk->sk_toa_data, sizeof(tdata));
		if (TCPOPT_TOA_V6 == tdata.opcode &&
				TCPOLEN_TOA_V6 == tdata.opsize){
			TOA_INC_STATS(ext_stats, GETNAME_TOA_OK_CNT_V6);
			sin->sin6_port = tdata.port;
			sin->sin6_addr = tdata.in6;
			TOA_DBG("inet6_getname_toa: ipv6 = " \
						"%pI6, port = %u\n",
						&sin->sin6_addr,
						ntohs(sin->sin6_port));
		}else if (TCPOPT_TOA == tdata.opcode &&
				TCPOLEN_TOA == tdata.opsize) {
			TOA_INC_STATS(ext_stats, GETNAME_TOA_OK_CNT_MAPPED);
			sin->sin6_port = tdata.port;
			ipv6_addr_set(&sin->sin6_addr, 0, 0,
					htonl(0x0000FFFF), tdata.ip);
			TOA_DBG("inet6_getname_toa: ipv6_mapped = " \
						"%pI6, port = %u\n",
						&sin->sin6_addr,
						ntohs(sin->sin6_port));
		} else { /* doesn't belong to us */
			TOA_INC_STATS(ext_stats, GETNAME_TOA_MISMATCH_CNT);
		}
	} else { /* no need to get client ip */
		TOA_INC_STATS(ext_stats, GETNAME_TOA_EMPTY_CNT);
	}

	return retval;
}
#endif

/* The three way handshake has completed - we got a valid synack -
 * now create the new socket.
 * We need to save toa data into the new socket.
 * @param sk [out]  the socket
 * @param skb [in] the ack/ack-get packet
 * @param req [in] the open request for this connection
 * @param dst [out] route cache entry
 * @return NULL if fail new socket if succeed.
 */
static struct sock *
tcp_v4_syn_recv_sock_toa(struct sock *sk, struct sk_buff *skb,
			struct request_sock *req, struct dst_entry *dst,
						struct sock **p_newsock)
{
	struct sock *newsock = *p_newsock;

	TOA_DBG("tcp_v4_syn_recv_sock_toa called\n");

	if (!sk || !skb)
		return NULL;

	/* set our value if need */
	if (NULL != newsock) {
		if (get_toa_data(skb, newsock->sk_toa_data))
			TOA_INC_STATS(ext_stats, SYN_RECV_SOCK_TOA_CNT);
		else
			TOA_INC_STATS(ext_stats, SYN_RECV_SOCK_NO_TOA_CNT);
		TOA_DBG("tcp_v4_syn_recv_sock_toa: set " \
			"sk->sk_toa_data\n");
	}
	return newsock;
}

#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
static struct sock *
tcp_v6_syn_recv_sock_toa(struct sock *sk, struct sk_buff *skb,
			 struct request_sock *req, struct dst_entry *dst,
					struct sock **p_newsock)
{
	struct sock *newsock = *p_newsock;

	TOA_DBG("tcp_v6_syn_recv_sock_toa called\n");

	if (!sk || !skb)
		return NULL;

	/* set our value if need */
	if (NULL != newsock) {
		if (get_toa_data(skb, newsock->sk_toa_data))
			TOA_INC_STATS(ext_stats, SYN_RECV_SOCK_TOA_CNT);
		else
			TOA_INC_STATS(ext_stats, SYN_RECV_SOCK_NO_TOA_CNT);
	}
	return newsock;
}
#endif

/*
 * HOOK FUNCS
 */

static struct hooker inet_getname_hooker = {
	.func = inet_getname_toa,
};

static struct hooker inet_tcp_hooker = {
	.func = tcp_v4_syn_recv_sock_toa,
};

#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
static struct hooker inet6_getname_hooker = {
	.func = inet6_getname_toa,
};

static struct hooker inet6_tcp_hooker = {
	.func = tcp_v6_syn_recv_sock_toa,
};
#endif

/* replace the functions with our functions */
static inline int
hook_toa_functions(void)
{
	int ret;

	ret = hooker_install(&inet_stream_ops.getname, &inet_getname_hooker);
	ret |= hooker_install(&ipv4_specific.syn_recv_sock, &inet_tcp_hooker);

#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	ret |= hooker_install(&inet6_stream_ops.getname, &inet6_getname_hooker);
	ret |= hooker_install(&ipv6_specific.syn_recv_sock, &inet6_tcp_hooker);
#endif
	return ret;
}

/* replace the functions to original ones */
static void
unhook_toa_functions(void)
{
	hooker_uninstall(&inet_getname_hooker);
	hooker_uninstall(&inet_tcp_hooker);

#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	hooker_uninstall(&inet6_getname_hooker);
	hooker_uninstall(&inet6_tcp_hooker);
#endif
}

/*
 * Statistics of toa in proc /proc/net/toa_stats
 */
static int toa_stats_show(struct seq_file *seq, void *v)
{
	int i, j, cpu_nr;

	/* print CPU first */
	seq_printf(seq, "                                  ");
	cpu_nr = num_possible_cpus();
	for (i = 0; i < cpu_nr; i++)
		if (cpu_online(i))
			seq_printf(seq, "CPU%d       ", i);
	seq_putc(seq, '\n');

	i = 0;
	while (NULL != toa_stats[i].name) {
		seq_printf(seq, "%-25s:", toa_stats[i].name);
		for (j = 0; j < cpu_nr; j++) {
			if (cpu_online(j)) {
				seq_printf(seq, "%10lu ", *(
					((unsigned long *) per_cpu_ptr(
					ext_stats, j)) + toa_stats[i].entry
					));
			}
		}
		seq_putc(seq, '\n');
		i++;
	}
	return 0;
}

static int toa_stats_seq_open(struct inode *inode, struct file *file)
{
	return single_open(file, toa_stats_show, NULL);
}

static const struct file_operations toa_stats_fops = {
	.owner = THIS_MODULE,
	.open = toa_stats_seq_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

/*
 * TOA module init and destory
 */

/* module init */
static int __init
toa_init(void)
{
	/* alloc statistics array for toa */
	ext_stats = alloc_percpu(struct toa_stat_mib);
	if (!ext_stats)
		return -ENOMEM;

	if (!proc_net_fops_create(&init_net, "toa_stats", 0, &toa_stats_fops)) {
		TOA_INFO("cannot create procfs /proc/net/toa_stats.\n");
		goto err_percpu;
	}

	/* hook funcs for parse and get toa */
	if (hook_toa_functions())
		goto err_proc;

	return 0;

err_proc:
	proc_net_remove(&init_net, "toa_stats");
err_percpu:
	free_percpu(ext_stats);
	return -ENODEV;
}

/* module cleanup*/
static void __exit
toa_exit(void)
{
	unhook_toa_functions();

	proc_net_remove(&init_net, "toa_stats");
	free_percpu(ext_stats);
}

module_init(toa_init);
module_exit(toa_exit);
MODULE_LICENSE("GPL");
