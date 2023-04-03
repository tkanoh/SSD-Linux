/*	$ssdlinux: sysinst.c,v 1.33 2004/05/21 08:57:45 yamagata Exp $	*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mount.h>
#include <sys/param.h>

#define TARGET_MOUNT_POINT "/mnt"
#define CDROM_MOUNT_POINT "/cdrom"
#define EXT2_FS	   "ext2"
#define EXT3_FS	   "ext3"
#define DEFAULT_FS EXT2_FS
#define DIST_PATH	"binary"
#define FTP_SITE	"ftp.plathome.co.jp"
#define FTP_DIST_PATH	"/pub/ssdlinux"
#define INST_DIST_PATH	"/usr/INST"
#define FTP_LOGIN	"ftp"

#define MAXARG 20
#define WORDBUFSIZ 256
#define NAMELEN 16
#define MAXMD 16	/* MAX number of selectable Install media */
#define MAXHDDEV 16
#define MAXHDPAT 64
#define MAXPAT 256
#define MAXBOOTDEV 16
#define IPADDRESSLEN 16

struct md_t {
	char name[NAMELEN];
	int type;  	/* 0: ether 1: cdrom */
};

struct hd_t {
	char name[NAMELEN];
	int flag_cd;
	int flag_bootable;
	int type[MAXHDPAT];
	int size[MAXHDPAT];
	int bootable[MAXHDPAT];
};

struct pa_t {
	char name[NAMELEN];
	char mntp[MAXPATHLEN];
	char fst[NAMELEN];
	char opt[NAMELEN];
	int size;
	int bsize;
	int bootable;
	int fck1;
	int fck2;
	int flag_act;
	int flag_ck;
	int flag_swap;
};

struct bp_t {
	char name[NAMELEN];
	int type;
};

struct dist_list_t {
	char name[NAMELEN];
	int flag_inst;
	char desc[NAMELEN*2];
	int flag_result;
} dist_list[] = {	
		{"kern",    1, "Generic Kernel : ", 0},
		{"base",    1, "Base           : ", 0},
		{"etc",     1, "System (/etc)  : ", 0},
		{"comp",    1, "Compiler       : ", 0},
#ifdef HAVE_KERNEL
		{"cross",   1, "Cross Compiler : ", 0},
#endif
		{"man",     1, "Manuals        : ", 0},
#ifdef HAVE_CONTRIB
		{"contrib", 0, "Contributions  : ", 0},
#endif
		{"src",     0, "Source         : ", 0}
};
#if defined(HAVE_KERNEL) || defined(HAVE_CONTRIB)
#define	NUM_DIST 7
#else
#define	NUM_DIST 6
#endif

struct net_t {
	char hostname[MAXHOSTNAMELEN];
	char domain[MAXHOSTNAMELEN];
	char ip[IPADDRESSLEN];
	char mask[IPADDRESSLEN];
	char cast[IPADDRESSLEN];
	char route[IPADDRESSLEN];
	char dns[IPADDRESSLEN];
};

struct ftp_t {
	char server[MAXHOSTNAMELEN];
	char remote_dir[MAXPATHLEN];
	char local_dir[MAXPATHLEN];
	char proxy[MAXHOSTNAMELEN];
	char login[NAMELEN];
	char passwd[NAMELEN*3];
};

static char *ACT[2] = {"   "," * "};
static char *SEL[2] = {" ",">"};
static char *YN[2] = {"no  ","yes "};
static char *FSCKOPT[2] = {"","-c"};
static char *MEDIA[2] = {"Network","CDROM"};
static char *BOOTTYPE[2] = {"Master boot record.","Partition boot secter."};

#ifndef CONF_NETWORK
#define NUM_NET_CONF 8
static char *net_conf[NUM_NET_CONF] = {
	"/etc/myname",
	"/etc/mygate",
	"/etc/ifconfig.eth0",
	"/etc/ifconfig.eth1",
	"/etc/resolv.conf",
	"/etc/hosts",
	"/etc/hosts.allow",
	"/etc/hosts.deny"
};
#endif

void s_popen(command)
char *command;
{
	register int i;
	FILE *fp;
	char buf[BUFSIZ];

#ifndef DEBUG
	if((fp=popen(command,"r"))==NULL) {
		printf("Error: '%s'\n",command);
		exit(1);
	}
	while(fgets(buf,BUFSIZ,fp)) printf("%s",buf);
	pclose(fp);
#else
	printf("*** %s\n",command);
#endif
	return;
}

void s_system(command)
char *command;
{
	register int i;

#ifndef DEBUG
	if(system(command)== -1) {
		printf("Error: '%s'\n",command);
		exit(1);
	};
#else
	printf("*** %s\n",command);
#endif
	return;
}

void chop(result,source)
char *result,*source;
{
	while((*source!='\n') && (*source!='\0')) {
		*result = *source;
		source++;
		result++;
	}
	*result='\0';

	return;
}

/* Convert TAB code to SPACE */
void tab2sp(result,source)
char *result,*source;
{
	while(((*source==' ') || (*source=='\t')) && (*source!='\0')) {
		source++;
	}
	while(*source!='\0') {
		if(*source=='\t') {
			*result = ' ';
			result++;
		}
		else {
			*result = *source;
			result++;
		}
		source++;
	}
	*result='\0';
	return;
}

/* get arguments and retrun number of arguments */
int getarg(result,source)
char **result,*source;
{
	register int i,j;
	char *buf;

	i=0;
	while((*source!='#') && (*source!='\n') && (*source!='\0')&& (*source!=10)) {
		if(*source!=' ') {
			buf=result[i];
			j = 0;
			while((*source!=' ') && (*source!='\0') && (*source!=10) && (*source!='\n')) {
				if (j < (BUFSIZ-1)) {
					*buf = *source;
					buf++;
					source++;
					j++;
				}
			}
			*buf='\0';
			i++;
			if (i >= MAXARG) {
				break;
			}
		}
		else {
			source++;
		}
	}
	return(i);
}

int getlu(source,n)
char *source;
int n;
{
	register int i;
	char *buf,str[NAMELEN];

	buf=str;

	for(i=0;i<n;i++) {
		source++;
	}
	while((*source!='\n') && (*source!='\0')) {
		*buf = *source;
		buf++;
		source++;
	}
	*buf='\0';

	return(atoi(str));
}

int getdevnum(source,n)
char *source;
int n;
{
	register int i;
	int c;

	for(i=0;i<n;i++) {
		source++;
	}
	c = *source;
	c -= 97;

	return(c);
}

