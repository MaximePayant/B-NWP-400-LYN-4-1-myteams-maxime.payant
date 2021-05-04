##
## EPITECH PROJECT, 2019
## Just a Makefile
## File description:
## Makefile
##

## VARIABLES
## --------------------------------------------->
EXEC :=	myteams_server
FLAG := -Wall -Wextra -pedantic -g3 -Ofast
CC :=	gcc
EXT :=	c
## --------------------------------------------->

## SOURCES VARIABLES
## --------------------------------------------->
SRC_FOLDER :=	src/		\
				src/client
IGNORE_SRC :=	.
SRC :=			$(filter-out $(IGNORE_SRC), $(sort $(shell find $(SRC_FOLDER) -ignore_readdir_race -maxdepth 1 -name '*.$(EXT)')))
## --------------------------------------------->

## INCLUDE VARIABLES
## --------------------------------------------->
INC_FOLDER =	./inc
IGNORE_INC := .
INC := $(filter-out $(IGNORE_INC), $(addprefix -I, $(INC_FOLDER)))
## --------------------------------------------->

## LIBRARY VARIABLES
## --------------------------------------------->
LFOLDER :=
LNAME :=
LIB :=		$(addprefix $(LFOLDER), $(LNAME))

LIB_FOLDER :=	$(addprefix -L, $(LFOLDER))
LIB_NAME :=		$(addprefix -l, $(LNAME))
LIB_EXT :=
## --------------------------------------------->

## OBJECT VARIABLES
## --------------------------------------------->
OBJ_PATH :=		obj/
OBJ_FOLDER :=	$(addprefix $(OBJ_PATH), $(SRC_FOLDER))
OBJ :=			$(addprefix $(OBJ_PATH), $(SRC:.$(EXT)=.o))
## --------------------------------------------->

## UNIT TEST VARIABLES
## --------------------------------------------->
TFOLDER :=
## --------------------------------------------->

## DON'T TOUCH
## --------------------------------------------->
SYSFILES :=			.minfo .minfo/process .minfo/builded .minfo/fails .minfo/errors
N = 				$(shell ls $(SRC_FOLDER) -I $(notdir $(IGNORE_SRC)) 2> .minfo/tmp | grep -e "\.$(EXT)" -c)
SHELL := 			/bin/bash
MAKEFLAGS += 		--no-print-directory --silent --silence
REDIRECT := 		2>> .minfo/errors_list
MAX_FILENAME_LEN =	$(lastword $(sort $(foreach var, $(SRC), $(shell echo -n $(var) | wc -m))))
## --------------------------------------------->

## COLOR AND SPEACH
## --------------------------------------------->
WHITE =		"\e[0;1m"
GREEN =		"\e[92;1m"
RED =		"\e[91;1m"
GRAY =		"\e[90;1m"
MAGENTA =	"\e[95;1m"
YELLOW =	"\e[93;1m"
BYELLOW =	"\e[103m"
CYAN =		"\e[36;1m"
BCYAN =		"\e[46m"

COLOR_RESET = 	echo -ne "\e[0;49m"
SLINE = 		"\n ╔══════════════════════════════\e[0;49m"
COMPILE_SRC =			echo -e "\e[0;49m" ; echo -ne $(BCYAN)   $(GRAY) "     Compiling sources ...     " ; echo -e "\e[0;49m"$(CYAN)$(SLINE)
COMPILE_OBJ =			echo -e "\e[0;49m" ; echo -ne $(BYELLOW) $(GRAY) "     Building objects ...      " ; echo -e "\e[0;49m"$(YELLOW)$(SLINE)
COMPILE_SRC_SUCCESS = 	echo -e $(MAGENTA)"\nIt seems like you finally succeed to code decently";
COMPILE_SRC_FAIL =		echo -e $(MAGENTA)"\n(Renomme le nom du binaire pour voir ?) Aannd you failed, try this out : http://cforbeginners.com/";
COMPILE_OBJ_SUCCESS =	echo -e $(CYAN)" ╚═> " $(GREEN) "Everything was Compiled";
COMPILE_OBJ_FAILED =	echo -e $(CYAN)" ╚═> " $(RED) "Coudn't Compile";
OBJ_BUILT =				(echo -ne $(CYAN) ╠[$(WHITE)$(shell cat .minfo/process) $(CYAN)/ $(WHITE)$(N)$(CYAN)] $(WHITE)$< $(CYAN) ; for i in {1..$(shell echo $(MAX_FILENAME_LEN) - `expr length $<` + 4 | bc)}; do echo -n '.'; done ; echo -e $(GREEN) Built ; $(MAKE) increment_builded)
OBJ_FAILED =			(echo -ne $(CYAN) ╠[$(WHITE)$(shell cat .minfo/process) $(CYAN)/ $(WHITE)$(N)$(CYAN)] $(WHITE)$< $(RED) ; for i in {1..$(shell echo $(MAX_FILENAME_LEN) - `expr length $<` + 4 | bc)}; do echo -n '.'; done ; echo -e $(RED) Failed  ; $(MAKE) increment_errors)
SRC_BUILT =				(echo -e $(YELLOW)" ╚═> " $(GREEN) "Everything was Built")
SRC_FAILED =			(echo -e $(YELLOW)" ╚═> " $(RED) "Coudn't Build" ; $(MAKE) increment_fails)
## --------------------------------------------->

