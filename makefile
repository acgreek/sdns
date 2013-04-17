CFLAGS=-Wall -Wextra
sdns: sdns.c table.h


opt: sdns.c table.h


table.h:	hosts defaults convert.pl
	./convert.pl < hosts > table.h

.PHONE: clean 
clean: sdns
	rm sdns