char *ip2char(ip)
unsigned int ip;
{
	char *cip;
	unsigned int p[4];

	cip=(char *)malloc(sizeof(char)*IPADDRESSLEN);
	memset(cip,0,sizeof(char)*IPADDRESSLEN);

	p[3]=(ip >> 24) & 0x000000ff;
	p[2]=(ip >> 16) & 0x000000ff;
	p[1]=(ip >>  8) & 0x000000ff;
	p[0]=ip & 0x000000ff;

	snprintf(cip,sizeof(char)*IPADDRESSLEN,"%u.%u.%u.%u",p[3],p[2],p[1],p[0]);

	return(cip);
}

unsigned int ip2int(cip)
char *cip;
{
	unsigned int ip,p[4];

	sscanf(cip,"%u.%u.%u.%u",&p[3],&p[2],&p[1],&p[0]);
	ip=(p[3]<< 24) |(p[2]<< 16) | (p[1]<< 8) | p[0];

	return(ip);
}

void print_pat(submenu,pa,num_pa,sel)
struct pa_t **pa;
int num_pa,submenu,sel;
{
	register int i;

	if(submenu)
		printf("\n\nSetup %s\n\n",pa[sel]->name);
	else
		printf("\n\nSetup Filesystem\n\n");
	printf("    %1s %4s %3s %4s %-11s %6s %-8s %5s %-5s %-16s\n",
		" ","  ","Use","Boot","Device    ","MB    ","FStype ","BSize","fsck","Mount Point");
	printf("    %1s %4s %3s %4s %-11s %6s %-8s %5s %4s %-16s\n",
		" ","  ","---","----","----------","------","-------","-----","-----","-----------");

	for(i=0;num_pa>i;i++) {
		if(pa[i]->bsize)
			printf("    %1s %3d. %3s %4s %-11s %6d %-8s  %4d  %4s %-s\n",
				SEL[i==sel],i,ACT[pa[i]->flag_act],ACT[pa[i]->bootable],pa[i]->name,pa[i]->size,pa[i]->fst,pa[i]->bsize,YN[pa[i]->flag_ck],pa[i]->mntp);
		else
			printf("    %1s %3d. %3s %4s %-11s %6d %-8s %5s  %4s %-s\n",
				SEL[i==sel],i,ACT[pa[i]->flag_act],ACT[pa[i]->bootable],pa[i]->name,pa[i]->size,pa[i]->fst,"     ",YN[pa[i]->flag_ck],pa[i]->mntp);
	}
	if(submenu) {
		      printf("\n    a. Toggle use this partition.  c. Toggle mke2fs/mkswap with fsck.\n"); 
		if(!pa[sel]->flag_swap) {
		        printf("    f. Toggle fs type ext2/ext3.   m. Enter/Change mount point.\n"); 
		        printf("    b. Change block size.\n"); 
		}
		printf("    x. Exit this menu.\n\n"); 
		if(!pa[sel]->flag_swap) {
			printf("Enter command [a, c, f, m, b or x] : ");
		}
		else {
			printf("Enter command [a, c, or x] : ");
		}
	}
	else {
		printf("\n    x.  Exit this menu.\n\n");
		printf("Enter number [0-%d or x] : ",num_pa-1);
	}

	return;
}

void print_bp(bp,num_bp,act)
struct bp_t **bp;
int num_bp,act;
{
	register int i;
	printf("\n\nSelect boot partition to install boot code.\n\n");
	for(i=0;num_bp>i;i++) {
		printf("    %s %-12s  %s\n",ACT[i==act],bp[i]->name,BOOTTYPE[bp[i]->type]);
	}
	printf("\n    t. Toggle boot partition.   x. Exit this menu.\n\n"); 
	printf("Enter command [t or x] : ");
	
	return;
}

void print_dist()
{
	register int i;

	printf("\n\nSelect Distributions\n\n");
	for(i=0;NUM_DIST>i;i++) {
		printf("    %2d. %s %s\n",i,dist_list[i].desc,YN[dist_list[i].flag_inst]);
	}
	printf("\n     x. Exit this menu.\n\n");
	printf("Enter number [0-%d or x] : ",NUM_DIST-1);
	
	return;
}

void print_md(md,num_md,act_md)
struct md_t **md;
int num_md,act_md;
{
	register int i;

	printf("\n\nSelect install media\n\n");
	for(i=0;i<num_md;i++)
		printf("    %s%-7s : %s\n",ACT[i==act_md],MEDIA[md[i]->type],md[i]->name);

	if(num_md==1) {
		printf("\n    x. Exit this menu.\n\n"); 
		printf("Enter command [x] : ");
	}
	else {
		printf("\n    t. Toggle install media.    x. Exit this menu.\n\n"); 
		printf("Enter command [t or x] : ");
	}
	return;
}

void print_net(net,interface)
struct net_t *net;
char *interface;
{
	printf("\n\nSetup Network on %s\n\n",interface);
	printf("    0. Hostname      : %s\n",net->hostname);
	printf("    1. Domainname    : %s\n",net->domain);
	printf("    2. IP address    : %s\n",net->ip);
	printf("    3. Netmask       : %s\n",net->mask);
	printf("    4. Broadcast     : %s\n",net->cast);
	printf("    5. Default route : %s\n",net->route);
	printf("    6. DNS server IP : %s\n\n",net->dns);
	printf("    x. Exit this menu.\n\n");
	printf("Enter number [0-6 or x] : ");

	return;
}

void print_ftp(ftp)
struct ftp_t *ftp;
{
	printf("\n\nSetup for FTP download\n\n");
	printf("    0. FTP server      : %s\n",ftp->server);
	printf("    1. Remote pathname : %s\n",ftp->remote_dir);
	printf("    2. Local pathname  : %s\n",ftp->local_dir);
	printf("    3. FTP proxy       : %s\n",ftp->proxy);
	printf("    4. Login name      : %s\n",ftp->login);
	printf("    5. Login Password  : %s\n\n",ftp->passwd);
	printf("    x. Exit this menu.\n\n");
	printf("Enter number [0-5 or x] : ");

	return;
}

int getanswer()
{
	char buf[BUFSIZ];
	fgets(buf,BUFSIZ,stdin);
	if(strlen(buf)==1) strcpy(buf,"z");
	return(*buf);
}

void isexit(n,msg)
int n;
char *msg;
{
	if (getanswer() != n) {
		printf("%s\n",msg);
		exit(0);
	}
	return;
}

int isskip(msg)
char *msg;
{
	printf("\n\n%s\n",msg);
	printf("Are you sure [y/N] ? ");
	if (getanswer() != 'y') {
		printf("\nSkip...\n");
		return(0);
	}
	printf("\n");
	return(1);
}

#ifdef PROBE_PCCARD

