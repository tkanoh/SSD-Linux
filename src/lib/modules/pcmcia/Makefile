#	$ssdlinux: Makefile,v 1.19 2004/08/12 04:10:26 todoroki Exp $

.include <bsd.own.mk>

.ifmake clean
SUBDIR=		include
SUBDIR+=	cb_enabler ds i82365 pcmcia_core
SUBDIR+=	tcic pnp
SUBDIR+=	dummy_cb dummy_cs
SUBDIR+=	3c574_cs 3c575_cb 3c589_cs axnet_cs eepro100_cb epic_cb \
		fmvj18x_cs nmclan_cs pcnet_cs smc91c92_cs tulip_cb xirc2ps_cs
SUBDIR+=	ibmtr_cs
SUBDIR+=	airo airo_cs netwave_cs ray_cs wavelan_cs wvlan_cs \
		hermes orinoco orinoco_cs orinoco_plx
SUBDIR+=	serial_cs serial_cb
SUBDIR+=	parport_cs
SUBDIR+=	ftl_cs iflash2+_mtd iflash2_mtd memory_cs memory_cb sram_mtd
SUBDIR+=	aha152x_cs apa1480_cb fdomain_cs qlogic_cs
SUBDIR+=	pcilynx_cb ohci1394_cb
SUBDIR+=	ide-cs

.else

SUBDIR=		include

.if ${USE_PCMCIA} == "pcmcia-cs"

# modules
SUBDIR+=	cb_enabler ds i82365 pcmcia_core
.if ${TARGET_OPENBLOCKS} == "none"
SUBDIR+=       tcic pnp
.endif

# clients

# Dummy
SUBDIR+=	dummy_cb dummy_cs

# NIC
SUBDIR+=	3c574_cs 3c575_cb 3c589_cs axnet_cs eepro100_cb epic_cb \
		fmvj18x_cs nmclan_cs pcnet_cs smc91c92_cs tulip_cb xirc2ps_cs

# Token-ring
#SUBDIR+=	ibmtr-cs

# wireless
SUBDIR+=	airo airo_cs netwave_cs ray_cs wavelan_cs wvlan_cs \
		hermes orinoco orinoco_cs orinoco_plx

# Moden and serial
SUBDIR+=	serial_cs serial_cb

# Parallel
#SUBDIR+=	parport_cs

# Memory cards
SUBDIR+=	ftl_cs iflash2+_mtd iflash2_mtd memory_cs memory_cb sram_mtd

# SCSI adapters
SUBDIR+=	aha152x_cs qlogic_cs
.if ${KERNEL_VERSION} == "2.4.20"
SUBDIR+=	apa1480_cb
.endif
.if ${TARGET_OPENBLOCKS} == "none"
SUBDIR+=       fdomain_cs
.endif

# IEEE1394
#SUBDIR+=	pcilynx_cb ohci1394_cb

# ATA/IDE
SUBDIR+=	ide-cs

.endif

.endif

.include <bsd.subdir.mk>
