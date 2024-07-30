####################################################
###################### MAKE ########################
####################################################

EXECUTAVEL = tsp
PATHEXEC = ./bin
PATHSRC= ./src
PATHTEMP = ./.temp

all:
	mkdir -p $(PATHEXEC)
	mkdir -p $(PATHTEMP)
	make $(EXECUTAVEL)	


#Juntando todos os objetos e gerando o programa
$(EXECUTAVEL): $(PATHTEMP)/Menu.o $(PATHTEMP)/Instancia.o $(PATHTEMP)/Solucao.o $(PATHTEMP)/Avaliador.o $(PATHTEMP)/HeuristicasConstrutivas.o $(PATHTEMP)/BuscasLocais.o $(PATHTEMP)/MultiStart.o $(PATHTEMP)/GRASP.o $(PATHTEMP)/main.o
	$(CPP) $(CCFLAGS) $(PATHTEMP)/Menu.o $(PATHTEMP)/Instancia.o $(PATHTEMP)/Solucao.o $(PATHTEMP)/Avaliador.o $(PATHTEMP)/HeuristicasConstrutivas.o $(PATHTEMP)/BuscasLocais.o $(PATHTEMP)/MultiStart.o $(PATHTEMP)/GRASP.o $(PATHTEMP)/main.o $(CCLNFLAGS) $(LSFLAGS) -o $(PATHEXEC)/$(EXECUTAVEL)


$(PATHTEMP)/main.o: $(PATHSRC)/main.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/main.cpp -o $(PATHTEMP)/main.o

$(PATHTEMP)/Instancia.o: $(PATHSRC)/Instancia.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/Instancia.cpp -o $(PATHTEMP)/Instancia.o

$(PATHTEMP)/Solucao.o: $(PATHSRC)/Solucao.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/Solucao.cpp -o $(PATHTEMP)/Solucao.o

$(PATHTEMP)/Avaliador.o: $(PATHSRC)/Avaliador.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/Avaliador.cpp -o $(PATHTEMP)/Avaliador.o

$(PATHTEMP)/Menu.o: $(PATHSRC)/Menu.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/Menu.cpp -o $(PATHTEMP)/Menu.o

$(PATHTEMP)/HeuristicasConstrutivas.o: $(PATHSRC)/HeuristicasConstrutivas.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/HeuristicasConstrutivas.cpp -o $(PATHTEMP)/HeuristicasConstrutivas.o

$(PATHTEMP)/BuscasLocais.o: $(PATHSRC)/BuscasLocais.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/BuscasLocais.cpp -o $(PATHTEMP)/BuscasLocais.o

$(PATHTEMP)/MultiStart.o: $(PATHSRC)/MultiStart.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/MultiStart.cpp -o $(PATHTEMP)/MultiStart.o

$(PATHTEMP)/GRASP.o: $(PATHSRC)/GRASP.cpp
	$(CPP) $(CCFLAGS) -c $(PATHSRC)/GRASP.cpp -o $(PATHTEMP)/GRASP.o

####################################################
###################### CLEAN #######################
####################################################

clean:
	/bin/rm -rf $(PATHEXEC)
	/bin/rm -rf $(PATHTEMP)

####################################################
##################### COMPILER #####################
####################################################

##### COMPILER CONFIGURATION's
# Compiler
CPP = g++
# Compilation parameters
CCOPT = -O3
## Include libraries identifiers
CCLNFLAGS = -lm
# Header's include path
CCFLAGS = $(CCOPT)