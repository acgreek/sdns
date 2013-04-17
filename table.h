/* table.h - Hostname/IP table initialization file for sdns.c */

#ifndef _SDNS_TABLE_H
#define _SDNS_TABLE_H
#include <stdio.h>
#include <string.h>

extern char question[];
extern char out[];
extern char answer[];
extern int account, ancount,arcount ;
/* translate sets the string 'answer' equal to the answer of the query,
   sets ancount equal to the number of answers in the answer string, and
   returns the length of the answer string */
int translate(unsigned short int qtype)
{
	if (	!strcmp(question, "1.0.0.127.in-addr.arpa") ||
		!strcmp(question, "127.0.0.1") ||
		!strcmp(question, "localhost") ||
		!strcmp(question, "localhost.localdomain") ) {
		if (qtype == 1) {
			strcpy(out,"localhost.localdomain");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 127, 0, 0, 1, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 11, 9, 108, 111, 99, 97, 108, 104, 111, 115, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 23, 9, 108, 111, 99, 97, 108, 104, 111, 115, 116, 11, 108, 111, 99, 97, 108, 100, 111, 109, 97, 105, 110, 0);
			ancount = 1;
			arcount = 2;
			return 74; }
		else if (qtype == 15) {
			strcpy(out,"localhost.localdomain");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 13, 0, 0, 9, 108, 111, 99, 97, 108, 104, 111, 115, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 127, 0, 0, 1, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 23, 9, 108, 111, 99, 97, 108, 104, 111, 115, 116, 11, 108, 111, 99, 97, 108, 100, 111, 109, 97, 105, 110, 0);
			ancount = 1;
			arcount = 2;
			return 76; }
		else {
			strcpy(out,"127.0.0.1");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 11, 9, 108, 111, 99, 97, 108, 104, 111, 115, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 127, 0, 0, 1, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 23, 9, 108, 111, 99, 97, 108, 104, 111, 115, 116, 11, 108, 111, 99, 97, 108, 100, 111, 109, 97, 105, 110, 0);
			ancount = 1;
			arcount = 2;
			return 74; } }

	if (	!strcmp(question, "146.156.60.66.in-addr.arpa") ||
		!strcmp(question, "66.60.156.146") ||
		!strcmp(question, "unhca.com") ||
		!strcmp(question, "www.unhca.com") ||
		!strcmp(question, "dns2.all.net") ) {
		if (qtype == 1) {
			strcpy(out,"www.unhca.com");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 66, 60, 156, 146, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 11, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 119, 119, 119, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 100, 110, 115, 50, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 3;
			return 92; }
		else if (qtype == 15) {
			strcpy(out,"www.unhca.com");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 13, 0, 0, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 66, 60, 156, 146, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 119, 119, 119, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 100, 110, 115, 50, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 3;
			return 94; }
		else {
			strcpy(out,"66.60.156.146");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 11, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 66, 60, 156, 146, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 119, 119, 119, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 100, 110, 115, 50, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 3;
			return 92; } }

	if (	!strcmp(question, "75.156.0.65.in-addr.arpa") ||
		!strcmp(question, "65.0.156.75") ||
		!strcmp(question, "fc2.all.net") ||
		!strcmp(question, "fc2.unhca.com") ||
		!strcmp(question, "dns1.all.net") ||
		!strcmp(question, "simulator.all.net") ||
		!strcmp(question, "responder.all.net") ||
		!strcmp(question, "game.all.net") ) {
		if (qtype == 1) {
			strcpy(out,"fc2.unhca.com");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 75, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 50, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 50, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 100, 110, 115, 49, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 19, 9, 115, 105, 109, 117, 108, 97, 116, 111, 114, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 19, 9, 114, 101, 115, 112, 111, 110, 100, 101, 114, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 103, 97, 109, 101, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 6;
			return 182; }
		else if (qtype == 15) {
			strcpy(out,"fc2.unhca.com");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 15, 0, 0, 3, 102, 99, 50, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 75, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 50, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 100, 110, 115, 49, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 19, 9, 115, 105, 109, 117, 108, 97, 116, 111, 114, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 19, 9, 114, 101, 115, 112, 111, 110, 100, 101, 114, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 103, 97, 109, 101, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 6;
			return 184; }
		else {
			strcpy(out,"65.0.156.75");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 50, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 75, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 50, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 100, 110, 115, 49, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 19, 9, 115, 105, 109, 117, 108, 97, 116, 111, 114, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 19, 9, 114, 101, 115, 112, 111, 110, 100, 101, 114, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 103, 97, 109, 101, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 6;
			return 182; } }

	if (	!strcmp(question, "76.156.0.65.in-addr.arpa") ||
		!strcmp(question, "65.0.156.76") ||
		!strcmp(question, "fc.all.net") ||
		!strcmp(question, "fc.unhca.com") ||
		!strcmp(question, "fc3.all.net") ||
		!strcmp(question, "fc3.unhca.com") ||
		!strcmp(question, "games.all.net") ) {
		if (qtype == 1) {
			strcpy(out,"fc.unhca.com");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 76, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 12, 2, 102, 99, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 2, 102, 99, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 51, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 51, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 103, 97, 109, 101, 115, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 5;
			return 145; }
		else if (qtype == 15) {
			strcpy(out,"fc.unhca.com");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 14, 0, 0, 2, 102, 99, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 76, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 2, 102, 99, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 51, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 51, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 103, 97, 109, 101, 115, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 5;
			return 147; }
		else {
			strcpy(out,"65.0.156.76");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 12, 2, 102, 99, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 76, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 2, 102, 99, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 51, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 51, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 103, 97, 109, 101, 115, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 5;
			return 145; } }

	if (	!strcmp(question, "77.156.0.65.in-addr.arpa") ||
		!strcmp(question, "65.0.156.77") ||
		!strcmp(question, "totful.com") ||
		!strcmp(question, "fc4.all.net") ||
		!strcmp(question, "fc4.unhca.com") ) {
		if (qtype == 1) {
			strcpy(out,"fc4.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 77, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 12, 6, 116, 111, 116, 102, 117, 108, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 52, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 52, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0);
			ancount = 1;
			arcount = 3;
			return 92; }
		else if (qtype == 15) {
			strcpy(out,"fc4.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 14, 0, 0, 6, 116, 111, 116, 102, 117, 108, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 77, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 52, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 52, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0);
			ancount = 1;
			arcount = 3;
			return 94; }
		else {
			strcpy(out,"65.0.156.77");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 12, 6, 116, 111, 116, 102, 117, 108, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 77, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 52, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 52, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0);
			ancount = 1;
			arcount = 3;
			return 92; } }

	if (	!strcmp(question, "78.156.0.65.in-addr.arpa") ||
		!strcmp(question, "65.0.156.78") ||
		!strcmp(question, "fc5.all.net") ||
		!strcmp(question, "fc5.unhca.com") ) {
		if (qtype == 1) {
			strcpy(out,"fc5.unhca.com");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 78, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 53, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 53, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0);
			ancount = 1;
			arcount = 2;
			return 68; }
		else if (qtype == 15) {
			strcpy(out,"fc5.unhca.com");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 15, 0, 0, 3, 102, 99, 53, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 78, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 53, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0);
			ancount = 1;
			arcount = 2;
			return 70; }
		else {
			strcpy(out,"65.0.156.78");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 53, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 78, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 53, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0);
			ancount = 1;
			arcount = 2;
			return 68; } }

	if (	!strcmp(question, "79.156.0.65.in-addr.arpa") ||
		!strcmp(question, "65.0.156.79") ||
		!strcmp(question, "hipaa.unhca.com") ||
		!strcmp(question, "fc6.all.net") ||
		!strcmp(question, "fc6.unhca.com") ||
		!strcmp(question, "hipaa.all.net") ||
		!strcmp(question, "hippa.unhca.com") ||
		!strcmp(question, "hippa.all.net") ) {
		if (qtype == 1) {
			strcpy(out,"fc6.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 79, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 17, 5, 104, 105, 112, 97, 97, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 54, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 54, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 104, 105, 112, 97, 97, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 17, 5, 104, 105, 112, 112, 97, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 104, 105, 112, 112, 97, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 6;
			return 180; }
		else if (qtype == 15) {
			strcpy(out,"fc6.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 19, 0, 0, 5, 104, 105, 112, 97, 97, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 79, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 54, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 54, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 104, 105, 112, 97, 97, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 17, 5, 104, 105, 112, 112, 97, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 104, 105, 112, 112, 97, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 6;
			return 182; }
		else {
			strcpy(out,"65.0.156.79");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 17, 5, 104, 105, 112, 97, 97, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 79, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 102, 99, 54, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 3, 102, 99, 54, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 104, 105, 112, 97, 97, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 17, 5, 104, 105, 112, 112, 97, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 104, 105, 112, 112, 97, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 6;
			return 180; } }

	if (	!strcmp(question, "1.229.7.204.in-addr.arpa") ||
		!strcmp(question, "204.7.229.1") ||
		!strcmp(question, "my.all.net") ) {
		if (qtype == 1) {
			strcpy(out,"");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 204, 7, 229, 1, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 12, 2, 109, 121, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 1;
			return 40; }
		else if (qtype == 15) {
			strcpy(out,"");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 14, 0, 0, 2, 109, 121, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 204, 7, 229, 1);
			ancount = 1;
			arcount = 1;
			return 42; }
		else {
			strcpy(out,"204.7.229.1");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 12, 2, 109, 121, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 204, 7, 229, 1);
			ancount = 1;
			arcount = 1;
			return 40; } }

	if (	!strcmp(question, "215.12.181.204.in-addr.arpa") ||
		!strcmp(question, "204.181.12.215") ||
		!strcmp(question, "all.net") ||
		!strcmp(question, "www.all.net") ||
		!strcmp(question, "localhost") ||
		!strcmp(question, "kryptonite.highspeedweb.net") ) {
		if (qtype == 1) {
			strcpy(out,"www.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 204, 181, 12, 215, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 9, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 119, 119, 119, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 11, 9, 108, 111, 99, 97, 108, 104, 111, 115, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 29, 10, 107, 114, 121, 112, 116, 111, 110, 105, 116, 101, 12, 104, 105, 103, 104, 115, 112, 101, 101, 100, 119, 101, 98, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 4;
			return 126; }
		else if (qtype == 15) {
			strcpy(out,"www.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 11, 0, 0, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 204, 181, 12, 215, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 119, 119, 119, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 11, 9, 108, 111, 99, 97, 108, 104, 111, 115, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 29, 10, 107, 114, 121, 112, 116, 111, 110, 105, 116, 101, 12, 104, 105, 103, 104, 115, 112, 101, 101, 100, 119, 101, 98, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 4;
			return 128; }
		else {
			strcpy(out,"204.181.12.215");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 9, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 204, 181, 12, 215, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 13, 3, 119, 119, 119, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 11, 9, 108, 111, 99, 97, 108, 104, 111, 115, 116, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 29, 10, 107, 114, 121, 112, 116, 111, 110, 105, 116, 101, 12, 104, 105, 103, 104, 115, 112, 101, 101, 100, 119, 101, 98, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 4;
			return 126; } }

	if (	!strcmp(question, "78.156.0.65.in-addr.arpa") ||
		!strcmp(question, "65.0.156.78") ||
		!strcmp(question, "notup.all.net") ) {
		if (qtype == 1) {
			strcpy(out,"");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 78, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 110, 111, 116, 117, 112, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 1;
			return 43; }
		else if (qtype == 15) {
			strcpy(out,"");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 17, 0, 0, 5, 110, 111, 116, 117, 112, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 78);
			ancount = 1;
			arcount = 1;
			return 45; }
		else {
			strcpy(out,"65.0.156.78");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 15, 5, 110, 111, 116, 117, 112, 3, 97, 108, 108, 3, 110, 101, 116, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 78);
			ancount = 1;
			arcount = 1;
			return 43; } }

	if (	!strcmp(question, "60.93.239.63.in-addr.arpa") ||
		!strcmp(question, "63.239.93.60") ||
		!strcmp(question, "east.unhca.com") ||
		!strcmp(question, "east.all.net") ) {
		if (qtype == 1) {
			strcpy(out,"east.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 63, 239, 93, 60, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 16, 4, 101, 97, 115, 116, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 101, 97, 115, 116, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 2;
			return 70; }
		else if (qtype == 15) {
			strcpy(out,"east.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 18, 0, 0, 4, 101, 97, 115, 116, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 63, 239, 93, 60, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 101, 97, 115, 116, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 2;
			return 72; }
		else {
			strcpy(out,"63.239.93.60");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 16, 4, 101, 97, 115, 116, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 63, 239, 93, 60, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 101, 97, 115, 116, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 2;
			return 70; } }

	if (	!strcmp(question, "61.93.239.63.in-addr.arpa") ||
		!strcmp(question, "63.239.93.61") ||
		!strcmp(question, "west.unhca.com") ||
		!strcmp(question, "west.all.net") ) {
		if (qtype == 1) {
			strcpy(out,"west.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 63, 239, 93, 61, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 16, 4, 119, 101, 115, 116, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 119, 101, 115, 116, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 2;
			return 70; }
		else if (qtype == 15) {
			strcpy(out,"west.all.net");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 15, 0, 1, 0, 0, 14, 16, 0, 18, 0, 0, 4, 119, 101, 115, 116, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 63, 239, 93, 61, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 119, 101, 115, 116, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 2;
			return 72; }
		else {
			strcpy(out,"63.239.93.61");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 16, 4, 119, 101, 115, 116, 5, 117, 110, 104, 99, 97, 3, 99, 111, 109, 0, 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 63, 239, 93, 61, 192, 12, 0, 12, 0, 1, 0, 0, 14, 16, 0, 14, 4, 119, 101, 115, 116, 3, 97, 108, 108, 3, 110, 101, 116, 0);
			ancount = 1;
			arcount = 2;
			return 70; } }


/* Default Domain Section */
	 if (strlen(question) > strlen(".all.net"))
		if(strncmp(question + (strlen(question) - strlen(".all.net")),
				".all.net", strlen(".all.net")) == 0) {
			strcpy(out,"204.181.12.215");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 204, 181, 12, 215);
			ancount = 1;
			arcount = 0;
			return 16; }

/* Default Domain Section */
	 if (strlen(question) > strlen(".totful.com"))
		if(strncmp(question + (strlen(question) - strlen(".totful.com")),
				".totful.com", strlen(".totful.com")) == 0) {
			strcpy(out,"65.0.156.77");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 65, 0, 156, 77);
			ancount = 1;
			arcount = 0;
			return 16; }

/* Default Domain Section */
	 if (strlen(question) > strlen(".unhca.com"))
		if(strncmp(question + (strlen(question) - strlen(".unhca.com")),
				".unhca.com", strlen(".unhca.com")) == 0) {
			strcpy(out,"66.60.156.146");
			sprintf(answer, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 192, 12, 0, 1, 0, 1, 0, 0, 14, 16, 0, 4, 66, 60, 156, 146);
			ancount = 1;
			arcount = 0;
			return 16; }

	return 0;
}
#endif
