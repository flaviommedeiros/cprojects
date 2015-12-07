#ifdef BCM_NAPI_RXPOLL
if( nrq->cmd == NICE_CMD_GET_RX_NAPI )
#else
		else if( nrq->cmd == NICE_CMD_GET_RX )
#endif
		{
			nrq->nrq_rx = pUmDevice->nice_rx;
			nrq->nrq_ctx = pUmDevice->nice_ctx;
			return 0;
		}
		else if( nrq->cmd == NICE_CMD_GET_SPEED ) {
			if(pDevice->LinkStatus != LM_STATUS_LINK_ACTIVE){
				nrq->nrq_speed = 0;
			}
			else if (pDevice->LineSpeed == LM_LINE_SPEED_1000MBPS) {
				nrq->nrq_speed = SPEED_1000;
			} else if (pDevice->LineSpeed == LM_LINE_SPEED_100MBPS) {
				nrq->nrq_speed = SPEED_100;
			} else if (pDevice->LineSpeed == LM_LINE_SPEED_10MBPS) {
				nrq->nrq_speed = SPEED_100;
			} else {
				nrq->nrq_speed = 0;
			}
			return 0;
		}
		else {
			if (!pUmDevice->opened)
				return -EINVAL;

			switch (nrq->cmd) {
			case NICE_CMD_BLINK_LED:
				if (LM_BlinkLED(pDevice, nrq->nrq_blink_time) ==
					LM_STATUS_SUCCESS) {
					return 0;
				}
				return -EINTR;

			case NICE_CMD_DIAG_SUSPEND:
				b57_suspend_chip(pUmDevice);
				return 0;

			case NICE_CMD_DIAG_RESUME:
				b57_resume_chip(pUmDevice);
				return 0;

			case NICE_CMD_REG_READ:
				if (nrq->nrq_offset >= 0x10000) {
					nrq->nrq_data = LM_RegRdInd(pDevice,
						nrq->nrq_offset);
				}
				else {
					nrq->nrq_data = LM_RegRd(pDevice,
						nrq->nrq_offset);
				}
				return 0;

			case NICE_CMD_REG_WRITE:
				if (nrq->nrq_offset >= 0x10000) {
					LM_RegWrInd(pDevice, nrq->nrq_offset,
						nrq->nrq_data);
				}
				else {
					LM_RegWr(pDevice, nrq->nrq_offset,
						nrq->nrq_data, FALSE);
				}
				return 0;

			case NICE_CMD_REG_READ_DIRECT:
			case NICE_CMD_REG_WRITE_DIRECT:
				if ((nrq->nrq_offset >= 0x10000) ||
					(pDevice->Flags & UNDI_FIX_FLAG)) {
					return -EINVAL;
				}

				if (nrq->cmd == NICE_CMD_REG_READ_DIRECT) {
					nrq->nrq_data = REG_RD_OFFSET(pDevice,
						nrq->nrq_offset);
				}
				else {
					REG_WR_OFFSET(pDevice, nrq->nrq_offset,
							nrq->nrq_data);
				}
				return 0;

			case NICE_CMD_MEM_READ:
				nrq->nrq_data = LM_MemRdInd(pDevice,
					nrq->nrq_offset);
				return 0;

			case NICE_CMD_MEM_WRITE:
				LM_MemWrInd(pDevice, nrq->nrq_offset,
					nrq->nrq_data);
				return 0;

			case NICE_CMD_CFG_READ32:
				pci_read_config_dword(pUmDevice->pdev,
					nrq->nrq_offset, (u32 *)&nrq->nrq_data);
				return 0;

			case NICE_CMD_CFG_READ16:
				pci_read_config_word(pUmDevice->pdev,
					nrq->nrq_offset, (u16 *)&nrq->nrq_data);
				return 0;

			case NICE_CMD_CFG_READ8:
				pci_read_config_byte(pUmDevice->pdev,
					nrq->nrq_offset, (u8 *)&nrq->nrq_data);
				return 0;

			case NICE_CMD_CFG_WRITE32:
				pci_write_config_dword(pUmDevice->pdev,
					nrq->nrq_offset, (u32)nrq->nrq_data);
				return 0;

			case NICE_CMD_CFG_WRITE16:
				pci_write_config_word(pUmDevice->pdev,
					nrq->nrq_offset, (u16)nrq->nrq_data);
				return 0;

			case NICE_CMD_CFG_WRITE8:
				pci_write_config_byte(pUmDevice->pdev,
					nrq->nrq_offset, (u8)nrq->nrq_data);
				return 0;

			case NICE_CMD_RESET:
				bcm5700_reset(dev);
				return 0;

			case NICE_CMD_ENABLE_MAC_LOOPBACK:
				if (pDevice->LoopBackMode != 0) {
					return -EINVAL;
				}

				BCM5700_PHY_LOCK(pUmDevice, flags);
				LM_EnableMacLoopBack(pDevice);
				BCM5700_PHY_UNLOCK(pUmDevice, flags);
				return 0;

			case NICE_CMD_DISABLE_MAC_LOOPBACK:
				if (pDevice->LoopBackMode !=
					LM_MAC_LOOP_BACK_MODE) {
					return -EINVAL;
				}

				BCM5700_PHY_LOCK(pUmDevice, flags);
				LM_DisableMacLoopBack(pDevice);
				BCM5700_PHY_UNLOCK(pUmDevice, flags);
				return 0;

			case NICE_CMD_ENABLE_PHY_LOOPBACK:
				if (pDevice->LoopBackMode != 0) {
					return -EINVAL;
				}

				BCM5700_PHY_LOCK(pUmDevice, flags);
				LM_EnablePhyLoopBack(pDevice);
				BCM5700_PHY_UNLOCK(pUmDevice, flags);
				return 0;

			case NICE_CMD_DISABLE_PHY_LOOPBACK:
				if (pDevice->LoopBackMode !=
					LM_PHY_LOOP_BACK_MODE) {
					return -EINVAL;
				}

				BCM5700_PHY_LOCK(pUmDevice, flags);
				LM_DisablePhyLoopBack(pDevice);
				BCM5700_PHY_UNLOCK(pUmDevice, flags);
				return 0;

			case NICE_CMD_ENABLE_EXT_LOOPBACK:
				if (pDevice->LoopBackMode != 0) {
					return -EINVAL;
				}

				if (pDevice->TbiFlags & ENABLE_TBI_FLAG) {
					if (nrq->nrq_speed != 1000)
						return -EINVAL;
				}
				else {
					if ((nrq->nrq_speed != 1000) &&
						(nrq->nrq_speed != 100) &&
						(nrq->nrq_speed != 10)) {
						return -EINVAL;
					}
				}
				BCM5700_PHY_LOCK(pUmDevice, flags);
				LM_EnableExtLoopBack(pDevice, nrq->nrq_speed);
				BCM5700_PHY_UNLOCK(pUmDevice, flags);
				return 0;

			case NICE_CMD_DISABLE_EXT_LOOPBACK:
				if (pDevice->LoopBackMode !=
					LM_EXT_LOOP_BACK_MODE) {
					return -EINVAL;
				}

				BCM5700_PHY_LOCK(pUmDevice, flags);
				LM_DisableExtLoopBack(pDevice);
				BCM5700_PHY_UNLOCK(pUmDevice, flags);
				return 0;

			case NICE_CMD_INTERRUPT_TEST:
				nrq->nrq_intr_test_result =
					b57_test_intr(pUmDevice);
				return 0;

			case NICE_CMD_LOOPBACK_TEST:
				value = 0;
				switch (nrq->nrq_looptype) {
					case NICE_LOOPBACK_TESTTYPE_EXT:
						if ((nrq->nrq_loopspeed & ~NICE_LOOPBACK_TEST_SPEEDMASK) ||
						   !(nrq->nrq_loopspeed & NICE_LOOPBACK_TEST_SPEEDMASK))
							break;
						switch (nrq->nrq_loopspeed) {
							case NICE_LOOPBACK_TEST_10MBPS:
								value = LM_LINE_SPEED_10MBPS;
								break;
							case NICE_LOOPBACK_TEST_100MBPS:
								value = LM_LINE_SPEED_100MBPS;
								break;
							case NICE_LOOPBACK_TEST_1000MBPS:
								value = LM_LINE_SPEED_1000MBPS;
								break;
						}
						/* Fall through */

					case NICE_LOOPBACK_TESTTYPE_MAC:
					case NICE_LOOPBACK_TESTTYPE_PHY:
						b57_suspend_chip(pUmDevice);
						value = b57_test_loopback(pUmDevice,
						                          nrq->nrq_looptype, value);
						b57_resume_chip(pUmDevice);
						break;
				}

				if (value == 1) {
					/* A '1' indicates success */
					value = 0;
				} else {
					value = -EINTR;
				}

				return value;

			case NICE_CMD_KMALLOC_PHYS: {
#if (LINUX_VERSION_CODE >= 0x020400)
                                dma_addr_t mapping;
                                __u64 cpu_pa;
                                void *ptr;
                                int i;
                                struct page *pg, *last_pg;

                                for (i = 0; i < MAX_MEM2; i++) {
                                        if (pUmDevice->mem_size_list2[i] == 0)
                                                break;
                                }
                                if (i >= MAX_MEM2)
                                        return -EFAULT;
                                ptr = pci_alloc_consistent(pUmDevice->pdev,
                                        nrq->nrq_size, &mapping);
                                if (!ptr) {
                                        return -EFAULT;
                                }
                                pUmDevice->mem_size_list2[i] = nrq->nrq_size;
                                pUmDevice->mem_list2[i] = ptr;
                                pUmDevice->dma_list2[i] = mapping;

                                /* put pci mapping at the beginning of buffer */
                                *((__u64 *) ptr) = (__u64) mapping;

                                /* Probably won't work on some architectures */
                                /* get CPU mapping */
                                cpu_pa = (__u64) virt_to_phys(ptr);
                                pUmDevice->cpu_pa_list2[i] = cpu_pa;
                                nrq->nrq_phys_addr_lo = (__u32) cpu_pa;
                                nrq->nrq_phys_addr_hi = (__u32) (cpu_pa >> 32);

                                pg = virt_to_page(ptr);
                                last_pg = virt_to_page(ptr + nrq->nrq_size - 1);
                                for (; ; pg++) {
#if (LINUX_VERSION_CODE > 0x020500)
                                        SetPageReserved(pg);
#else
                                        mem_map_reserve(pg);
#endif
                                        if (pg == last_pg)
                                                break;
                                }
                                return 0;
#else
                                return -EOPNOTSUPP;
#endif
			}

			case NICE_CMD_KFREE_PHYS: {
                                int i;
                                __u64 cpu_pa;

                                cpu_pa = (__u64) nrq->nrq_phys_addr_lo +
                                        ((__u64) nrq->nrq_phys_addr_hi << 32);
                                for (i = 0; i < MAX_MEM2; i++) {
                                        if (pUmDevice->cpu_pa_list2[i] ==
                                                cpu_pa)
                                        {
                                                break;
                                        }
                                }
                                if (i >= MAX_MEM2)
                                        return -EFAULT;

                                bcm5700_freemem2(pUmDevice, i);
                                return 0;
			}

			case NICE_CMD_SET_WRITE_PROTECT:
				if (nrq->nrq_write_protect)
					pDevice->Flags |= EEPROM_WP_FLAG;
				else
					pDevice->Flags &= ~EEPROM_WP_FLAG;
				return 0;
			case NICE_CMD_GET_STATS_BLOCK: {
				PT3_STATS_BLOCK pStats =
					(PT3_STATS_BLOCK)pDevice->pStatsBlkVirt;
				if (mm_copy_to_user(nrq->nrq_stats_useraddr,
					pStats, nrq->nrq_stats_size)) {
					return -EFAULT;
				}
				return 0;
			}
			case NICE_CMD_CLR_STATS_BLOCK: {
				int j;
				PT3_STATS_BLOCK pStats =
					(PT3_STATS_BLOCK)pDevice->pStatsBlkVirt;

				memset(pStats, 0, sizeof(T3_STATS_BLOCK));
				if (T3_ASIC_REV(pDevice->ChipRevId) ==
					T3_ASIC_REV_5705) {
					return 0;
				}
				for(j = 0x0300; j < 0x0b00; j = j + 4) {
					MEM_WR_OFFSET(pDevice, j, 0);
				}

				return 0;
			}

			}
		}