/* detect pccard device */
int probe_pccard()
{
	FILE *fp;
	char buf[BUFSIZ],str[BUFSIZ],*word[MAXARG];
	register int i,j;

	for(i=0;i<MAXARG;i++)
		word[i]=(char *)malloc(sizeof(char)*WORDBUFSIZ);

	j=0;
	fp=fopen("/proc/devices","r");
	while(fgets(buf,BUFSIZ,fp)) {
		if(strlen(buf)==1) continue;
		tab2sp(str,buf);
		if(*str=='#') continue;
		i=getarg(word,str);
		if((i==2) && (strcmp(word[0],"254")==0) && (strcmp(word[1],"pcmcia")==0)) {
			s_system("/sbin/cardmgr");
			j=1;
			break;
		}
	}
	fclose(fp);

	for(i=0;i<MAXARG;i++) free(word[i]);

	return(j);
}
#endif

/* detect disk partitions */
int probe_hd(hd)
struct hd_t **hd;
{
	FILE *fp;
	char buf[BUFSIZ],str[BUFSIZ],*word[MAXARG];
	register int i,j;

	for(i=0;i<MAXARG;i++)
		word[i]=(char *)malloc(sizeof(char)*WORDBUFSIZ);

	for(i=0;i<MAXHDDEV;i++) {
		strcpy(hd[i]->name,"");
		hd[i]->flag_cd=0;
		hd[i]->flag_bootable=0;
		for(j=1;j<MAXHDPAT;j++) {
			hd[i]->type[j]=(int)malloc(sizeof(int));
			hd[i]->type[j]=0;
			hd[i]->size[j]=0;
			hd[i]->bootable[j]=0;
		}
	}

	j=0;
	fp=fopen("/proc/partitions","r");
	while(fgets(buf,BUFSIZ,fp)) {
		if(strlen(buf)==1) continue;
		tab2sp(str,buf);
		i=getarg(word,str);
		if((i==4) && (strlen(word[3])==3)) {
			strcpy(hd[j]->name,word[3]);
			j++;
			if (j >= MAXHDDEV) {
				break;
			}
		}
	}
	fclose(fp);

	for(i=0;i<MAXARG;i++) free(word[i]);

	return(j);
}

/* detect eth and cdrom device */
int probe_md(md,hd,num_hd)
struct md_t **md;
struct hd_t **hd;
int num_hd;
{
	FILE *fp;
	char buf[BUFSIZ],str[BUFSIZ],*word[MAXARG];
	register int i,j,k,m;

	for(i=0;i<MAXARG;i++)
		word[i]=(char *)malloc(sizeof(char)*WORDBUFSIZ);

	m=0;
	if(fp=fopen("/proc/net/dev","r")) {
		while(fgets(buf,BUFSIZ,fp)) {
			if(strlen(buf)==1) continue;
			tab2sp(str,buf);
			i=getarg(word,str);
			if(((i==17) || (i==16)) && (strncmp(word[0],"eth",3)==0)) {
				strncpy(md[m]->name,word[0],4);
				md[m]->type=0;
				m++;
				break;
			}
		}
		fclose(fp);
	}

	/* detect cdrom device */
	if(fp=fopen("/proc/sys/dev/cdrom/info","r")) {
		while(fgets(buf,BUFSIZ,fp)) {
			if(strlen(buf)==1) continue;
			tab2sp(str,buf);
			if(*str=='#') continue;
			i=getarg(word,str);
			if((i>2) && (strcmp(word[0],"drive"))==0 && (strcmp(word[1],"name:"))==0) {
				for(j=2;j<i;j++) {
					if (strncmp(word[j],"sr",2)==0) {
						if (m >= MAXMD) {
							continue;
						}
						snprintf(md[m]->name,sizeof(char)*NAMELEN,"/dev/scd%d",getlu(word[j],2));
						md[m]->type=1;
						m++;
					}
					else if (strncmp(word[j],"hd",2)==0) {
						if (m >= MAXMD) {
							continue;
						}
						snprintf(md[m]->name,sizeof(char)*NAMELEN,"/dev/%s",word[j]);
						md[m]->type=1;
						m++;
						for(k=0; k<num_hd; k++) {
							if (strncmp(word[j],hd[k]->name,3)==0) {
								hd[k]->flag_cd=1;
								break;
							}
						}
					}
				}
			}
		}	
		fclose(fp);
	}

	for(i=0;i<MAXARG;i++) free(word[i]);

	return(m);
}

void start_msg()
{
	printf("\n\nSSD/Linux %s/%s Installer\n\n",SSDRELEASENAME,KERNEL_VERSION);
	printf("  Why do you choose Linux ?\n");
	printf("  We recommend you to use NetBSD, FreeBSD, or OpenBSD instead.\n\n");
	printf("Are you sure to install [y/N] ? ");
	isexit('y',"\n  Cool !!\n");
	printf("Really [y/N] ? ");
	isexit('y',"\n  Smart !!\n");
	printf("\n  It isn't smart ...\n\n");
	return;
}

/* read disk partitions */
int rd_partition(hd,num_hd)
struct hd_t **hd;
int num_hd;
{
	FILE *fp;
	char buf[BUFSIZ],str[BUFSIZ],*word[MAXARG];
	int units,bootable_exist;
	register int i,j;

	for(i=0;i<MAXARG;i++)
		word[i]=(char *)malloc(sizeof(char)*WORDBUFSIZ);

	bootable_exist=1;
	for(i=0;i < num_hd; i++) { 
		if(hd[i]->flag_cd) continue;
		snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/fdisk -l /dev/%s",hd[i]->name);
		fp=popen(buf,"r");
		while(fgets(buf,BUFSIZ,fp)) {
			if(strlen(buf)==1) continue;
			tab2sp(str,buf);
			if(*str=='#') continue;
			j=getarg(word,str);
			if((j==10) && (strcmp(word[0],"Units")==0)) {
				units=atoi(word[4]);
				continue;
			}
			snprintf(buf,sizeof(char)*NAMELEN,"/dev/%s",hd[i]->name);
			if(strncmp(word[0],buf,8)==0) {
				j=getlu(word[0],8);
				if(strcmp(word[1],"*")==0) {
					bootable_exist=0;
					hd[i]->flag_bootable=1;
					hd[i]->bootable[j]=1;
					sscanf(word[5],"%2x",&(hd[i]->type[j]));
					hd[i]->size[j]=((atoi(word[3]) - atoi(word[2])) * units ) / 2048;
				} else { 
					hd[i]->bootable[j]=0;
					sscanf(word[4],"%2x",&(hd[i]->type[j]));
					hd[i]->size[j]=((atoi(word[2]) - atoi(word[1])) * units ) / 2048;
				}
			}
		}
		pclose(fp);
	}

	for(i=0;i<MAXARG;i++) free(word[i]);

	return(bootable_exist);
}

