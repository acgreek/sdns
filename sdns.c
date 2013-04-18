/* RFC 1034 and 1035 server */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
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
#define LOG(x, ...) { \
	char message[BUFFSIZE];  \
	FILE *F=fopen(DNSlog,"a+");\
	if (F != NULL) {\
		snprintf(message,BUFFSIZE-1,x, ##__VA_ARGS__);\
		logfile(F,message); \
	} \
	fclose(F); \
}


char  question[BUFFSIZE], answer[BUFFSIZE], out[BUFFSIZE];
int ancount,arcount;


struct sockaddr_in cliaddr;
char in_packet[BUFFSIZE], out_packet[BUFFSIZE];

#include "table.h"
void logfile(FILE * F,char * message) {
	static unsigned int messcount=0,  messcount2=0;	// log queue should be lengthened
	static char oldIP[TIMESTAMPSIZE], oldPort[TIMESTAMPSIZE], oldIP2[TIMESTAMPSIZE], oldPort2[TIMESTAMPSIZE];
	static char oldtimestamp[TIMESTAMPSIZE], oldtimestamp2[TIMESTAMPSIZE], lastmess[BUFFSIZE], lastmess2[BUFFSIZE];

	char timestamp[TIMESTAMPSIZE];
	time_t t=time(NULL);
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

void dumppacket(unsigned inpacketsize) {
	FILE *F;
	F=fopen(DNSlog,"a+");
	if (F != NULL) {
		char message[BUFFSIZE];
		snprintf(message,sizeof(message)-1, "Dump: (%d)", inpacketsize);
		unsigned i;
		for (i = 0; i < inpacketsize; i++) {
			unsigned int c=in_packet[i];
			char newmess[8];
			snprintf(newmess,7," %X", c);
			strcat(message,newmess);
		}
		logfile(F, message);
	}			/* This sprintf makes RECVSIZE*3 + 8 the minimum size for BUFFSIZE */
	fclose(F);
}

void setResponse(HEADER *out_head,int rd, uint rcode, int ancount,int qdcount, int arcount) {
	out_head->rcode = rcode;		/* no such host or domain (we are authoritive) */
	out_head->ancount = ancount;	/* 0 answers (assumed) */
	out_head->qdcount = qdcount;	/* 0 question only (assumed) */
	out_head->nscount = 0x00;	/* 0 number of name server resource records in authority record section */
	out_head->arcount = arcount;	/* 0 number or resource records in the additional records section */
	out_head->qr = 1;		/* Response */
	out_head->opcode = 0;		/* Opcode */
	out_head->aa = 1;		/* Authoritative */
	out_head->tc = 0;		/* Not truncated */
	out_head->rd = rd;	/* Recursion desired is to be copied over (I don't want it...) */
	out_head->ra = 0;		/* No recursion available */
	out_head->unused = 0;		/* Unset unused bits */
}

int buildListenSocket(int argc, char *argv[]) {
	int sockfd;
	struct sockaddr_in servaddr;
	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
		LOG("Can't create socket");
		fprintf(stderr,"Can't create socket\n");
		return -1;
	}
	if (argc > 1) {
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
	int retval = bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (retval == -1) {
		LOG("Can't Bind");
		fprintf(stderr,"Can't Bind\n");
		return -1;
	}
	return sockfd;
}

void listenAndRespondLoop(int sockfd) {
	while (1) {
		int i;
		for (i = 0; i < BUFFSIZE; i++) {
			out_packet[i] = '\0';
			in_packet[i] = '\0';
			question[i] = '\0';
			answer[i] = '\0';
		}
		socklen_t len = sizeof(cliaddr);
		int size=recvfrom(sockfd, in_packet, RECVSIZE, 0, (struct sockaddr *) &cliaddr, (socklen_t *)&len);
		//unsigned int inpacketsize=size;
		if (size > RECVSIZE) {
		//	inpacketsize=RECVSIZE;
			LOG("System call screwed up - packet too big");
			continue;
		}
		if (size <= HEADERLENGTH) {
			LOG("packet too small");
			continue;
		}
		HEADER *in_head = (HEADER*) &in_packet;
		HEADER *out_head = (HEADER*) &out_packet;
		if (in_head->opcode != QUERY) {
			LOG("Not a query (opcode != 0)");
			continue;
		}
		if (in_head->qr != 0) {
			LOG("Not a query (qr != 0)");
			continue;
		}
		if (in_head->qdcount == 0) {
			LOG("Question count == 0");
			continue;
		}
		unsigned int qindex = 0;
		size = 0;
		char *read_offset = in_packet + HEADERLENGTH;
		while(read_offset[size] != '\0'){		/* pre-zero'ed packet will run into a zero after end of packet if nowhere else */
			unsigned char charstilldot = (unsigned char)read_offset[size++];	/* the size so far... */
			if ((qindex != 0) && (charstilldot != 0))
				question[qindex++] = '.';
			while (charstilldot--) {
				question[qindex++] = tolower(read_offset[size++]);
			}
		}
		size++;	/* there could be real hazardous characters in the question... */
		int qtype = read_offset[size] * 256 + read_offset[size + 1]; /* Qtype */
		if (size <= 1) {
			LOG("Illegal name size (too small)");
			continue;
		}
		if (size > 255) {
			LOG("Illegal name size (too big)");
			continue;
		}
		unsigned int port=cliaddr.sin_port;
		if (port == NAMESERVER_PORT) {
			LOG("Port 53 as source");
			continue;
		} /* does zone transfer use port 53 source?*/
		out_head->id = in_head->id;
		int ans_size = translate(qtype);
		int ignore = 0;
		char *reqtype;
		switch (qtype) {
			case 1:	reqtype="A";ignore=0;break;
			case 2:	reqtype="NS";ignore=0;break;
			case 3:	reqtype="MD(old)";ignore=NOTIMP;break;
			case 4:	reqtype="MF(old)";ignore=NOTIMP;break;
			case 5:	reqtype="CNAME";ignore=0;break;
			case 6:	reqtype="SOA";ignore=REFUSED;break;
			case 7:	reqtype="MB(old)";ignore=NOTIMP;break;
			case 8:	reqtype="MG(old)";ignore=NOTIMP;break;
			case 9:	reqtype="MR(old)";ignore=NOTIMP;break;
			case 10:reqtype="NULL";ignore=NOTIMP;break;
			case 11:reqtype="WKS";ignore=NOTIMP;break;
			case 12:reqtype="PTR";ignore=0;break;
			case 13:reqtype="HINFO";ignore=REFUSED;break;
			case 14:reqtype="MINFO";ignore=REFUSED;break;
			case 15:reqtype="MX";ignore=0;break;
			case 16:reqtype="TXT";ignore=REFUSED;break;
			case 17:reqtype="RespniblePerson(exper)";ignore=REFUSED;break;
			case 18:reqtype="AndrewFS(exper)";ignore=NOTIMP;break;
			case 19:reqtype="X.25(exper)";ignore=NOTIMP;break;
			case 20:reqtype="ISDN(exper)";ignore=NOTIMP;break;
			case 21:reqtype="RouteThrough(exper)";ignore=NOTIMP;break;
			case 22:reqtype="NSAP(exper)";ignore=NOTIMP;break;
			case 23:reqtype="NSAP-PTR(exper)";ignore=NOTIMP;break;
			case 24:reqtype="SecSig";ignore=REFUSED;break;
			case 25:reqtype="SecKey";ignore=REFUSED;break;
			case 26:reqtype="X.400(exper)";ignore=NOTIMP;break;
			case 27:reqtype="GPS";ignore=REFUSED;break;
			case 28:reqtype="IPV6-P";ignore=-1;break;
			case 29:reqtype="Loc";ignore=REFUSED;break;
			case 30:reqtype="NextDom";ignore=NOTIMP;break;
			case 31:reqtype="Endpoint";ignore=NOTIMP;break;
			case 32:reqtype="Nimrod/SMB-NS";ignore=NOTIMP;break;
			case 33:reqtype="ServerSel/SMB-NodeStat";ignore=NOTIMP;break;
			case 34:reqtype="ATMad";ignore=NOTIMP;break;
			case 35:reqtype="NameAuth";ignore=NOTIMP;break;
			case 36:reqtype="KeyExch";ignore=REFUSED;break;
			case 37:reqtype="CERT";ignore=REFUSED;break;
			case 38:reqtype="IPV6-A";ignore=-1;break;
			case 39:reqtype="Dname";ignore=NOTIMP;break;
			case 40:reqtype="SINK";ignore=NOTIMP;break;
			case 41:reqtype="OPT";ignore=NOTIMP;break;
			case 42:reqtype="APL";ignore=REFUSED;break;
			case 100:reqtype="UINFO";ignore=REFUSED;break;
			case 101:reqtype="UID";ignore=REFUSED;break;
			case 102:reqtype="GID";ignore=REFUSED;break;
			case 103:reqtype="UNSPEC";ignore=REFUSED;break;
			case 249: case -7:reqtype="TransKey";ignore=REFUSED;break;
			case 250: case -6:reqtype="TransSig";ignore=REFUSED;break;
			case 251: case -5:reqtype="IncXfer";ignore=REFUSED;break;
			case 252: case -4:reqtype="AXFR";ignore=REFUSED;break;
			case 253: case -3:reqtype="MAILB";ignore=REFUSED;break;
			case 254: case -2:reqtype="MAILA";ignore=REFUSED;break;
			case 255: case -1:reqtype="ALL";ignore=0;break;
			default:reqtype="Unknown";ignore=NOTIMP;break;
		}
		if (ans_size == 0) {
			LOG("lookup %s (%s:%d) - not in table", question, reqtype, qtype);
			setResponse(out_head,in_head->rd, 3, 0,0,0);
			size=-4;
		}			/* no question, no answer, no problem */
		else if (ignore == -1) {
			LOG("Ignoring %s (%s:%d) => %s", question, reqtype, qtype, out);
		} else if (ignore != 0) {
			LOG("Code %s (%s:%d) => %d", question, reqtype, qtype, ignore);
			setResponse(out_head,in_head->rd, ignore, 0,0,0);
			size=-4;
		}
		else	{
			LOG("lookup %s (%s:%d) => %s", question, reqtype, qtype, out);
			setResponse(out_head,in_head->rd, 0, htons(ancount),0x100,htons(arcount));
			memcpy(out_packet + HEADERLENGTH, in_packet + HEADERLENGTH, size + 4); /* Copy question section into out packet */
			read_offset = out_packet + size + HEADERLENGTH + 4; out_head->rcode = 0; /* Point read_offset to answer section */
			memcpy(read_offset, answer, ans_size);}     /* Copy answer section into out packet */
		if (ignore != -1) {
			int retval = sendto(sockfd,&out_packet,(HEADERLENGTH + size + 4 + ans_size), 0, (const struct sockaddr *) &cliaddr, len);
			if (retval == -1)
				LOG("could not send");
		}
	}
}

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
	LOG("Starting sdns");
	int sockfd = buildListenSocket(argc,argv);
	if (-1 == sockfd)
		exit(EXIT_FAILURE);
	listenAndRespondLoop(sockfd);
	exit(EXIT_SUCCESS);
}
