switch(popt->index) {
            case QEMU_OPTION_M:
                machine = find_machine(optarg);
                if (!machine) {
                    QEMUMachine *m;
                    printf("Supported machines are:\n");
                    for(m = first_machine; m != NULL; m = m->next) {
                        printf("%-10s %s%s\n",
                               m->name, m->desc,
                               m->is_default ? " (default)" : "");
                    }
                    if (*optarg != '?') {
                        PANIC("Invalid machine parameter: %s",
                                          optarg);
                    } else {
                        QEMU_EXIT(0);
                    }
                }
                break;
            case QEMU_OPTION_cpu:
                /* hw initialization will check this */
                if (*optarg == '?') {
/* XXX: implement xxx_cpu_list for targets that still miss it */
#if defined(cpu_list)
                    cpu_list(stdout, &fprintf);
#endif
                    QEMU_EXIT(0);
                } else {
                    cpu_model = optarg;
                }
                break;
            case QEMU_OPTION_initrd:
                initrd_filename = optarg;
                break;
            case QEMU_OPTION_hda:
                if (cyls == 0)
                    hda_opts = drive_add(optarg, HD_ALIAS, 0);
                else
                    hda_opts = drive_add(optarg, HD_ALIAS
			     ",cyls=%d,heads=%d,secs=%d%s",
                             0, cyls, heads, secs,
                             translation == BIOS_ATA_TRANSLATION_LBA ?
                                 ",trans=lba" :
                             translation == BIOS_ATA_TRANSLATION_NONE ?
                                 ",trans=none" : "");
                 break;
            case QEMU_OPTION_hdb:
                hdb_opts = drive_add(optarg, HD_ALIAS, 1);
                break;

            case QEMU_OPTION_hdc:
            case QEMU_OPTION_hdd:
                drive_add(optarg, HD_ALIAS, popt->index - QEMU_OPTION_hda);
                break;
            case QEMU_OPTION_drive:
                drive_add(NULL, "%s", optarg);
	        break;
            case QEMU_OPTION_mtdblock:
                drive_add(optarg, MTD_ALIAS);
                break;
            case QEMU_OPTION_sd:
                drive_add(optarg, SD_ALIAS);
                break;
            case QEMU_OPTION_pflash:
                drive_add(optarg, PFLASH_ALIAS);
                break;
            case QEMU_OPTION_snapshot:
                snapshot = 1;
                break;
            case QEMU_OPTION_hdachs:
                {
                    const char *p;
                    p = optarg;
                    cyls = strtol(p, (char **)&p, 0);
                    if (cyls < 1 || cyls > 16383)
                        goto chs_fail;
                    if (*p != ',')
                        goto chs_fail;
                    p++;
                    heads = strtol(p, (char **)&p, 0);
                    if (heads < 1 || heads > 16)
                        goto chs_fail;
                    if (*p != ',')
                        goto chs_fail;
                    p++;
                    secs = strtol(p, (char **)&p, 0);
                    if (secs < 1 || secs > 63)
                        goto chs_fail;
                    if (*p == ',') {
                        p++;
                        if (!strcmp(p, "none"))
                            translation = BIOS_ATA_TRANSLATION_NONE;
                        else if (!strcmp(p, "lba"))
                            translation = BIOS_ATA_TRANSLATION_LBA;
                        else if (!strcmp(p, "auto"))
                            translation = BIOS_ATA_TRANSLATION_AUTO;
                        else
                            goto chs_fail;
                    } else if (*p != '\0') {
                    chs_fail:
                        PANIC("qemu: invalid physical CHS format");
                    }
		    if (hda_opts != NULL) {
                        char num[16];
                        snprintf(num, sizeof(num), "%d", cyls);
                        qemu_opt_set(hda_opts, "cyls", num);
                        snprintf(num, sizeof(num), "%d", heads);
                        qemu_opt_set(hda_opts, "heads", num);
                        snprintf(num, sizeof(num), "%d", secs);
                        qemu_opt_set(hda_opts, "secs", num);
                        if (translation == BIOS_ATA_TRANSLATION_LBA)
                            qemu_opt_set(hda_opts, "trans", "lba");
                        if (translation == BIOS_ATA_TRANSLATION_NONE)
                            qemu_opt_set(hda_opts, "trans", "none");
                    }
                }
                break;
            case QEMU_OPTION_numa:
                if (nb_numa_nodes >= MAX_NODES) {
                    PANIC("qemu: too many NUMA nodes");
                }
                numa_add(optarg);
                break;
            case QEMU_OPTION_nographic:
                display_type = DT_NOGRAPHIC;
                break;
#ifdef CONFIG_CURSES
            case QEMU_OPTION_curses:
                display_type = DT_CURSES;
                break;
#endif
            case QEMU_OPTION_portrait:
                graphic_rotate = 1;
                break;
            case QEMU_OPTION_kernel:
                kernel_filename = optarg;
                break;
            case QEMU_OPTION_append:
                kernel_cmdline = optarg;
                break;
            case QEMU_OPTION_cdrom:
                drive_add(optarg, CDROM_ALIAS);
                break;
            case QEMU_OPTION_boot:
                boot_devices = optarg;
                /* We just do some generic consistency checks */
                {
                    /* Could easily be extended to 64 devices if needed */
                    const char *p;

                    boot_devices_bitmap = 0;
                    for (p = boot_devices; *p != '\0'; p++) {
                        /* Allowed boot devices are:
                         * a b     : floppy disk drives
                         * c ... f : IDE disk drives
                         * g ... m : machine implementation dependant drives
                         * n ... p : network devices
                         * It's up to each machine implementation to check
                         * if the given boot devices match the actual hardware
                         * implementation and firmware features.
                         */
                        if (*p < 'a' || *p > 'q') {
                            PANIC("Invalid boot device '%c'", *p);
                        }
                        if (boot_devices_bitmap & (1 << (*p - 'a'))) {
                            PANIC(
                                    "Boot device '%c' was given twice",*p);
                        }
                        boot_devices_bitmap |= 1 << (*p - 'a');
                    }
                }
                break;
            case QEMU_OPTION_fda:
            case QEMU_OPTION_fdb:
                drive_add(optarg, FD_ALIAS, popt->index - QEMU_OPTION_fda);
                break;
#ifdef TARGET_I386
            case QEMU_OPTION_no_fd_bootchk:
                fd_bootchk = 0;
                break;
#endif
            case QEMU_OPTION_net:
                if (nb_net_clients >= MAX_NET_CLIENTS) {
                    PANIC("qemu: too many network clients");
                }
                net_clients[nb_net_clients] = optarg;
                nb_net_clients++;
                break;
#ifdef CONFIG_SLIRP
            case QEMU_OPTION_tftp:
		tftp_prefix = optarg;
                break;
            case QEMU_OPTION_bootp:
                bootp_filename = optarg;
                break;
            case QEMU_OPTION_redir:
                net_slirp_redir(NULL, optarg, NULL);
                break;
#endif
            case QEMU_OPTION_bt:
                if (nb_bt_opts >= MAX_BT_CMDLINE) {
                    PANIC("qemu: too many bluetooth options");
                }
                bt_opts[nb_bt_opts++] = optarg;
                break;
#ifdef HAS_AUDIO
            case QEMU_OPTION_audio_help:
                AUD_help ();
                QEMU_EXIT(0);
                break;
            case QEMU_OPTION_soundhw:
                select_soundhw (optarg);
                break;
#endif
            case QEMU_OPTION_h:
                qemu_help(0);
                break;
            case QEMU_OPTION_version:
                version();
                QEMU_EXIT(0);
                break;
            case QEMU_OPTION_m: {
                uint64_t value;
                char *ptr;

                value = strtoul(optarg, &ptr, 10);
                switch (*ptr) {
                case 0: case 'M': case 'm':
                    value <<= 20;
                    break;
                case 'G': case 'g':
                    value <<= 30;
                    break;
                default:
                    PANIC("qemu: invalid ram size: %s", optarg);
                }

                /* On 32-bit hosts, QEMU is limited by virtual address space */
                if (value > (2047 << 20)
#ifndef CONFIG_KQEMU
                    && HOST_LONG_BITS == 32
#endif
                    ) {
                    PANIC("qemu: at most 2047 MB RAM can be simulated");
                }
                if (value != (uint64_t)(ram_addr_t)value) {
                    PANIC("qemu: ram size too large");
                }
                ram_size = value;
                break;
            }
            case QEMU_OPTION_d:
                {
                    int mask;
                    const CPULogItem *item;

                    mask = cpu_str_to_log_mask(optarg);
                    if (!mask) {
                        printf("Log items (comma separated):\n");
                        for(item = cpu_log_items; item->mask != 0; item++) {
                            printf("%-10s %s\n", item->name, item->help);
                        }
                        PANIC("Invalid parameter -d=%s", optarg);
                    }
                    cpu_set_log(mask);
                }
                break;
            case QEMU_OPTION_s:
                gdbstub_dev = "tcp::" DEFAULT_GDBSTUB_PORT;
                break;
            case QEMU_OPTION_gdb:
                gdbstub_dev = optarg;
                break;
            case QEMU_OPTION_L:
                data_dir = optarg;
                break;
            case QEMU_OPTION_bios:
                bios_name = optarg;
                break;
            case QEMU_OPTION_singlestep:
                singlestep = 1;
                break;
            case QEMU_OPTION_S:
                autostart = 0;
                break;
#ifndef _WIN32
	    case QEMU_OPTION_k:
		keyboard_layout = optarg;
		break;
#endif
            case QEMU_OPTION_localtime:
                rtc_utc = 0;
                break;
            case QEMU_OPTION_vga:
                select_vgahw (optarg);
                break;
#if defined(TARGET_PPC) || defined(TARGET_SPARC)
            case QEMU_OPTION_g:
                {
                    const char *p;
                    int w, h, depth;
                    p = optarg;
                    w = strtol(p, (char **)&p, 10);
                    if (w <= 0) {
                    graphic_error:
                        PANIC("qemu: invalid resolution or depth");
                    }
                    if (*p != 'x')
                        goto graphic_error;
                    p++;
                    h = strtol(p, (char **)&p, 10);
                    if (h <= 0)
                        goto graphic_error;
                    if (*p == 'x') {
                        p++;
                        depth = strtol(p, (char **)&p, 10);
                        if (depth != 8 && depth != 15 && depth != 16 &&
                            depth != 24 && depth != 32)
                            goto graphic_error;
                    } else if (*p == '\0') {
                        depth = graphic_depth;
                    } else {
                        goto graphic_error;
                    }

                    graphic_width = w;
                    graphic_height = h;
                    graphic_depth = depth;
                }
                break;
#endif
            case QEMU_OPTION_echr:
                {
                    char *r;
                    term_escape_char = strtol(optarg, &r, 0);
                    if (r == optarg)
                        printf("Bad argument to echr\n");
                    break;
                }
            case QEMU_OPTION_monitor:
                monitor_device = optarg;
                break;
            case QEMU_OPTION_serial:
                if (serial_device_index >= MAX_SERIAL_PORTS) {
                    PANIC("qemu: too many serial ports");
                }
                serial_devices[serial_device_index] = optarg;
                serial_device_index++;
                break;
            case QEMU_OPTION_watchdog:
                i = select_watchdog(optarg);
                if (i > 0) {
                    if (i == 1) {
                        PANIC("Invalid watchdog parameter: %s",
                                          optarg);
                    } else {
                        QEMU_EXIT(0);
                    }
                }
                break;
            case QEMU_OPTION_watchdog_action:
                if (select_watchdog_action(optarg) == -1) {
                    PANIC("Unknown -watchdog-action parameter");
                }
                break;
            case QEMU_OPTION_virtiocon:
                if (virtio_console_index >= MAX_VIRTIO_CONSOLES) {
                    PANIC("qemu: too many virtio consoles");
                }
                virtio_consoles[virtio_console_index] = optarg;
                virtio_console_index++;
                break;
            case QEMU_OPTION_parallel:
                if (parallel_device_index >= MAX_PARALLEL_PORTS) {
                    PANIC("qemu: too many parallel ports");
                }
                parallel_devices[parallel_device_index] = optarg;
                parallel_device_index++;
                break;
            case QEMU_OPTION_loadvm:
                loadvm = optarg;
                break;
            case QEMU_OPTION_savevm_on_exit:
                savevm_on_exit = optarg;
                break;
            case QEMU_OPTION_full_screen:
                full_screen = 1;
                break;
#ifdef CONFIG_SDL
            case QEMU_OPTION_no_frame:
                no_frame = 1;
                break;
            case QEMU_OPTION_alt_grab:
                alt_grab = 1;
                break;
            case QEMU_OPTION_no_quit:
                no_quit = 1;
                break;
            case QEMU_OPTION_sdl:
                display_type = DT_SDL;
                break;
#endif
            case QEMU_OPTION_pidfile:
                pid_file = optarg;
                break;
#ifdef TARGET_I386
            case QEMU_OPTION_win2k_hack:
                win2k_install_hack = 1;
                break;
            case QEMU_OPTION_rtc_td_hack:
                rtc_td_hack = 1;
                break;
#ifndef CONFIG_ANDROID
            case QEMU_OPTION_acpitable:
                if(acpi_table_add(optarg) < 0) {
                    PANIC("Wrong acpi table provided");
                }
                break;
#endif
            case QEMU_OPTION_smbios:
                do_smbios_option(optarg);
                break;
#endif
#ifdef CONFIG_KVM
            case QEMU_OPTION_enable_kvm:
                kvm_allowed = 1;
                break;
            case QEMU_OPTION_disable_kvm:
                kvm_allowed = 0;
                break;
#endif /* CONFIG_KVM */
            case QEMU_OPTION_usb:
                usb_enabled = 1;
                break;
            case QEMU_OPTION_usbdevice:
                usb_enabled = 1;
                if (usb_devices_index >= MAX_USB_CMDLINE) {
                    PANIC("Too many USB devices");
                }
                usb_devices[usb_devices_index] = optarg;
                usb_devices_index++;
                break;
            case QEMU_OPTION_smp:
                smp_cpus = atoi(optarg);
                if (smp_cpus < 1) {
                    PANIC("Invalid number of CPUs");
                }
                break;
	    case QEMU_OPTION_vnc:
                display_type = DT_VNC;
		vnc_display = optarg;
		break;
#ifdef TARGET_I386
            case QEMU_OPTION_no_acpi:
                acpi_enabled = 0;
                break;
            case QEMU_OPTION_no_hpet:
                no_hpet = 1;
                break;
            case QEMU_OPTION_no_virtio_balloon:
                no_virtio_balloon = 1;
                break;
#endif
            case QEMU_OPTION_no_reboot:
                no_reboot = 1;
                break;
            case QEMU_OPTION_no_shutdown:
                no_shutdown = 1;
                break;
            case QEMU_OPTION_show_cursor:
                cursor_hide = 0;
                break;
            case QEMU_OPTION_uuid:
                if(qemu_uuid_parse(optarg, qemu_uuid) < 0) {
                    PANIC("Fail to parse UUID string. Wrong format.");
                }
                break;
	    case QEMU_OPTION_option_rom:
		if (nb_option_roms >= MAX_OPTION_ROMS) {
		    PANIC("Too many option ROMs");
		}
		option_rom[nb_option_roms] = optarg;
		nb_option_roms++;
		break;
#if defined(TARGET_ARM) || defined(TARGET_M68K)
            case QEMU_OPTION_semihosting:
                semihosting_enabled = 1;
                break;
#endif
            case QEMU_OPTION_name:
                qemu_name = optarg;
                break;
#if defined(TARGET_SPARC) || defined(TARGET_PPC)
            case QEMU_OPTION_prom_env:
                if (nb_prom_envs >= MAX_PROM_ENVS) {
                    PANIC("Too many prom variables");
                }
                prom_envs[nb_prom_envs] = optarg;
                nb_prom_envs++;
                break;
#endif
#ifdef TARGET_ARM
            case QEMU_OPTION_old_param:
                old_param = 1;
                break;
#endif
            case QEMU_OPTION_clock:
                configure_alarms(optarg);
                break;
            case QEMU_OPTION_startdate:
                {
                    struct tm tm;
                    time_t rtc_start_date = 0;
                    if (!strcmp(optarg, "now")) {
                        rtc_date_offset = -1;
                    } else {
                        if (sscanf(optarg, "%d-%d-%dT%d:%d:%d",
                               &tm.tm_year,
                               &tm.tm_mon,
                               &tm.tm_mday,
                               &tm.tm_hour,
                               &tm.tm_min,
                               &tm.tm_sec) == 6) {
                            /* OK */
                        } else if (sscanf(optarg, "%d-%d-%d",
                                          &tm.tm_year,
                                          &tm.tm_mon,
                                          &tm.tm_mday) == 3) {
                            tm.tm_hour = 0;
                            tm.tm_min = 0;
                            tm.tm_sec = 0;
                        } else {
                            goto date_fail;
                        }
                        tm.tm_year -= 1900;
                        tm.tm_mon--;
                        rtc_start_date = mktimegm(&tm);
                        if (rtc_start_date == -1) {
                        date_fail:
                            PANIC("Invalid date format. Valid format are:\n"
                                    "'now' or '2006-06-17T16:01:21' or '2006-06-17'");
                        }
                        rtc_date_offset = time(NULL) - rtc_start_date;
                    }
                }
                break;

            /* -------------------------------------------------------*/
            /* User mode network stack restrictions */
            case QEMU_OPTION_drop_udp:
                slirp_drop_udp();
                break;
            case QEMU_OPTION_drop_tcp:
                slirp_drop_tcp();
                break;
            case QEMU_OPTION_allow_tcp:
                slirp_allow(optarg, IPPROTO_TCP);
                break;
            case QEMU_OPTION_allow_udp:
                slirp_allow(optarg, IPPROTO_UDP);
                break;
             case QEMU_OPTION_drop_log:
                {
                    FILE* drop_log_fd;
                    drop_log_filename = optarg;
                    drop_log_fd = fopen(optarg, "w+");

                    if (!drop_log_fd) {
                        fprintf(stderr, "Cannot open drop log: %s\n", optarg);
                        exit(1);
                    }

                    slirp_drop_log_fd(drop_log_fd);
                }
                break;

            case QEMU_OPTION_dns_log:
                {
                    FILE* dns_log_fd;
                    dns_log_filename = optarg;
                    dns_log_fd = fopen(optarg, "wb+");

                    if (dns_log_fd == NULL) {
                        fprintf(stderr, "Cannot open dns log: %s\n", optarg);
                        exit(1);
                    }

                    slirp_dns_log_fd(dns_log_fd);
                }
                break;


            case QEMU_OPTION_max_dns_conns:
                {
                    int max_dns_conns = 0;
                    if (parse_int(optarg, &max_dns_conns)) {
                      fprintf(stderr,
                              "qemu: syntax: -max-dns-conns max_connections\n");
                      exit(1);
                    }
                    if (max_dns_conns <= 0 ||  max_dns_conns == LONG_MAX) {
                      fprintf(stderr,
                              "Invalid arg for max dns connections: %s\n",
                              optarg);
                      exit(1);
                    }
                    slirp_set_max_dns_conns(max_dns_conns);
                }
                break;

            case QEMU_OPTION_net_forward:
                net_slirp_forward(optarg);
                break;
            case QEMU_OPTION_net_forward_tcp2sink:
                {
                    SockAddress saddr;

                    if (parse_host_port(&saddr, optarg)) {
                        fprintf(stderr,
                                "Invalid ip/port %s for "
                                "-forward-dropped-tcp2sink. "
                                "We expect 'sink_ip:sink_port'\n",
                                optarg);
                        exit(1);
                    }
                    slirp_forward_dropped_tcp2sink(saddr.u.inet.address,
                                                   saddr.u.inet.port);
                }
                break;
            /* -------------------------------------------------------*/

            case QEMU_OPTION_tb_size:
                tb_size = strtol(optarg, NULL, 0);
                if (tb_size < 0)
                    tb_size = 0;
                break;
            case QEMU_OPTION_icount:
                icount_option = optarg;
                break;
            case QEMU_OPTION_incoming:
                incoming = optarg;
                break;
#ifdef CONFIG_XEN
            case QEMU_OPTION_xen_domid:
                xen_domid = atoi(optarg);
                break;
            case QEMU_OPTION_xen_create:
                xen_mode = XEN_CREATE;
                break;
            case QEMU_OPTION_xen_attach:
                xen_mode = XEN_ATTACH;
                break;
#endif


            case QEMU_OPTION_mic:
                audio_input_source = (char*)optarg;
                break;
#ifdef CONFIG_TRACE
            case QEMU_OPTION_trace:
                trace_filename = optarg;
                tracing = 1;
                break;
#if 0
            case QEMU_OPTION_trace_miss:
                trace_cache_miss = 1;
                break;
            case QEMU_OPTION_trace_addr:
                trace_all_addr = 1;
                break;
#endif
            case QEMU_OPTION_tracing:
                if (strcmp(optarg, "off") == 0)
                    tracing = 0;
                else if (strcmp(optarg, "on") == 0 && trace_filename)
                    tracing = 1;
                else {
                    PANIC("Unexpected option to -tracing ('%s')",
                            optarg);
                }
                break;
#if 0
            case QEMU_OPTION_dcache_load_miss:
                dcache_load_miss_penalty = atoi(optarg);
                break;
            case QEMU_OPTION_dcache_store_miss:
                dcache_store_miss_penalty = atoi(optarg);
                break;
#endif
#endif
#ifdef CONFIG_NAND
            case QEMU_OPTION_nand:
                nand_add_dev(optarg);
                break;

#endif
            case QEMU_OPTION_disable_hax:
                hax_disabled = 1;
                break;
            case QEMU_OPTION_android_ports:
                android_op_ports = (char*)optarg;
                break;

            case QEMU_OPTION_android_port:
                android_op_port = (char*)optarg;
                break;

            case QEMU_OPTION_android_report_console:
                android_op_report_console = (char*)optarg;
                break;

            case QEMU_OPTION_http_proxy:
                op_http_proxy = (char*)optarg;
                break;

            case QEMU_OPTION_charmap:
                op_charmap_file = (char*)optarg;
                break;

            case QEMU_OPTION_android_hw:
                android_op_hwini = (char*)optarg;
                break;

            case QEMU_OPTION_dns_server:
                android_op_dns_server = (char*)optarg;
                break;

            case QEMU_OPTION_radio:
                android_op_radio = (char*)optarg;
                break;

            case QEMU_OPTION_gps:
                android_op_gps = (char*)optarg;
                break;

            case QEMU_OPTION_audio:
                android_op_audio = (char*)optarg;
                break;

            case QEMU_OPTION_cpu_delay:
                android_op_cpu_delay = (char*)optarg;
                break;

            case QEMU_OPTION_show_kernel:
                android_kmsg_init(ANDROID_KMSG_PRINT_MESSAGES);
                break;

#ifdef CONFIG_NAND_LIMITS
            case QEMU_OPTION_nand_limits:
                android_op_nand_limits = (char*)optarg;
                break;
#endif  // CONFIG_NAND_LIMITS

            case QEMU_OPTION_netspeed:
                android_op_netspeed = (char*)optarg;
                break;

            case QEMU_OPTION_netdelay:
                android_op_netdelay = (char*)optarg;
                break;

            case QEMU_OPTION_netfast:
                android_op_netfast = 1;
                break;

            case QEMU_OPTION_tcpdump:
                android_op_tcpdump = (char*)optarg;
                break;

            case QEMU_OPTION_boot_property:
                boot_property_parse_option((char*)optarg);
                break;

            case QEMU_OPTION_lcd_density:
                android_op_lcd_density = (char*)optarg;
                break;

            case QEMU_OPTION_ui_port:
                android_op_ui_port = (char*)optarg;
                break;

            case QEMU_OPTION_ui_settings:
                android_op_ui_settings = (char*)optarg;
                break;

            case QEMU_OPTION_audio_test_out:
                android_audio_test_start_out();
                break;

            case QEMU_OPTION_android_avdname:
                android_op_avd_name = (char*)optarg;
                break;

            case QEMU_OPTION_timezone:
                if (timezone_set((char*)optarg)) {
                    fprintf(stderr, "emulator: it seems the timezone '%s' is not in zoneinfo format\n",
                            (char*)optarg);
                }
                break;

#ifdef CONFIG_MEMCHECK
            case QEMU_OPTION_android_memcheck:
                android_op_memcheck = (char*)optarg;
                /* This will set ro.kernel.memcheck system property
                 * to memcheck's tracing flags. */
                stralloc_add_format(kernel_config, " memcheck=%s", android_op_memcheck);
                break;
#endif // CONFIG_MEMCHECK

            case QEMU_OPTION_snapshot_no_time_update:
                android_snapshot_update_time = 0;
                break;

            case QEMU_OPTION_list_webcam:
                android_list_web_cameras();
                exit(0);

            default:
                os_parse_cmd_args(popt->index, optarg);
            }