/* make partition array */
int pat_array(num_bp,hd,pa,bp,num_hd)
int *num_bp;
struct hd_t **hd;
struct pa_t **pa;
struct bp_t **bp;
int num_hd;
{
	int num_pat;
	register int i,j,k;

	i=0;
	*num_bp=0;
	for(j=0;j < num_hd; j++) {
		if(hd[j]->flag_bootable) {
			snprintf(bp[*num_bp]->name,sizeof(char)*NAMELEN,"/dev/%s",hd[i]->name);
			bp[*num_bp]->type=0;
			(*num_bp)++;
		}
			
		for(k=0;k < MAXHDPAT; k++) {
			if(hd[j]->type[k]==0x82) {
				snprintf(pa[i]->name,sizeof(char)*NAMELEN,"/dev/%s%d",hd[j]->name,k);
				strcpy(pa[i]->mntp,"swap");
				strcpy(pa[i]->fst,"swap");
				strcpy(pa[i]->opt,"defaults");
				pa[i]->size=hd[j]->size[k];
				pa[i]->bsize=0;
				pa[i]->bootable=0;
				pa[i]->fck1=0;
				pa[i]->fck2=0;
				pa[i]->flag_act=1;
				pa[i]->flag_ck=0;
				pa[i]->flag_swap=1;
				i++;
			
			}
			else if((hd[j]->type[k]==0x83) || (hd[j]->type[k]==0x85)) {
				snprintf(pa[i]->name,sizeof(char)*NAMELEN,"/dev/%s%d",hd[j]->name,k);
				strcpy(pa[i]->mntp,"");
				strcpy(pa[i]->fst,DEFAULT_FS);
				strcpy(pa[i]->opt,"defaults");
				pa[i]->size=hd[j]->size[k];
				pa[i]->bsize=4096;
				pa[i]->bootable=hd[j]->bootable[k];
				pa[i]->fck1=1;
				pa[i]->fck2=1;
				pa[i]->flag_act=0;
				pa[i]->flag_ck=0;
				pa[i]->flag_swap=0;
				if(pa[i]->bootable) {
					strcpy(bp[*num_bp]->name,pa[i]->name);
					bp[*num_bp]->type=1;
					(*num_bp)++;
				}
				i++;
			}
		}
	}
	num_pat=i;

	strcpy(pa[0]->mntp,"/");
	pa[0]->flag_act=1;

	/* proc fs */
	strcpy(pa[i]->name,"none");
	strcpy(pa[i]->mntp,"/proc");
	strcpy(pa[i]->fst,"proc");
	strcpy(pa[i]->opt,"defaults");
	pa[i]->size=0;
	pa[i]->bsize=0;
	pa[i]->bootable=0;
	pa[i]->fck1=0;
	pa[i]->fck2=0;
	pa[i]->flag_act=1;
	pa[i]->flag_ck=0;
	pa[i]->flag_swap=0;
	i++;

	/* devpts */
	strcpy(pa[i]->name,"none");
	strcpy(pa[i]->mntp,"/dev/pts");
	strcpy(pa[i]->fst,"devpts");
	strcpy(pa[i]->opt,"gid=4,mode=620");
	pa[i]->size=0;
	pa[i]->bsize=0;
	pa[i]->bootable=0;
	pa[i]->fck1=0;
	pa[i]->fck2=0;
	pa[i]->flag_act=1;
	pa[i]->flag_ck=0;
	pa[i]->flag_swap=0;

	return(num_pat);
}

/* Setup Partition. */
void set_partition(pa,num_pat)
struct pa_t **pa;
int num_pat;
{
	int m;
	register int i,j;
	char buf[BUFSIZ];

	print_pat(0,pa,num_pat,-1);
	while((i=getanswer()) != 'x') {
		if ((i-=48) < 0) {
			printf("Error: Illegal number.\n");
			printf("Enter number [0-%d or x] : ",num_pat-1);
			continue;
		}
		if (i>(num_pat-1)) {
			printf("Error: Illegal number.\n");
			printf("Enter number [0-%d or x] : ",num_pat-1);
			continue;
		}
		print_pat(1,pa,num_pat,i);
		while((j=getanswer()) != 'x') {
			switch(j) {
				case 'a':
					pa[i]->flag_act = !pa[i]->flag_act;
					break;
				case 'c':
					pa[i]->flag_ck = !pa[i]->flag_ck;
					break;
				case 'f':
					if(strcmp(pa[i]->fst,EXT2_FS)==0) 
						strcpy(pa[i]->fst,EXT3_FS);
					else 
						strcpy(pa[i]->fst,EXT2_FS);
					break;
				case 'm':
					printf("Enter mount point : ");
					fgets(buf,MAXPATHLEN,stdin);
					chop(pa[i]->mntp,buf);
					if(strlen(pa[i]->mntp)) pa[i]->flag_act=1;
					break;
				case 'b':
					printf("Enter block size (512, 1024, 2048, 4096 or 8192) : ");
					fgets(buf,BUFSIZ,stdin);
					sscanf(buf,"%d",&m);
					if(!((m==512) || (m==1024) || (m==2048) || (m==4096) || (m==8192)))
						printf("Error: Illegal block size.\n");
					else 
						pa[i]->bsize=m;
					break;
				default:
					printf("Error: Illegal command.\n");
					break;
			}
			print_pat(1,pa,num_pat,i);
		}
		print_pat(0,pa,num_pat,-1);
	}

	return;
}

/* Set root partition parameters */
int set_root_partition(exist_root,pa,num_pat)
int *exist_root;
struct pa_t **pa;
int num_pat;
{ 
	register int i,j;

	for(i=0;i < num_pat; i++) {
		if((strcmp(pa[i]->mntp,"/")==0) && (pa[i]->flag_act)) {
			j=i;
			*exist_root=1;
			pa[i]->fck1=0;
			pa[i]->fck2=0;
			break;
		}
	}

	return(j);
}

/* Select boot partition */
int set_boot_partition(bp,num_bp)
struct bp_t **bp;
int num_bp;
{
	register int i,j;

	j=0;
	print_bp(bp,num_bp,j);
	while((i=getanswer()) != 'x') {
		switch(i) {
			case 't':
				j++;
				if(j==num_bp)
					j -= num_bp;
				break;
			default:
				printf("Error: Illegal command.\n");
				break;
		}
		print_bp(bp,num_bp,j);
	}

	return(j);
}

/* Run mkswap */
void run_mkswap(pa,num_pat)
struct pa_t **pa;
int num_pat;
{
	register int i;
	char buf[BUFSIZ];
	FILE *fp;

	for(i=0;i < num_pat; i++) {
		if(!pa[i]->flag_act) continue; 
		if(pa[i]->flag_swap) {
			snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/mkswap %s %s",
				FSCKOPT[pa[i]->flag_ck],pa[i]->name);
			s_system(buf);
#ifndef DEBUG
			fp=fopen("/etc/fstab","a");
			fprintf(fp,"%s swap swap defaults 0 0\n",pa[i]->name);
			fclose(fp);
#endif
		} 
	}

	s_system("/sbin/swapon -a");
	return;
}

