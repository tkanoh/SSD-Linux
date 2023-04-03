/*	$ssdlinux: flashcfg.c,v 1.18 2004/11/02 02:19:36 todoroki Exp $	*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <linux/mtd/mtd.h>

extern char **environ;
/* some variables used in getopt (3) */
extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;

#define	KILO_BYTE	1024
#define	MEGA_BYTE	(1024*1024)
#define	SECT1_SIZE	(8*KILO_BYTE)
#define	SECT2_SIZE	(64*KILO_BYTE)
#define	FLASH_SIZE	(8*MEGA_BYTE)
#define	MAGIC		0x0052504F

#define STATUS_COL	50

typedef struct nvram_boot_t {
	char boot_magic[2];
	char boot_dev[14];
} nvram_boot_t;

nvram_boot_t nvram_boot;

#define	NVRAM_BOOT_OFF	256

typedef struct boot_block_t {
	unsigned long	magic;
	unsigned long	dest;
	unsigned long	num_512blocks;
	unsigned long	debug_flag;
	unsigned long	entry_point;
	unsigned long	reserved[3];
} boot_block_t;

boot_block_t * pboot_block;

unsigned short *membase;

void flash_set_bootdev(char *);
void flash_prog_kern(char *);
void flash_save_param(char *);
void flash_delete_param(void);
void flash_extract_param(void);

/*#define DEBUG*/
#define ENABLE_MULTIBOOT

void
usage()
{
	fprintf(stderr, "usage: flashcfg                Show this.\n");
#ifdef	ENABLE_MULTIBOOT
	fprintf(stderr, "       flashcfg -c [rootdev]   Change root file system [initrd|harddisk|hda1-4]\n");
#else
	fprintf(stderr, "       flashcfg -c [rootdev]   Change root file system [initrd|harddisk]\n");
#endif
	fprintf(stderr, "       flashcfg -f boot_image  Load boot image to flash\n");
	fprintf(stderr, "       flashcfg -s list_file   Save files to flash\n");
	fprintf(stderr, "       flashcfg -x             Restore files from flash\n");
	fprintf(stderr, "       flashcfg -d             Delete saved files from flash\n");
	fprintf(stderr, "       flashcfg -h             Show this.\n");
}

int
main(int argc, char *argv[])
{
	FILE *fp;
	int i, f;
	char *boot_dev;

	if (getuid()) {
		fprintf(stderr, "must be super user\n");
		return (0);
	}

	while ((i = getopt(argc, argv, "c:f:s:xdh")) != -1) {
		switch (i) {
		case 'c':
			if (strcmp(optarg, "harddisk") == 0)
				boot_dev = "\001\007hda1";
			else if (strcmp(optarg, "initrd") == 0)
				boot_dev = "\002\007ram";
#ifdef  ENABLE_MULTIBOOT
			else if (strcmp(optarg, "hda1") == 0)
				boot_dev = "\001\007hda1";
			else if (strcmp(optarg, "hda2") == 0)
				boot_dev = "\001\007hda2";
			else if (strcmp(optarg, "hda3") == 0)
				boot_dev = "\001\007hda3";
			else if (strcmp(optarg, "hda4") == 0)
				boot_dev = "\001\007hda4";
#endif
			else {
				fprintf(stderr, "invalid option %s\n",
					optarg);
				return (1);
			}
#ifdef DEBUG
			fprintf(stderr, "option %c: arg = %s\n", i, optarg);
#endif
			flash_set_bootdev(boot_dev);
                        fprintf(stderr, "Boot device change to %s\n", optarg);
			return (0);

		case 'f':
#ifdef DEBUG
			fprintf(stderr, "option %c: arg = %s\n", i, optarg);
#endif
			flash_prog_kern(optarg);
                        fprintf(stderr, "done\n");
			return (0);

		case 's':
#ifdef DEBUG
			fprintf(stderr, "option %c: arg = %s\n", i, optarg);
#endif
			flash_save_param(optarg);
                        fprintf(stderr, "done\n");
			return (0);

		case 'x':
			flash_extract_param();
			return (0);

		case 'd':
			flash_delete_param();
                        fprintf(stderr, "done\n");
			return (0);

		case 'h':
			usage();
			return (0);

		default:
			usage();
			return (0);
		}
	}
        if (argc != 1) {
                usage();
                return (0);
        }
	argc -= optind;
	argv += optind;
/*	flash_extract_param(); */
	usage();
	return (0);
}

void
flash_set_bootdev(char *arg)
{
	int fd, n, i;

#ifdef DEBUG
	printf("boot device option = %s\n", arg);
#endif
	if ((fd = open("/dev/nvram0", O_RDWR)) < 0) {
		perror("/dev/nvram0");
		return;
	}

	if (lseek(fd, NVRAM_BOOT_OFF, 0L) == -1) {
		perror("lseek");
		return;
	}

	if ((n = read(fd, &nvram_boot, sizeof (nvram_boot))) !=
		sizeof (nvram_boot)) {
		perror("read");
		close(fd);
		return;
	}

	nvram_boot.boot_magic[0] = 'N';
	nvram_boot.boot_magic[1] = 'V';
	(void)strcpy(nvram_boot.boot_dev, arg);

	if (lseek(fd, NVRAM_BOOT_OFF, 0L) == -1) {
		perror("lseek");
		return;
	} 

	if ((i = write(fd, &nvram_boot, n)) != n) {
		perror("write");
	}
	close(fd);
}