## RULES
## --------------------------------------------->
.PHONY: all introduce compile_obj re clean fclean

all: introduce $(EXEC)
	if [ $(shell cat .minfo/builded) == $(N) ] \
	|| [ $(shell cat .minfo/errors) == 0 ] \
	&& [ $(shell cat .minfo/fails) == 0 ]; \
		then $(COMPILE_SRC_SUCCESS) \
		else $(COMPILE_SRC_FAIL) \
	fi
	rm -f .minfo/builded
	rm -f .minfo/errors
	rm -f .minfo/fails
	rm -f .minfo/process
	rm -f .minfo/tmp
	$(COLOR_RESET)

introduce: $(SYSFILES) $(OBJ_FOLDER)
	$(COMPILE_SRC)

$(EXEC): compile_obj
	$(COLOR_RESET)
	$(COMPILE_OBJ)
	if [ $(shell cat .minfo/errors) == 0 ]; \
		then \
			($(COLOR_RESET) ; \
			$(CC) -o $@ $(OBJ) $(LIB_FOLDER) $(LIB_NAME) $(LIB_EXT) $(INC) $(FLAG) \
				&& $(SRC_BUILT) || $(SRC_FAILED)); \
		else \
			echo -e $(YELLOW)" ╚═> " $(RED) "Coudn't Build"; \
	fi
	$(COLOR_RESET)

compile_obj: $(OBJ)
	$(COLOR_RESET)
	if [ $(shell cat .minfo/errors) == 0 ]; \
		then $(COMPILE_OBJ_SUCCESS) \
		else $(COMPILE_OBJ_FAILED) \
	fi
	$(COLOR_RESET)
	echo -e $(MAGENTA)"\nWarning list :"
	$(COLOR_RESET)
	cat .minfo/errors_list
	$(COLOR_RESET)

$(OBJ): $(OBJ_PATH)%.o: %.$(EXT)
	$(COLOR_RESET)
	$(CC) -o $@ -c $< $(INC) $(FLAG) $(REDIRECT) \
		&& $(OBJ_BUILT) || $(OBJ_FAILED)
	$(MAKE) increment_process
	$(COLOR_RESET)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(EXEC)
	rm -rf .minfo

re: fclean all
## --------------------------------------------->

# LIBRARY RULES
#------------------------------------------>
.PHONY: lib $(LFOLDER)

lib: $(LFOLDER)

$(LFOLDER):
	make -C $@ $(LIB_PROG)
#------------------------------------------>

# UNIT TEST RULES
#------------------------------------------>
.PHONY: lib $(TFOLDER)

test: introduce_test $(TFOLDER)

introduce_test:
	mkdir -p tests/bin/

$(TFOLDER):
	gcc -o $(lastword $(subst /, $(empty), $@)) $@*.c
	mv $(lastword $(subst /, $(empty), $@)) tests/bin/

test_clean:
	rm -rf tests/bin/
#------------------------------------------>

## SYSTEM RULES
## --------------------------------------------->
$(SYSFILES):
	mkdir -p .minfo
	echo 1 > .minfo/process
	echo 0 > .minfo/builded
	echo 0 > .minfo/errors
	echo 0 > .minfo/fails
	touch .minfo/errors_list

$(OBJ_FOLDER):
	mkdir -p $@

increment_builded: $(SYSFILES)
	$(shell echo $$((`cat ".minfo/builded"` + 1)) > .minfo/builded)

increment_fails: $(SYSFILES)
	$(shell echo $$((`cat ".minfo/fails"` + 1)) > .minfo/fails)

increment_errors: $(SYSFILES)
	$(shell echo $$((`cat ".minfo/errors"` + 1)) > .minfo/errors)

increment_process: $(SYSFILES)
	$(shell echo $$((`cat ".minfo/process"` + 1)) > .minfo/process)
## --------------------------------------------->