/* Run mke2fs */
void run_mke2fs(pa,num_pat)
struct pa_t **pa;
int num_pat;
{
	register int i;
	char buf[BUFSIZ];

	for(i=0;i < num_pat; i++) {
		if(!pa[i]->flag_act) continue; 
		if(!pa[i]->flag_swap) {
			if(strcmp(pa[i]->fst,EXT2_FS)==0)
				snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/mke2fs %s -b %d %s",
					FSCKOPT[pa[i]->flag_ck],pa[i]->bsize,pa[i]->name);
			else
				snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/mke2fs -j %s -b %d %s",
					FSCKOPT[pa[i]->flag_ck],pa[i]->bsize,pa[i]->name);
			s_system(buf);
		}
	}
	return;
}

/* Do mount fs */
do_mount(pa,num_pat,root_pat)
struct pa_t **pa;
int num_pat;
int root_pat;
{
	register int i;
	char buf[BUFSIZ];

	snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/mount -t %s %s %s",pa[root_pat]->fst,pa[root_pat]->name,TARGET_MOUNT_POINT);
	s_system(buf);

	snprintf(buf,sizeof(char)*BUFSIZ,"/bin/mkdir %s/tmp",TARGET_MOUNT_POINT);
	s_system(buf);

	snprintf(buf,sizeof(char)*BUFSIZ,"/bin/chmod 1777 %s/tmp",TARGET_MOUNT_POINT);
	s_system(buf);

	snprintf(buf,sizeof(char)*BUFSIZ,"TMPDIR=%s/tmp && export TMPDIR",TARGET_MOUNT_POINT);
	s_system(buf);

	for(i=0;i < num_pat; i++) {
		if(i==root_pat) continue;
		if(!pa[i]->flag_act) continue; 
		if(!pa[i]->flag_swap) {
			snprintf(buf,sizeof(char)*BUFSIZ,"/bin/mkdir -p %s%s",TARGET_MOUNT_POINT,pa[i]->mntp);
			s_system(buf);
			snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/mount -t %s %s %s/%s",pa[i]->fst,pa[i]->name,TARGET_MOUNT_POINT,pa[i]->mntp);
			s_system(buf);
		}
	}
	return;
}

/* Do umount fs */
do_umount(pa,num_pat,root_pat)
struct pa_t **pa;
int num_pat;
int root_pat;
{
	register int i;
	char buf[BUFSIZ];

	for(i=0;i < num_pat; i++) {
		if(i==root_pat) continue;
		if(!pa[i]->flag_act) continue; 
		if(!pa[i]->flag_swap) {
			snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/umount %s/%s",TARGET_MOUNT_POINT,pa[i]->mntp);
			s_system(buf);
		}
	}

	snprintf(buf,sizeof(char)*BUFSIZ,"TMPDIR=/tmp && export TMPDIR");
	s_system(buf);
	snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/umount %s",TARGET_MOUNT_POINT);
	s_system(buf);

	return;
}

/* Set Distributions */
void set_distributions()
{
	register int i;

	print_dist();
	while((i=getanswer()) != 'x') {
		if ((i-=48) < 0) {
			printf("Error: Illegal number.\n");
			printf("Enter number [0-%d or x] : ",NUM_DIST-1);
			continue;
		}
		if (i>(NUM_DIST-1)) {
			printf("Error: Illegal number.\n");
			printf("Enter number [0-%d or x] : ",NUM_DIST-1);
			continue;
		}
		dist_list[i].flag_inst = !dist_list[i].flag_inst;
		print_dist();
	}
	return;
}

int set_install_media(md,num_md)
struct md_t **md;
int num_md;
{
	register int i,j;

	j=0;
	print_md(md,num_md,j);
	while((i=getanswer()) != 'x') {
		switch(i) {
			case 't':
				j++;
				if(j==num_md)
					j -= num_md;
				break;
			default:
				printf("Error: Illegal command.\n");
				break;
		}
		print_md(md,num_md,j);
	}
	return(j);
}

/* extract distribution (CDROM) */

void do_extract_from_cdrom(md)
struct md_t *md;
{
	register int i;
	char buf[BUFSIZ],str[BUFSIZ];
	struct stat *fs;
	fs=(struct stat *)malloc(sizeof(struct stat));

	snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/mount -rt iso9660 %s %s",md->name,CDROM_MOUNT_POINT);
	s_system(buf);

	for(i=0;i<NUM_DIST;i++) {
		if(dist_list[i].flag_inst) {
			snprintf(buf,sizeof(char)*BUFSIZ,"%s/%s/%s/%s.tgz",
				CDROM_MOUNT_POINT,DIST_ARCH,DIST_PATH,dist_list[i].name);
			snprintf(str,sizeof(char)*BUFSIZ,"cd %s && /usr/bin/tar xvpzf %s",
					TARGET_MOUNT_POINT,buf);
			printf("Extract %s.tgz ...\n",dist_list[i].name);
#ifndef DEBUG
			if(stat(buf,fs)==0) {
				s_popen(str);
				dist_list[i].flag_result= 1;
			}
			else {
				dist_list[i].flag_result= -1;
			}
#else
			s_popen(str);
			dist_list[i].flag_result= 1;
#endif
		}
	}

	snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/umount %s",CDROM_MOUNT_POINT);
	s_system(buf);

	free(fs);
	return;
}

#ifdef CONF_NETWORK
/* Run dhclient */
void run_dhclient(md)
struct md_t *md;
{
	char buf[BUFSIZ];

	snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/dhclient -q %s",md->name);
	s_popen(buf);
	return;
}

/* Set DHCP */
int set_dhcp(md)
struct md_t *md;
{
	FILE *fp;
	char buf[BUFSIZ];

	printf("\n\nUsing DHCP client on %s [y/N] ? ",md->name);
	if(getanswer() == 'y') {
		run_dhclient(md);
		return(1);
	}
	return(0);
}

void set_network(md,net)
struct net_t *net;
struct md_t *md;
{
	char buf[BUFSIZ];
	unsigned int p,q,mask;
	register int i;

	strcpy(net->hostname,"");
	strcpy(net->domain,"");
	strcpy(net->ip,"");
	strcpy(net->route,"");
	strcpy(net->dns,"");

