CFLAGS=-Wall -Wextra

sdns: sdns.c table.h

opt: sdns.c table.h

table.h:	hosts defaults convert.pl
	./convert.pl < hosts > $@

.PHONE: clean clean_sdns clean_table
clean: clean_sdns clean_table

clean_sdns: sdns  
	rm $^
clean_table: table.h
	rm $^
