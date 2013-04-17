/* RFC 1034 and 1035 server */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <linux/in.h>
#include <string.h>   /*for memcpy */
#include <ctype.h>
#include <arpa/nameser.h>  /*for HEADER structure */
#include <time.h>

//#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h>


#define HEADERLENGTH 12
#define RECVSIZE 512
#define BUFFSIZE RECVSIZE*4 /* fc - BUFFSIZE better be > 255 bytes bigger than max ethernet frame */
/* fc - we really need 3*RECVSIZE + 12 (or so) for a message as well */
#define BYTESIZE 255
#define	TIMESTAMPSIZE 64
#define DNSPORT  0x3500
#define DNSlog "logfile"
#define LOG1(x) {F=fopen(DNSlog,"a+");if (F != NULL) {sprintf(message,x);logfile(F);} fclose(F);dumppacket();}
#define LOG2(y,z) {F=fopen(DNSlog,"a+");if (F != NULL) {sprintf(message,y,z); logfile(F);} fclose(F);}
#define LOG3(x,y,z) {F=fopen(DNSlog,"a+");if (F != NULL) {sprintf(message,x,y,z); logfile(F);} fclose(F);}
#define LOG4(w,x,y,z) {F=fopen(DNSlog,"a+");if (F != NULL) {sprintf(message,w,x,y,z); logfile(F);} fclose(F);}
#define LOG5(v,w,x,y,z) {F=fopen(DNSlog,"a+");if (F != NULL) {sprintf(message,v,w,x,y,z); logfile(F);} fclose(F);}

unsigned int qindex, messcount,  messcount2, port;	// log queue should be lengthened
char in_packet[BUFFSIZE], timestamp[TIMESTAMPSIZE], out_packet[BUFFSIZE], question[BUFFSIZE], answer[BUFFSIZE],
	 oldIP[TIMESTAMPSIZE], oldPort[TIMESTAMPSIZE], oldIP2[TIMESTAMPSIZE], oldPort2[TIMESTAMPSIZE],
	 oldtimestamp[TIMESTAMPSIZE], oldtimestamp2[TIMESTAMPSIZE], lastmess[BUFFSIZE], lastmess2[BUFFSIZE],
	 *read_offset, message[BUFFSIZE], out[BUFFSIZE], newmess[8], *reqtype;
unsigned char charstilldot, c, d;
time_t *tloc, t;
int i, size, inpacketsize, ans_size, retval, sockfd, logcount, ancount, arcount, qtype, ignore;
FILE *F;
/* fc HEADER *in_head, *out_head; socklen_t len; struct sockaddr_in servaddr, cliaddr;*/
HEADER *in_head, *out_head; socklen_t len; struct sockaddr_in servaddr, cliaddr;

#include "table.h"

void logfile(FILE * F) {
	t=time(NULL);
	strftime(timestamp, 20, "%Y/%m/%d %T", localtime(&t));
	if (!strcmp(message, lastmess)) {
		messcount++;
		if (messcount == 10 || messcount == 50 || messcount == 100 || messcount == 1000 || messcount == 2000 || messcount == 5000)
			fprintf(F, "%s %s:%d sdns %s (%d times)\n",timestamp,inet_ntoa(cliaddr.sin_addr),(cliaddr.sin_port),lastmess,messcount);
		strncpy(oldtimestamp,timestamp,sizeof(oldtimestamp) -1 );}
	else if (!strcmp(message, lastmess2)) {
		messcount2++;
		if (messcount2 == 10 || messcount2 == 50 || messcount2 == 100 || messcount2 == 1000 || messcount2 == 2000 || messcount2 == 5000)
			fprintf(F, "%s %s:%d sdns %s (%d times)\n",timestamp,inet_ntoa(cliaddr.sin_addr),(cliaddr.sin_port),lastmess2,messcount2);
		strncpy(oldtimestamp2,timestamp,sizeof(oldtimestamp) -1);}
	else    {
		if (messcount2 > 1)
			fprintf(F, "%s %s:%s sdns %s (%d times in total)\n",oldtimestamp2,oldIP2,oldPort2,lastmess2,messcount2);
		messcount2=messcount;
		strncpy(lastmess2,lastmess, sizeof(lastmess2)-1) ;
		strncpy(oldIP2, oldIP,sizeof(oldIP2)-1);
		strncpy(oldPort2,oldPort,sizeof(oldPort2)-1);
		strncpy(oldtimestamp2,oldtimestamp,sizeof(oldtimestamp) -1);
		messcount = 1;
		strncpy(lastmess,message,sizeof(lastmess)-1);
		sprintf(oldIP,"%s",inet_ntoa(cliaddr.sin_addr));
		sprintf(oldPort,"%d",(cliaddr.sin_port));
		strncpy(oldtimestamp,timestamp,sizeof(oldtimestamp) -1);
		fprintf(F,"%s %s:%d sdns %s\n",timestamp,inet_ntoa(cliaddr.sin_addr),(cliaddr.sin_port),message);}
}