	print_net(net,md->name);
	while((i=getanswer()) != 'x') {
		switch(i) {
			case '0':
				printf("Enter Hostname : ");
				fgets(buf,MAXHOSTNAMELEN,stdin);
				chop(net->hostname,buf);
				break;
			case '1':
				printf("Enter Domainname : ");
				fgets(buf,MAXHOSTNAMELEN,stdin);
				chop(net->domain,buf);
				break;
			case '2':
				printf("Enter IP address : ");
				fgets(buf,BUFSIZ,stdin);
				chop(net->ip,buf);
				break;
			case '3':
				printf("Enter Netmask : ");
				fgets(buf,BUFSIZ,stdin);
				chop(net->mask,buf);
				break;
			case '4':
				printf("Enter Broadcast : ");
				fgets(buf,BUFSIZ,stdin);
				chop(net->cast,buf);
				break;
			case '5':
				printf("Enter default route IP address : ");
				fgets(buf,BUFSIZ,stdin);
				chop(net->route,buf);
				break;
			case '6':
				printf("Enter DNS server IP address : ");
				fgets(buf,BUFSIZ,stdin);
				chop(net->dns,buf);
				break;
			default:
				printf("Error: Illegal command.\n");
				break;
		}
		if(strlen(net->ip)) {
			p=ip2int(net->ip);
			q = (p  >> 30) & 0x0003;
			if (!((q >> 1) & 0x1)) mask=0xff000000;
			if (!(q ^ 0x2)) mask=0xffff0000;
			if (!(q ^ 0x3)) mask=0xffffff00;
			if(strlen(net->route)==0) strcpy(net->route,net->ip);
			if(strlen(net->mask)==0) strcpy(net->mask,ip2char(mask));
			if(strlen(net->cast)==0) strcpy(net->cast,ip2char(p | (~mask)));
		}
		print_net(net,md->name);
	}
	return;
}

void do_network(md,net)
struct net_t *net;
struct md_t *md;
{
	char buf[BUFSIZ];

	snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/ifconfig %s inet %s broadcast %s netmask %s",
		md->name,net->ip,net->cast,net->mask);
	s_system(buf);
	snprintf(buf,sizeof(char)*BUFSIZ,"/sbin/route add defualt gw %s 0.0.0.0 metric 1",net->route);
	s_system(buf);
	return;
}
#endif /* #ifdef CONF_NETWORK */

/* Setup ftp parameters */
void set_ftp(net,ftp)
struct net_t *net;
struct ftp_t *ftp;
{
	char buf[BUFSIZ];
	register int i;

	strcpy(ftp->server,FTP_SITE);
	snprintf(ftp->remote_dir,sizeof(char)*MAXPATHLEN,"%s/%s/%s/%s",
		FTP_DIST_PATH,SSDRELEASENAME,DIST_ARCH,DIST_PATH);
	strcpy(ftp->local_dir,INST_DIST_PATH);
	strcpy(ftp->proxy,"");
	strcpy(ftp->login,FTP_LOGIN);
	strcpy(ftp->passwd,"");

	if(strlen(net->domain))
		snprintf(ftp->passwd,sizeof(char)*NAMELEN*3,"root@%s",net->domain);
	else 
		strcpy(ftp->passwd,"Your_Mail_Address");
	print_ftp(ftp);
	while((i=getanswer()) != 'x') {
		switch(i) {
			case '0':
				printf("Enter FTP server : ");
				fgets(buf,MAXHOSTNAMELEN,stdin);
				chop(ftp->server,buf);
				break;
			case '1':
				printf("Enter Remote pathnmae : ");
				fgets(buf,MAXPATHLEN,stdin);
				chop(ftp->remote_dir,buf);
				break;
			case '2':
				printf("Enter Local pathname : ");
				fgets(buf,MAXPATHLEN,stdin);
				chop(ftp->local_dir,buf);
				break;
			case '3':
				printf("Enter FTP Proxy (ex. ftp://proxy.your.site:8080) : ");
				fgets(buf,MAXHOSTNAMELEN,stdin);
				chop(ftp->proxy,buf);
				break;
			case '4':
				printf("Enter Login name : ");
				fgets(buf,BUFSIZ,stdin);
				chop(ftp->login,buf);
				break;
			case '5':
				printf("Enter password : ");
				fgets(buf,BUFSIZ,stdin);
				chop(ftp->passwd,buf);
				break;
			default:
				printf("Error: Illegal command.\n");
				break;
		}
		print_ftp(ftp);
	}

	return;
}

void set_proxy(ftp)
struct ftp_t *ftp;
{
	char buf[BUFSIZ];

	if(strlen(ftp->proxy)) {
		snprintf(buf,sizeof(char)*BUFSIZ,"set ftp_proxy=%s && export ftp_proxy",ftp->proxy);
		s_system(buf);
	}
	return;
}

/* Convert '@' to '%' */
void at2per(result,source)
char *result,*source;
{
	while(*source!='\0') {
		if(*source=='@') {
			*result = '%';
			result++;
		}
		else {
			*result = *source;
			result++;
		}
		source++;
	}
	*result='\0';
	return;
}

/* fetch distribution */
void do_ftp(ftp)
struct ftp_t *ftp;
{
	char buf[BUFSIZ],str[BUFSIZ];
	register int i;

	snprintf(buf,sizeof(char)*BUFSIZ,"/bin/mkdir -p %s%s",TARGET_MOUNT_POINT,ftp->local_dir);
	s_system(buf);

	/* lukemftp-1.5 dose not work correct if password contain '@' */
	at2per(str,ftp->passwd);
	

	for(i=0;i<NUM_DIST;i++) {
		if(dist_list[i].flag_inst) {
			snprintf(buf,sizeof(char)*BUFSIZ,"cd %s%s && /usr/bin/ftp ftp://%s:%s@%s%s/%s.tgz",
				TARGET_MOUNT_POINT,ftp->local_dir,ftp->login,str,ftp->server,
				ftp->remote_dir,dist_list[i].name);
			printf("Fetch %s.tgz ...\n",dist_list[i].name);
			s_popen(buf);
		}
	}
	return;
}

/* extract distribution (FTP) */
void do_extract_from_ftp(ftp)
struct ftp_t *ftp;
{
	char buf[BUFSIZ],str[BUFSIZ];
	register int i,j;
	struct stat *fs;

	fs=(struct stat *)malloc(sizeof(struct stat));

	for(i=0;i<NUM_DIST;i++) {
		if(dist_list[i].flag_inst) {
			snprintf(buf,sizeof(char)*BUFSIZ,"%s%s/%s.tgz",
				TARGET_MOUNT_POINT,ftp->local_dir,dist_list[i].name);
			snprintf(str,sizeof(char)*BUFSIZ,"cd %s && /usr/bin/tar xvpzf %s",
				TARGET_MOUNT_POINT,buf);
			printf("Extract %s.tgz ...\n",dist_list[i].name);
#ifndef DEBUG
			if(stat(buf,fs)==0) {
				s_popen(str);
				dist_list[i].flag_result= 1;
			}
			else {
				dist_list[i].flag_result= -1;
			}
#else
			s_popen(str);
			dist_list[i].flag_result= 1;
#endif
		}
	}

