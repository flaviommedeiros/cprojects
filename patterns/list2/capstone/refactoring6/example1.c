if (
#ifndef CAPSTONE_X86_REDUCE
						Opcode != X86_BLENDPSrri &&
						Opcode != X86_BLENDPDrri &&
						Opcode != X86_PBLENDWrri &&
						Opcode != X86_MPSADBWrri &&
						Opcode != X86_DPPSrri &&
						Opcode != X86_DPPDrri &&
						Opcode != X86_INSERTPSrr &&
						Opcode != X86_VBLENDPSYrri &&
						Opcode != X86_VBLENDPSYrmi &&
						Opcode != X86_VBLENDPDYrri &&
						Opcode != X86_VBLENDPDYrmi &&
						Opcode != X86_VPBLENDWrri &&
						Opcode != X86_VMPSADBWrri &&
						Opcode != X86_VDPPSYrri &&
						Opcode != X86_VDPPSYrmi &&
						Opcode != X86_VDPPDrri &&
						Opcode != X86_VINSERTPSrr &&
#endif
						Opcode != X86_INT)
						if(immediate & 0x80)
							immediate |= ~(0xffull);
