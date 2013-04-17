#!/usr/bin/perl

# ----------- Default Domain IP Information -----------
# $defaultdomain{".your.domain"} = "1.2.3.4";  <-- Example: Do not use!
require "defaults";
# ----------- End Default Domain IP Information -------                              
$TYPE_IP = 1;
$TYPE_NAME = 12;
$TYPE_MX = 15;
$CLASS_INET = 1;
$COMPRESS = 0xC00C;
$TTL=3600;
$MX_PREF = pack("n",0);
$name_rr = pack("n n n N", $COMPRESS, $TYPE_NAME, $CLASS_INET, $TTL);
$ip_rr = pack("n n n N", $COMPRESS, $TYPE_IP, $CLASS_INET, $TTL);
$mx_rr = pack("n n n N", $COMPRESS, $TYPE_MX, $CLASS_INET, $TTL);

print "/* table.h - Hostname/IP table initialization file for sdns.c */\n\n";
print "#ifndef _SDNS_TABLE_H\n#define _SDNS_TABLE_H\n\n";
print "/* translate sets the string 'answer' equal to the answer of the query,\n";
print "   sets ancount equal to the number of answers in the answer string, and\n";
print "   returns the length of the answer string */ \n";
print "int translate(unsigned short int qtype)\n{\n";
print "
#include <stdio.h>
#include <string.h>
 
extern char question[];
extern char out[];
extern char answer[];
extern int ancount,arcount ;
";

for $hostsline (<>) {
	@allnames = ();
	$ancount=2;
	$hostsline =~ y/A-Z/a-z/;
	($ip, $names) = split(/\s+/, $hostsline, 2);
	$ip_rdata = trname($ip,);
	if ((unpack("c", $hostsline) eq "#") || ($ip eq "")) {
		next; }
	else {
		($a, $b, $c, $d) = split(/\./, $ip, 4);
		($car, $cdr) = split(/\s+/, $names, 2);
		if ($car ne "") {
			print "\tif (\t";
			print "!strcmp(question, \"$d.$c.$b.$a.in-addr.arpa\") ||\n";
			print "\t\t!strcmp(question, \"$a.$b.$c.$d\") ||\n\t\t"; }
		while($car ne "") {
			push @allnames,$car;
			print "!strcmp(question, \"$car\") ";
			($car, $cdr) = split(/\s+/, $cdr, 2);
			if ($car ne "") {
				print "||\n\t\t"; }
			else {
				print ") {\n";
				# Generate the answer strings
				$mxname = trmxname($allnames[0]);
				$firstname = trname(shift(@allnames));
				$ip_first_answer = $ip_rr . $ip_rdata . $name_rr .  $firstname;
				$name_first_answer = $name_rr . $firstname . $ip_rr . $ip_rdata;
				$mx_first_answer = $mx_rr . $mxname . $ip_rr . $ip_rdata;
				foreach $hostname (@allnames) {
					$ancount++;
					$firstname = trname($hostname);
					$ip_first_answer .= trrr($hostname) . $firstname;
					$name_first_answer .= trrr($hostname) . $firstname; 
					$mx_first_answer .= trrr($hostname) . $firstname; }
				print "\t\tif (qtype == $TYPE_IP) {\n";
				print "\t\t\tstrcpy(out,\"$allnames[0]\");\n";
				print sprintfstr($ip_first_answer);
				print "\n\t\telse if (qtype == $TYPE_MX) {\n";
				print "\t\t\tstrcpy(out,\"$allnames[0]\");\n";
				print sprintfstr($mx_first_answer); 
				print "\n\t\telse {\n";
				print "\t\t\tstrcpy(out,\"$ip\");\n";
				print sprintfstr($name_first_answer) . " }\n"; } } }
	print "\n"; }

foreach $domain (sort keys %defaultdomain) {
	$ip = $defaultdomain{$domain};
	$defdomain_answer = $ip_rr . trname($ip);
	print "\n/* Default Domain Section */\n";
	print "\t if (strlen(question) > strlen(\"$domain\"))\n";
	print "\t\tif(strncmp(question + (strlen(question) - strlen(\"$domain\")),\n";
	print "\t\t\t\t\"$domain\", strlen(\"$domain\")) == 0) {\n";
	print "\t\t\tstrcpy(out,\"$ip\");\n";
	$ancount=1;
	print sprintfstr($defdomain_answer) . "\n"; }

print "\n\treturn 0;\n}\n#endif\n";



sub trname 
{
	my ($domainname) = @_;
	my ($len, $endname, $thing);
	if (($domainname =~ m/(\d+\.\d+\.\d+\.\d+)$/) &&
	   ($domainname =~ m/^(\d+\.\d+\.\d+\.\d+)/)) {
		$len = 4;
		my ($a, $b, $c, $d) = split(/\./, $domainname);
		$endname = pack("n C C C C", $len, $a, $b, $c, $d); }
	else {
		$len = length($domainname); 
		$endname = pack("n", ($len + 2));
		my @splitname = split(/\./,$domainname);
		foreach $thing (@splitname) {
			$len = length($thing);
			$endname .= pack("c", $len) . pack("C$len", unpack("C$len", $thing)); }
		$endname .= pack("c", 0); }
	return $endname;
} 

sub trmxname
{
	my ($domainname) = @_;
	my ($len, $endname, $thing);
	$len = length($domainname) + 4;
	$endname = pack("n n", $len, 0);
	my @splitname = split(/\./,$domainname);
	foreach $thing (@splitname) {
		$len = length($thing);
		$endname .= pack("c", $len) . $thing; }
	$endname .= pack("c", 0);
	return $endname
}

sub trrr
{
	my ($domainname) = @_;
	if (($domainname =~m/(\d+\.\d+\.\d+\.\d+)$/) &&
		($domainname =~ m/^(\d+\.\d+\.\d+\.\d+)/)) {
		return $ip_rr; }
	return $name_rr; 
}

sub sprintfstr
{
	my ($start_string) = @_;
	my ($len, $endstring, $i, $value);
	$len = length($start_string);
	$endstring = "";
	print "\t\t\tsprintf(answer, \"";
	for ($i = 0; $i < $len; $i++) {
		$endstring .= "\%c"; }
	$endstring .= "\"";
	for ($i = 0; $i < $len; $i++) {
		$value = sprintf("%d", unpack("C", substr($start_string, $i, 1)));
		$endstring .= ", $value"; }
	$arcount = $ancount - 1; # one answer, rest will go into additional section		
	$endstring .= ");\n\t\t\tancount = 1;\n\t\t\tarcount = $arcount;\n\t\t\treturn " . $len . "; }";
}