void dumppacket() {
	F=fopen(DNSlog,"a+");
	if (F != NULL) {
		sprintf(message,"Dump: (%d)", inpacketsize);
		for (i = 0; i < inpacketsize; i++) {
			c=in_packet[i];sprintf(newmess," %X", c);strcat(message,newmess);
		}
		logfile(F);}			/* This sprintf makes RECVSIZE*3 + 8 the minimum size for BUFFSIZE */
	fclose(F);
}

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
	LOG1("Starting sdns");
	lastmess[0] = '\0';
	strncpy(lastmess2, "", sizeof(lastmess2) -1);
	messcount = 0;messcount2 = 0; logcount=0;
	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
		LOG1("Can't create socket");printf("Can't create socket\n");
		exit(EXIT_FAILURE);
	}
	if (argv[1]) {
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = inet_addr(argv[1]);
		servaddr.sin_port = DNSPORT;
	} else {
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = 0;
		servaddr.sin_port = DNSPORT;
	}
	retval = bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (retval == -1) {
		LOG1("Can't Bind");printf("Can't Bind\n");
		exit(EXIT_FAILURE);
	}
	while (1) {
		for (i = 0; i < BUFFSIZE; i++) {
			out_packet[i] = '\0';
			in_packet[i] = '\0';
			question[i] = '\0';
			answer[i] = '\0';
		}
		len = sizeof(cliaddr);
		size=recvfrom(sockfd, in_packet, RECVSIZE, 0, (struct sockaddr *) &cliaddr, (socklen_t *)&len);
		inpacketsize=size;
		if (size > RECVSIZE) {
			inpacketsize=RECVSIZE;LOG1("System call screwed up - packet too big"); continue;}
		if (size <= HEADERLENGTH) {
			LOG1("packet too small");
			continue;
		}
		in_head = (HEADER*) &in_packet;
		out_head = (HEADER*) &out_packet;
		if (in_head->opcode != QUERY) {
			LOG1("Not a query (opcode != 0)");
			continue;
		}
		if (in_head->qr != 0) {
			LOG1("Not a query (qr != 0)");
			continue;
		}
		if (in_head->qdcount == 0) {
			LOG1("Question count == 0");
			continue;
		}
		qindex = 0; size = 0; read_offset = in_packet + HEADERLENGTH;
		while(read_offset[size] != '\0'){		/* pre-zero'ed packet will run into a zero after end of packet if nowhere else */
			charstilldot = (unsigned char)read_offset[size++];	/* the size so far... */
			if ((qindex != 0) && (charstilldot != 0))
				question[qindex++] = '.';
			while (charstilldot--) {
				question[qindex++] = tolower(read_offset[size++]);
			}
		}
		size++;	/* there could be real hazardous characters in the question... */
		qtype = read_offset[size] * 256 + read_offset[size + 1]; /* Qtype */
		if (size <= 1) {
			LOG1("Illegal name size (too small)");
			continue;
		}
		if (size > 255) {
			LOG1("Illegal name size (too big)");
			continue;
		}
		port=cliaddr.sin_port;
		if (port == NAMESERVER_PORT) {
			LOG1("Port 53 as source");
			continue;
		} /* does zone transfer use port 53 source?*/
		out_head->id = in_head->id;
		ans_size = translate(qtype);
		switch (qtype) {
			case 1:	reqtype="A";ignore=0;break;
			case 2:		reqtype="NS";ignore=0;break;
			case 3:		reqtype="MD(old)";ignore=NOTIMP;break;
			case 4:		reqtype="MF(old)";ignore=NOTIMP;break;
			case 5:		reqtype="CNAME";ignore=0;break;
			case 6:		reqtype="SOA";ignore=REFUSED;break;
			case 7:		reqtype="MB(old)";ignore=NOTIMP;break;
			case 8:		reqtype="MG(old)";ignore=NOTIMP;break;
			case 9:		reqtype="MR(old)";ignore=NOTIMP;break;
			case 10:	reqtype="NULL";ignore=NOTIMP;break;
			case 11:	reqtype="WKS";ignore=NOTIMP;break;
			case 12:	reqtype="PTR";ignore=0;break;
			case 13:	reqtype="HINFO";ignore=REFUSED;break;
			case 14:	reqtype="MINFO";ignore=REFUSED;break;
			case 15:	reqtype="MX";ignore=0;break;
			case 16:	reqtype="TXT";ignore=REFUSED;break;
			case 17:	reqtype="RespniblePerson(exper)";ignore=REFUSED;break;
			case 18:	reqtype="AndrewFS(exper)";ignore=NOTIMP;break;
			case 19:	reqtype="X.25(exper)";ignore=NOTIMP;break;
			case 20:	reqtype="ISDN(exper)";ignore=NOTIMP;break;
			case 21:	reqtype="RouteThrough(exper)";ignore=NOTIMP;break;
			case 22:	reqtype="NSAP(exper)";ignore=NOTIMP;break;
			case 23:	reqtype="NSAP-PTR(exper)";ignore=NOTIMP;break;
			case 24:	reqtype="SecSig";ignore=REFUSED;break;
			case 25:	reqtype="SecKey";ignore=REFUSED;break;
			case 26:	reqtype="X.400(exper)";ignore=NOTIMP;break;
			case 27:	reqtype="GPS";ignore=REFUSED;break;
			case 28:	reqtype="IPV6-P";ignore=-1;break;
			case 29:	reqtype="Loc";ignore=REFUSED;break;
			case 30:	reqtype="NextDom";ignore=NOTIMP;break;
			case 31:	reqtype="Endpoint";ignore=NOTIMP;break;
			case 32:	reqtype="Nimrod/SMB-NS";ignore=NOTIMP;break;
			case 33:	reqtype="ServerSel/SMB-NodeStat";ignore=NOTIMP;break;
			case 34:	reqtype="ATMad";ignore=NOTIMP;break;
			case 35:	reqtype="NameAuth";ignore=NOTIMP;break;
			case 36:	reqtype="KeyExch";ignore=REFUSED;break;
			case 37:	reqtype="CERT";ignore=REFUSED;break;
			case 38:	reqtype="IPV6-A";ignore=-1;break;
			case 39:	reqtype="Dname";ignore=NOTIMP;break;
			case 40:	reqtype="SINK";ignore=NOTIMP;break;
			case 41:	reqtype="OPT";ignore=NOTIMP;break;
			case 42:	reqtype="APL";ignore=REFUSED;break;
			case 100:	reqtype="UINFO";ignore=REFUSED;break;
			case 101:	reqtype="UID";ignore=REFUSED;break;
			case 102:	reqtype="GID";ignore=REFUSED;break;
			case 103:	reqtype="UNSPEC";ignore=REFUSED;break;
			case 249: case -7:	reqtype="TransKey";ignore=REFUSED;break;
			case 250: case -6:	reqtype="TransSig";ignore=REFUSED;break;
			case 251: case -5:	reqtype="IncXfer";ignore=REFUSED;break;
			case 252: case -4:	reqtype="AXFR";ignore=REFUSED;break;
			case 253: case -3:	reqtype="MAILB";ignore=REFUSED;break;
			case 254: case -2:	reqtype="MAILA";ignore=REFUSED;break;
			case 255: case -1:	reqtype="ALL";ignore=0;break;
			default:	reqtype="Unknown";ignore=NOTIMP;break;
		}
		if (ans_size == 0) {
			LOG4("lookup %s (%s:%d) - not in table", question, reqtype, qtype);
			out_head->rcode = 3;		/* no such host or domain (we are authoritive) */
			out_head->ancount = 0x00;	/* 0 answers (assumed) */
			out_head->qdcount = 0x00;	/* 0 question only (assumed) */
			out_head->nscount = 0x00;	/* 0 number of name server resource records in authority record section */
			out_head->arcount = 0x00;	/* 0 number or resource records in the additional records section */
			out_head->qr = 1;		/* Response */
			out_head->opcode = 0;		/* Opcode */
			out_head->aa = 1;		/* Authoritative */
			out_head->tc = 0;		/* Not truncated */
			out_head->rd = in_head->rd;	/* Recursion desired is to be copied over (I don't want it...) */
			out_head->ra = 0;		/* No recursion available */
			out_head->unused = 0;		/* Unset unused bits */
			size=-4;}			/* no question, no answer, no problem */
		else if (ignore == -1) {LOG5("Ignoring %s (%s:%d) => %s", question, reqtype, qtype, out);}
		else if (ignore != 0) {LOG5("Code %s (%s:%d) => %d", question, reqtype, qtype, ignore);
			out_head->rcode = ignore;       /* Response code - Per above */
			out_head->ancount = 0x00;	/* 0 answers (assumed) */
			out_head->qdcount = 0x00;	/* 0 question only (assumed) */
			out_head->nscount = 0x00;	/* 0 number of name server resource records in authority record section */
			out_head->arcount = 0x00;	/* 0 number or resource records in the additional records section */
			out_head->qr = 1;		/* Response */
			out_head->opcode = 0;		/* Opcode */
			out_head->aa = 1;		/* Authoritative */
			out_head->tc = 0;		/* Not truncated */
			out_head->rd = in_head->rd;	/* Recursion desired is to be copied over (I don't want it...) */
			out_head->ra = 0;		/* No recursion available */
			out_head->unused = 0;		/* Unset unused bits */
			size=-4;}			/* no question, no answer, no problem */
		else	{
			LOG5("lookup %s (%s:%d) => %s", question, reqtype, qtype, out);
			out_head->rcode = 0;            /* Response code - no error indication */
			out_head->ancount = htons(ancount);	/* ancount answers */
			out_head->qdcount = 0x100;	/* 1 question only (assumed) */
			out_head->nscount = 0x00;	/* 0 number of name server resource records in authority record section */
			out_head->arcount = htons(arcount);	/* 0 number or resource records in the additional records section */
			out_head->qr = 1;		/* Response */
			out_head->opcode = 0;		/* Opcode */
			out_head->aa = 1;		/* Authoritative */
			out_head->tc = 0;		/* Not truncated */
			out_head->rd = in_head->rd;	/* Recursion desired is to be copied over (I don't want it...) */
			out_head->ra = 0;		/* No recursion available */
			out_head->unused = 0;		/* Unset unused bits */
			memcpy(out_packet + HEADERLENGTH, in_packet + HEADERLENGTH, size + 4); /* Copy question section into out packet */
			read_offset = out_packet + size + HEADERLENGTH + 4; out_head->rcode = 0; /* Point read_offset to answer section */
			memcpy(read_offset, answer, ans_size);}     /* Copy answer section into out packet */
		if (ignore != -1) {
			retval = sendto(sockfd,&out_packet,(HEADERLENGTH + size + 4 + ans_size), 0, (const struct sockaddr *) &cliaddr, len);
			if (retval == -1)
				LOG1("could not send");
		}
	}
	exit(EXIT_SUCCESS);
}
