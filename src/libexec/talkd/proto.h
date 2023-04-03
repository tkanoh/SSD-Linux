/*	$ssdlinux: proto.h,v 1.1 2002/05/22 18:04:42 kanoh Exp $	*/
/* quirks for repairs.c */

#define QUIRK_NONE   0
#define QUIRK_OTALK  1

struct sockaddr;
struct CtlMessage;
struct CtlResponse;

extern char ourhostname[];

/* print.c */
void print_request(const char *cp, const struct CtlMessage *mp);
void print_response(const char *cp, const struct CtlResponse *rp);
void print_broken_packet(const char *pack, size_t len, struct sockaddr *);
void debug(const char *fmt, ...);
void set_debug(int logging, int badpackets);

/* table.c */
void insert_table(struct CtlMessage *request, struct CtlResponse *response);
struct CtlMessage *find_request(struct CtlMessage *request);
struct CtlMessage *find_match(struct CtlMessage *request);

/* repairs.c */
int rationalize_packet(char *buf, socklen_t len, socklen_t maxlen, 
		       struct sockaddr *);
socklen_t irrationalize_reply(char *buf, socklen_t maxbuf, int quirk);

/* other */
/*
int announce(struct CtlMessage *request, const char *remote_machine);
*/
void process_request(struct CtlMessage *mp, struct CtlResponse *rp, const char *fromhost);
int new_id(void);
int delete_invite(unsigned id_num);