	free(fs);
	return;
}

#ifdef INSTALLBOOT
void do_installboot(bp)
struct bp_t *bp;
{
	char buf[BUFSIZ];

	snprintf(buf,sizeof(char)*BUFSIZ,"ln -sf %s/boot /boot",TARGET_MOUNT_POINT);
	s_system(buf);

	snprintf(buf,sizeof(char)*BUFSIZ,"/usr/mdec/installboot --root-directory=%s %s",TARGET_MOUNT_POINT, bp->name);
	s_popen(buf);
	return;
}
#endif /* #ifdef INSTALLBOOT */

#ifdef HAVE_GRUB
void wr_menulst(bp)
char *bp;
{
	FILE *fp;
	char buf[BUFSIZ];

#ifndef DEBUG
	snprintf(buf,sizeof(char)*BUFSIZ,"%s/boot/grub/menu.lst",TARGET_MOUNT_POINT);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/tmp/menu.lst");
#endif
	fp=fopen(buf,"w");

	fprintf(fp,"# Boot automatically after 30 secs.\n");
	fprintf(fp,"timeout\t30\n\n");
	fprintf(fp,"# By default, boot the first entry.\n");
	fprintf(fp,"default\t0\n\n");
	fprintf(fp,"# Fallback to the second entry.\n");
	fprintf(fp,"fallback\t1\n\n");
	fprintf(fp,"# For booting SSD/Linux %s/%s\n",SSDRELEASENAME,KERNEL_VERSION);
	fprintf(fp,"title\tSSD/Linux %s/%s\n",SSDRELEASENAME,KERNEL_VERSION);
	fprintf(fp,"root\t(hd%d,%d)\n",getdevnum(bp,7),getlu(bp,8) - 1);
	fprintf(fp,"kernel\t/vmlinuz root=%s\n\n",bp);
	fprintf(fp,"# For booting SSD/Linux %s/%s from FD\n",SSDRELEASENAME,KERNEL_VERSION);
	fprintf(fp,"title\tSSD/Linux %s/%s from FD\n",SSDRELEASENAME,KERNEL_VERSION);
	fprintf(fp,"root\t(fd0)\n");
	fprintf(fp,"kernel\t/bzImage root=/dev/ram\n");
	fprintf(fp,"pause\tInsert instfs floppy disk and type any key.\n");
	fprintf(fp,"initrd\t/initrd.fs.gz\n");

	fclose(fp);
	return;
}
#endif /* #ifdef HAVE_GRUB */

void run_makedev()
{
	char buf[BUFSIZ];

	snprintf(buf,sizeof(char)*BUFSIZ,"cd %s/dev && %s/dev/MAKEDEV generic",
		TARGET_MOUNT_POINT,TARGET_MOUNT_POINT);
	s_popen(buf);
	return;
}

void wr_fstab(pa,num_pat)
struct pa_t **pa;
int num_pat;
{
	FILE *fp;
	char buf[BUFSIZ];
	register int i;

#ifndef DEBUG
	snprintf(buf,sizeof(char)*BUFSIZ,"%s/etc/fstab",TARGET_MOUNT_POINT);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/tmp/fstab");
#endif
	fp=fopen(buf,"w");
	for(i=0;i<(num_pat + 2);i++) {
		if(pa[i]->flag_act) {
			fprintf(fp,"%s\t%s\t%s\t%s\t%d %d\n",
				pa[i]->name,pa[i]->mntp,pa[i]->fst,pa[i]->opt,pa[i]->fck1,pa[i]->fck2);
		}
	}
	fclose(fp);
	return;
}

void wr_rcconf(pccard,dhcp,md)
int pccard,dhcp;
struct md_t *md;
{
	char buf[BUFSIZ];

#if defined(PROBE_PCCARD) || defined(CONF_NETWORK)
	FILE *fp;
#ifndef DEBUG
	snprintf(buf,sizeof(char)*BUFSIZ,"%s/etc/rc.conf",TARGET_MOUNT_POINT);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/tmp/rc.conf");
#endif
	fp=fopen(buf,"a");
#ifdef PROBE_PCCARD
	if(pccard)
		fprintf(fp,"pcmcia=YES\n");
#endif
#ifdef CONF_NETWORK
	if(dhcp)
		fprintf(fp,"dhclient=YES\tdhclient_flags=\"-q %s\"\n",md->name);
#endif
	fclose(fp);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/bin/cp /etc/rc.conf %s/etc/rc.conf",TARGET_MOUNT_POINT);
		s_system(buf);
#endif /* #if defined(PROBE_PCCARD) || defined(CONF_NETWORK) */
	return;
}

void wr_network(md,net)
struct md_t *md;
struct net_t *net;
{
	char buf[BUFSIZ];
	FILE *fp;

#ifdef CONF_NETWORK
#ifndef DEBUG
	snprintf(buf,sizeof(char)*BUFSIZ,"%s/etc/myname",TARGET_MOUNT_POINT);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/tmp/myname");
#endif
	fp=fopen(buf,"w");
	fprintf(fp,"%s\n",net->hostname);
	fclose(fp);

#ifndef DEBUG
	snprintf(buf,sizeof(char)*BUFSIZ,"%s/etc/mygate",TARGET_MOUNT_POINT);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/tmp/mygate");
#endif
	fp=fopen(buf,"w");
	fprintf(fp,"%s\n",net->route);
	fclose(fp);

#ifndef DEBUG
	snprintf(buf,sizeof(char)*BUFSIZ,"%s/etc/ifconfig.%s",TARGET_MOUNT_POINT,md->name);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/tmp/ifconfig.%s",md->name);
#endif
	fp=fopen(buf,"w");
	fprintf(fp,"inet %s broadcast %s netmask %s\n",net->ip,net->cast,net->mask);
	fclose(fp);

#ifndef DEBUG
	snprintf(buf,sizeof(char)*BUFSIZ,"%s/etc/resolv.conf",TARGET_MOUNT_POINT);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/tmp/resolv.conf");
#endif
	fp=fopen(buf,"w");
	fprintf(fp,"domain %s\n",net->domain);
	fprintf(fp,"nameserver %s\n",net->dns);
	fprintf(fp,"search %s\n",net->domain);
	fclose(fp);

#ifndef DEBUG
	snprintf(buf,sizeof(char)*BUFSIZ,"%s/etc/hosts",TARGET_MOUNT_POINT);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/tmp/hosts");
#endif
	fp=fopen(buf,"a");
	fprintf(fp,"%s\t%s.%s\t%s\n",net->ip,net->hostname,net->domain,net->hostname);
	fclose(fp);

#ifndef DEBUG
	snprintf(buf,sizeof(char)*BUFSIZ,"%s/etc/hosts.allow",TARGET_MOUNT_POINT);
#else
	snprintf(buf,sizeof(char)*BUFSIZ,"/tmp/hosts.allow");
#endif
	fp=fopen(buf,"w");
	fprintf(fp,"#ftpd: .%s\n",net->domain);
	fprintf(fp,"#telnetd: .%s\n",net->domain);
	fprintf(fp,"#rshd: .%s\n",net->domain);
	fprintf(fp,"#rlogind: .%s\n",net->domain);
	fprintf(fp,"#rexecd: .%s\n",net->domain);
	fprintf(fp,"#fingerd: .%s\n",net->domain);
	fprintf(fp,"#identd: ALL\n");
	fprintf(fp,"#tftpd: .%s\n",net->domain);
	fprintf(fp,"#rsync: .%s\n",net->domain);
	fclose(fp);
#else
	register int i;