void
flash_prog_kern(char *kern)
{
	int i, st, ifd, ofd, nread;
	struct stat sb;
	erase_info_t erase;

	if ((ifd = open(kern, O_RDONLY)) < 0) {
		perror(kern);
		return;
	}

	if (fstat(ifd, &sb) < 0) {
		perror("stat");
		close(ifd);
		return;
	}

	if (sb.st_size > (FLASH_SIZE - 8*SECT1_SIZE - 256*KILO_BYTE)) {
		fprintf(stderr, "file size exceeds MAX kernel SIZE\n");
		close(ifd);
		return;
	}

	if ((membase = malloc(SECT2_SIZE)) == NULL) {
		perror("malloc");
		return;
	}

	nread = read(ifd, membase, SECT2_SIZE);

	if (nread < SECT2_SIZE) {
		fprintf(stderr, "file isn't kernel image\n");
		free(membase);
		close(ifd);
		return;
	}

	pboot_block = (boot_block_t *)membase;
	
	if (pboot_block->magic != MAGIC) {
		fprintf(stderr, "file isn't kernel image\n");
		free(membase);
		close(ifd);
		return;
	}

	if ((ofd = open("/dev/mtd/1", O_RDWR)) < 0) {
		perror("/dev/mtd/1");
		close(ifd);
		return;
	}

	erase.start = 0;
	erase.length = SECT2_SIZE;
	i=0;
	lseek(ifd, 0, SEEK_SET);
	fprintf(stderr, "Load boot image to FlashROM\n");
	while ((nread = read(ifd, membase, SECT2_SIZE)) > 0) {
		fprintf(stderr, ".");
		if (ioctl(ofd, MEMERASE, &erase) != 0) {
			perror("Erase failure");
			close(ifd);
			close(ofd);
			return;
		}
		fprintf(stderr, "%c#",0x08);
		if (write(ofd, membase, nread) < 0) {
			perror("mtd");
			close(ifd);
			close(ofd);
			return;
		}
		i++;
		erase.start += nread;
		if(i>=STATUS_COL) {
			fprintf(stderr, "\n");
			i=0;
		}
	}
	fprintf(stderr, "\n");

	free(membase);
	close(ifd);
	close(ofd);
}

void
flash_save_param(char *list)
{
	int i, pid, st, ifd, ofd, nread;
	struct stat sb;
	char localbuf[256];
	erase_info_t erase;

	strcpy(localbuf, "/tmp/flashcfg.XXXXXX");

	if ((ifd = mkstemp(localbuf)) < 0) {
		perror("mkstemp");
		return;
	}

	if ((pid = fork()) == 0) {
		/* in child */
		execl("/usr/bin/tar", "tar", "cvpTzf", list, localbuf, NULL);
		/* not reached here */
	} else {
		wait(&st);
	}

#ifdef DEBUG
	if (st)
		fprintf(stderr, "child returns %d\n", st);
#endif

	if ((ifd = open(localbuf, O_RDONLY)) < 0) {
		perror(localbuf);
		return;
	}

	if (fstat(ifd, &sb) < 0) {
		perror("stat");
		close(ifd);
		return;
	}

	if (sb.st_size > 8 * SECT1_SIZE) {
		fprintf(stderr, "file size exceeds 64KB\n");
		close(ifd);
		return;
	}

	if ((membase = malloc(SECT1_SIZE)) == NULL) {
		perror("malloc");
		return;
	}

	if ((ofd = open("/dev/mtd/0", O_RDWR)) < 0) {
		perror("/dev/mtd/0");
		close(ifd);
		return;
	}

	erase.start = 0;
	erase.length = SECT1_SIZE;
	i=0;
	fprintf(stderr, "Save files to FlashROM\n");
	while ((nread = read(ifd, membase, SECT1_SIZE)) > 0) {
		fprintf(stderr, ".");
		if (ioctl(ofd, MEMERASE, &erase) != 0) {
			perror("Erase failure");
			close(ifd);
			close(ofd);
			return;
		}
		fprintf(stderr, "%c#",0x08);
		if (write(ofd, membase, nread) < 0) {
			perror("mtd");
			close(ifd);
			close(ofd);
			return;
		}
		erase.start += nread;
		if(i>STATUS_COL) {
			fprintf(stderr, "\n");
			i=0;
		}
		i++;
	}
	fprintf(stderr, "\n");

	free(membase);
	close(ifd);
	close(ofd);
	unlink(localbuf);
}

void
flash_extract_param()
{
	int pid, st;

	if ((pid = fork()) == 0) {
		/* in child */
		execl("/usr/bin/tar", "tar", "--no-time-check",
			"-xvpzf", "/dev/mtd/0",
			"-C", "/", NULL);
		/* not reached here */
	} else {
		wait(&st);
	}
#ifdef DEBUG
	if (st)
		fprintf(stderr, "child returns %d\n", st);
#endif
}

void flash_delete_param()
{
	int ofd, i;
	erase_info_t erase;

	if ((ofd = open("/dev/mtd/0", O_RDWR)) < 0) {
		perror("/dev/mtd/0");
		close(ofd);
		return;
	}

	erase.start = 0;
	erase.length = SECT1_SIZE;
	fprintf(stderr, "Delete saved files from FlashROM\n");
	for (i = 0; i < 8; i++) {
		fprintf(stderr, ".");
		fflush(stderr);
		if (ioctl(ofd, MEMERASE, &erase) != 0) {
			perror("Erase failure");
			close(ofd);
			return;
		}
		erase.start += SECT1_SIZE;
	}
	fprintf(stderr, "\n");
	close(ofd);
}
