CC		=	gcc
NAME	=	backup
SRC		=	backup.c
OBJ		=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror

.PHONY: all clean install

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:	$(NAME) cron
	mv $(NAME) ..

cron:
	echo "0 */3 * * * cd .. && ./$(NAME)" > cronjob.tmp
	crontab cronjob.tmp
	$(RM) cronjob.tmp

.DEFAULT_GOAL := all

all:	$(NAME) install

clean:
	$(RM) -f $(OBJ)
	$(RM) -f ../$(NAME)
	sh cron_clean.sh