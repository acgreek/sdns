sdns:	sdns.c table.h
	cc -o sdns sdns.c

opt: sdns.c table.h
	cc -O -o sdns sdns.c

table.h:	hosts defaults convert.pl
	./convert.pl < hosts > table.h
