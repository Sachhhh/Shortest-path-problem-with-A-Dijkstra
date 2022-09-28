# Ce Makefile permet de générer les executables et les fichiers
# binaires necessaire au fonctionnement et aux tests des différents
# algorithmes du projet

# les fichiers executables sont situés dans le repertoire 'bin'
# les fichiers binaires sont situés dans le repertoire 'obj'
# les fichiers sources sont situés dans le fichier 'src'
# les fichiers sources de test sont situés dans le fichier 'tests'

# --------------------------------------------------------
# ------------------- Les repertoires --------------------
# --------------------------------------------------------

#Pour les fichiers d'entete
INCDIR=./include
#Pour les librairies standards
STDINC=/usr/include
#Pour les fichiers executables
BINDIR=./bin
#Pour les fichiers binaires (.o)
OBJDIR=./obj
#Pour les fichiers de tests
TESTS=./tests
#Pour les fichiers sources .c
SRCDIR=./src
#Pout le chemin de la SDL
DIRSDL=/usr/include/SDL2


# --------------------------------------------------------
# ---------------- Le nom du compilateur -----------------
# --------------------------------------------------------

CC=gcc

# --------------------------------------------------------
# --------- Les Flags : options de compilation -----------
# --------------------------------------------------------

#Les options du compilateur : compilation (-c) et debug (-g). On peut ajouter -O3 pour optimiser quand le code est juste
CFLAGS=-c -g -I$(INCDIR) -I$(STDINC) 

#Les options de l'editeur de liens : -lm pour la bibliothèque mathématique. Voir les Makefile de TP pour ajouter la SDL si besoin
LDFLAGS= -lm -I$(DIRSDL) -lSDL2_phelma -lSDL2 -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lm

# --------------------------------------------------------
# ---------------- Compilation Générale ------------------
# --------------------------------------------------------

#Les executables que l'on veut construire: a la fois ceux des tests et ceux des programmes finaux
EXEDIR=$(BINDIR)/test_graph $(BINDIR)/test_heap $(BINDIR)/test_listver $(BINDIR)/test_lifover $(BINDIR)/test_listedge $(BINDIR)/test_edge $(BINDIR)/test_dijkstra $(BINDIR)/test_astar $(BINDIR)/test_temps $(BINDIR)/test_metro $(BINDIR)/pcc

#Les fichiers binaire : ajouter les noms des nouveaux fichiers ici
OBJ=$(OBJDIR)/test_graph.o $(OBJDIR)/graph.o $(OBJDIR)/heap.o $(OBJDIR)/listedge.o $(OBJDIR)/edge.o $(OBJDIR)/vertex.o $(OBJDIR)/test_listver.o $(OBJDIR)/listver.o $(OBJDIR)/lifover.o $(OBJDIR)/test_lifover.o $(OBJDIR)/test_listedge.o $(OBJDIR)/test_edge.o $(OBJDIR)/tabver.o $(OBJDIR)/Dijkstra.o $(OBJDIR)/test_dijkstra.o $(OBJDIR)/Astar.o $(OBJDIR)/test_astar.o $(OBJDIR)/test_temps.o $(OBJDIR)/test_metro.o $(OBJDIR)/metro.o $(OBJDIR)/pcc.o

#Pour construire tous les executables
all: $(EXEDIR)

# --------------------------------------------------------
# ------- Règles de compilation des éxécutables ----------
# --------------------------------------------------------
#Test du module metro
$(BINDIR)/test_metro : $(OBJDIR)/test_metro.o $(OBJDIR)/metro.o $(OBJDIR)/vertex.o $(OBJDIR)/graph.o $(OBJDIR)/heap.o $(OBJDIR)/lifover.o $(OBJDIR)/tabver.o $(OBJDIR)/listedge.o $(OBJDIR)/Astar.o $(OBJDIR)/listver.o $(OBJDIR)/graph.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du module edge
$(BINDIR)/test_edge : $(OBJDIR)/test_edge.o $(OBJDIR)/edge.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du module edge
$(BINDIR)/test_heap : $(OBJDIR)/test_heap.o $(OBJDIR)/heap.o $(OBJDIR)/vertex.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du module listver
$(BINDIR)/test_listver : $(OBJDIR)/test_listver.o $(OBJDIR)/listver.o $(OBJDIR)/vertex.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du module lifover
$(BINDIR)/test_lifover : $(OBJDIR)/test_lifover.o $(OBJDIR)/lifover.o $(OBJDIR)/listver.o $(OBJDIR)/vertex.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du module Graph
$(BINDIR)/test_graph : $(OBJDIR)/test_graph.o $(OBJDIR)/graph.o $(OBJDIR)/listedge.o $(OBJDIR)/vertex.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du module liste_edge
$(BINDIR)/test_listedge : $(OBJDIR)/test_listedge.o $(OBJDIR)/listedge.o $(OBJDIR)/edge.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du module Dijkstra
$(BINDIR)/test_dijkstra : $(OBJDIR)/test_dijkstra.o $(OBJDIR)/vertex.o $(OBJDIR)/graph.o $(OBJDIR)/heap.o $(OBJDIR)/lifover.o $(OBJDIR)/tabver.o $(OBJDIR)/listedge.o $(OBJDIR)/Dijkstra.o $(OBJDIR)/listver.o $(OBJDIR)/metro.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du module Astar
$(BINDIR)/test_astar : $(OBJDIR)/test_astar.o $(OBJDIR)/vertex.o $(OBJDIR)/graph.o $(OBJDIR)/heap.o $(OBJDIR)/lifover.o $(OBJDIR)/tabver.o $(OBJDIR)/listedge.o $(OBJDIR)/Astar.o $(OBJDIR)/listver.o $(OBJDIR)/metro.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du module de calcul des temps d'execution
$(BINDIR)/test_temps : $(OBJDIR)/test_temps.o $(OBJDIR)/Dijkstra.o $(OBJDIR)/Astar.o $(OBJDIR)/vertex.o $(OBJDIR)/graph.o $(OBJDIR)/heap.o $(OBJDIR)/lifover.o $(OBJDIR)/tabver.o $(OBJDIR)/listedge.o $(OBJDIR)/listver.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Test du programme principal
$(BINDIR)/pcc : $(OBJDIR)/pcc.o $(OBJDIR)/Dijkstra.o $(OBJDIR)/Astar.o $(OBJDIR)/metro.o $(OBJDIR)/vertex.o $(OBJDIR)/graph.o $(OBJDIR)/heap.o $(OBJDIR)/lifover.o $(OBJDIR)/tabver.o $(OBJDIR)/listedge.o $(OBJDIR)/listver.o $(OBJDIR)/metro.o
	$(CC) -o $@ $^ $(LDFLAGS)

# --------------------------------------------------------
# ----- Règles de compilation des fichiers binaires ------
# --------------------------------------------------------

# pour construire les fichiers binaires .o
$(OBJDIR)/%.o : $(TESTS)/%.c
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $^ -o $@

# --------------------------------------------------------
# --------------------- Nettoyage ------------------------
# --------------------------------------------------------

clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/* $(EXEDIR) *.dSYM

clear:
	rm -rf $(OBJDIR)/* $(BINDIR)/* $(EXEDIR) *.dSYM