	for (i=0;i<NUM_NET_CONF;i++) {
		if((fp=fopen(net_conf[i],"r"))!=NULL) {
			fclose(fp);
			snprintf(buf,sizeof(char)*BUFSIZ,"/bin/cp %s %s%s",net_conf[i],TARGET_MOUNT_POINT,net_conf[i]);
			s_system(buf);
		} 
	}
#endif /* #ifdef CONF_NETWORK */
	
	return;
}

void do_rminst(ftp)
struct ftp_t *ftp;
{
	register int q;
	char buf[BUFSIZ];

	snprintf(buf,sizeof(char)*BUFSIZ,"Remove %s%s",TARGET_MOUNT_POINT,ftp->local_dir);
	q=isskip(buf);
	if(q) {
		snprintf(buf,sizeof(char)*BUFSIZ,"/bin/rm -rf %s%s",TARGET_MOUNT_POINT,ftp->local_dir);
		s_system(buf);
	}
	return;
}

void do_passwd()
{
	register int q;
	char buf[BUFSIZ];

	q=isskip("Set root passwd");
	if(q) {
		s_system("/usr/bin/passwd");
		snprintf(buf,sizeof(char)*BUFSIZ,"/bin/cp /etc/passwd %s/etc/passwd",TARGET_MOUNT_POINT);
		s_system(buf);
		snprintf(buf,sizeof(char)*BUFSIZ,"/bin/cp /etc/shadow %s/etc/shadow",TARGET_MOUNT_POINT);
		s_system(buf);
		snprintf(buf,sizeof(char)*BUFSIZ,"/bin/chmod 600 %s/etc/passwd",TARGET_MOUNT_POINT);
		s_system(buf);
		snprintf(buf,sizeof(char)*BUFSIZ,"/bin/chmod 600 %s/etc/shadow",TARGET_MOUNT_POINT);
		s_system(buf);
	}
	return;
}

int main()
{
	int exist_root, root_pat,act_md,act_bp;
	int num_hd,num_bp,num_pat,num_md,dhcp,pccard;
	register int i,q;
	struct md_t *md[MAXMD];
	struct hd_t *hd[MAXHDDEV];
	struct pa_t *pa[MAXPAT];
	struct bp_t *bp[MAXBOOTDEV];
	struct net_t *net;
	struct ftp_t *ftp;

	for(i=0;i<MAXMD;i++)
		md[i]=(struct md_t *)malloc(sizeof(struct md_t));

	for(i=0;i<MAXHDDEV;i++)
		hd[i]=(struct hd_t *)malloc(sizeof(struct hd_t));

	for(i=0;i<MAXPAT;i++)
		pa[i]=(struct pa_t *)malloc(sizeof(struct pa_t));

	for(i=0;i<MAXBOOTDEV;i++)
		bp[i]=(struct bp_t *)malloc(sizeof(struct bp_t));

	net=(struct net_t *)malloc(sizeof(struct net_t));
	ftp=(struct ftp_t *)malloc(sizeof(struct ftp_t));

#ifdef PROBE_PCCARD
	pccard=probe_pccard();
#endif
	num_hd=probe_hd(hd);
	num_md=probe_md(md,hd,num_hd);

	if(!num_md) {
		printf("\n\nError: Any install media not availavle.\n");
		exit(1);
	}

	start_msg();

	if(rd_partition(hd,num_hd)) {
		printf("\n\nError: bootable partition for linux not detected.\n");
		printf(    "       run 'fdisk' and set bootable partition first.\n");
		exit(1);
	} 
	num_pat=pat_array(&num_bp,hd,pa,bp,num_hd);
	if(!num_pat) {
		printf("\n\nError: any partition for linux not detected.\n");
		printf(    "       run 'fdisk' and setup partition first.\n");
		exit(1);
	}
	set_partition(pa,num_pat);
	root_pat=set_root_partition(&exist_root,pa,num_pat);

	if(!exist_root) {
		printf("\n\nError: root partition not defined.\n");
		exit(1);
	}

#ifdef INSTALLBOOT
	act_bp=set_boot_partition(bp,num_bp);
#endif

	q=isskip("Taking mkswap and mke2fs.");
	if(q) {
		run_mkswap(pa,num_pat);
		run_mke2fs(pa,num_pat);
	}

	do_mount(pa,num_pat,root_pat);
	set_distributions();
	act_md=set_install_media(md,num_md);

	if(md[act_md]->type) {
		q=isskip("Extract binaries from CDROM.");
		if(q) do_extract_from_cdrom(md[act_md]);
	}
	else {
#ifdef CONF_NETWORK
		if(!(dhcp=set_dhcp(md[act_md]))) {
			set_network(md[act_md],net);
			do_network(md[act_md],net);
		}
#endif
		set_ftp(net,ftp);
		set_proxy(ftp);
		q=isskip("Start fetch binaries and extract.");
		if(q) {
			do_ftp(ftp);
			do_extract_from_ftp(ftp);
		}
	}

#ifdef INSTALLBOOT
	q=isskip("Install boot block.");
	if(q) do_installboot(bp[act_bp]);
#endif
	printf("\n\nMake device files...\n");
	run_makedev();
#ifdef HAVE_GRUB
	printf("\n\nWrite /boot/grub/menu.lst.\n");
	wr_menulst(pa[root_pat]->name);
#endif
	printf("\n\nWrite /etc/fstab.\n");
	wr_fstab(pa,num_pat);
	printf("\n\nModify /etc/rc.conf.\n");
	wr_rcconf(pccard,dhcp,md[act_md]);
	if(!md[act_md]->type) {
		if(!dhcp) {
			q=isskip("Write entered network parameters to /etc.");
			if(q) wr_network(md[act_md],net);
		}
		do_rminst(ftp);
	}
	do_passwd();
	do_umount(pa,num_pat,root_pat);

	printf("\n\nInstallation Completed.\n\n");
	printf("  Good luck...\n");

	exit(0);
}
