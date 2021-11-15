##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##


all:
	make --no-print-directory -C server/
	make --no-print-directory -C client/

bonus:
	make --no-print-directory bonus -C server/

clean:
	make --no-print-directory clean -C server/
	make --no-print-directory clean -C client/

fclean:
	make --no-print-directory fclean -C server/
	make --no-print-directory fclean -C client/

re:
	make --no-print-directory re -C server/
	make --no-print-directory re -C client/

debug:
	make --no-print-directory debug -C server/
	make --no-print-directory debug -C client/

.PHONY: all clean fclean re debug bonus