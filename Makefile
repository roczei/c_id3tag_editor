PROGRAM_NEVE = id3tag
RM = /bin/rm
OBJ = id3tag.o id3_fv1.o id3_fv2.o id3_fv3.o
C = id3tag.c id3_fv1.c id3_fv2.c id3_fv3.c

COMPILER = gcc

$(PROGRAM_NEVE): $(OBJ)
	$(COMPILER) -o $(PROGRAM_NEVE) $(OBJ)
	@strip $(PROGRAM_NEVE)
	#@$(RM) $(OBJ)
	echo $? $@

$(OBJ): id3tag.h

id3tag.o: id3tag.c
	$(COMPILER) -c id3tag.c

id3_fv1.o: id3_fv1.c
	$(COMPILER) -c id3_fv1.c
id3_fv2.o: id3_fv2.c
	$(COMPILER) -c id3_fv2.c
id3_fv3.o: id3_fv3.c
	$(COMPILER) -c id3_fv3.c

clean:
	@$(RM) $(OBJ)
