CODEDIR = ./Source
INCDIR  = ./Source
EXECDIR = .

GCC = $(CROSS_COMPILE)gcc

CFLAG = -I $(INCDIR) -c

OBJ = $(CODEDIR)/elfSys.o			\
		$(CODEDIR)/libSys.o			\
		$(CODEDIR)/file.o				\
		$(CODEDIR)/viewLib.o			\
		$(CODEDIR)/main.o

TARGET = $(EXECDIR)/libSys

$(TARGET) :	$(OBJ)
			$(GCC) $^ -o $@

$(CODEDIR)/elfSys.o :	$(CODEDIR)/elfSys.c			\
								$(CODEDIR)/elfSys.h			\
								$(CODEDIR)/type.h				\
								$(CODEDIR)/viewLib.h
						$(GCC) $(CFLAG) -o $@ $<

$(CODEDIR)/libSys.o :	$(CODEDIR)/libSys.c			\
								$(CODEDIR)/libSys.h			\
								$(CODEDIR)/type.h				\
								$(CODEDIR)/viewLib.h			\
								$(CODEDIR)/elfSys.h
						$(GCC) $(CFLAG) -o $@ $<

$(CODEDIR)/file.o :		$(CODEDIR)/file.c				\
								$(CODEDIR)/file.h			\
								$(CODEDIR)/type.h
						$(GCC) $(CFLAG) -o $@ $<

$(CODEDIR)/viewLib.o :	$(CODEDIR)/viewLib.c			\
								$(CODEDIR)/viewLib.h			\
								$(CODEDIR)/type.h
						$(GCC) $(CFLAG) -o $@ $<

$(CODEDIR)/main.o :		$(CODEDIR)/main.c			\
								$(CODEDIR)/type.h			\
								$(CODEDIR)/libSys.h		\
								$(CODEDIR)/file.h
						$(GCC) $(CFLAG) -o $@ $<


all:	clean $(TARGET)

clean:
	rm -rf $(OBJ) $(TARGET)

codeClean:
	rm -rf $(CODEDIR)/*~ $(EXECDIR)/*~
					
