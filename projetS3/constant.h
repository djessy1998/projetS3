//Utile pour l'initialisation du joueur
#define PM_START   0
#define POSX_START 352
#define POSY_START 400

//Utile pour l'atlas avec les images correspondantes
#define NBIMAGES	41

//A MODIFIER EN CORRESPONDANCE AVEC LES BLOCS PLUS BAS
#define JOUEUR_IM 	   0
#define TERREINV_IM	     1
#define CASQUE_IM	     2
#define ARMURE_IM	     3
#define TRONC_IM	     4
#define ABG_IM		     5
#define ABD_IM		     6
#define BASARB_IM	     7
#define TOPARB_IM	     8
#define FONDGROTTE_IM  9
#define TERRESH_IM 	   10
#define HERBE_IM       11
#define HERBE1_IM      12
#define TERRE1_IM      13
#define TERRE2_IM      14
#define TERRE3_IM      15
#define TERREHERBE1_IM 16
#define TERREHERBE2_IM 17
#define TERREHERBE3_IM 18
#define FONDTERRE1_IM  19
#define FONDTERRE2_IM  20
#define FONDTERRE3_IM  21

#define VIEENT_IM	     22
#define INVIM_IM	     23
#define ACTUELINV_IM	 24
#define MIVIE_IM	     25
#define NOVIE_IM	     26
#define CRACK_IM	     27
#define JOUEURD_IM	   28
#define MAP_IM 	       29
#define SLIME_IM	     30
#define BG_IM	         31
#define VIEENTM_IM	   32
#define MIVIEM_IM	     33
#define NOVIEM_IM	     34
#define CLOUD_IM       35
#define CLOUD1_IM      36
#define CLOUD2_IM      37
#define CLOUD3_IM      38
#define ARMUREINV_IM   39
#define CASQUEINV_IM   40

//Utile pour intialiser SDL
//A propos de la fenetre
#define SCREEN_WIDTH   720
#define SCREEN_HEIGHT  560
#define NBBLOCS_FENETREX 47
#define NBBLOCS_FENETREY 37

//A propos du joueur
#define PLAYER_WIDTH   22
#define PLAYER_HEIGHT  54
#define VELOCITE_MAX   15
#define VITESSE        1.
#define VITESSEJ       0.2
#define FULL_VIE       100
#define DISTCHUTEMPV   100
#define NB_BLOCS_AU_DESSUS_JOUEUR 25

//A propos des monstres
#define NBMONSTRE     10
#define VELOCITE_MAX_MONSTRE 10
#define HAUTEUR_MONSTRE 22
#define LARGEUR_MONSTRE 32
#define DROITE 1
#define GAUCHE -1
#define IMMOBILE 0

//A propos du monde
#define TMONDE         1000
#define NB_GROTTES     10
#define DIST_ENTRE_POINTS 2
#define NBARBRES       100

//A propos de la miniMap
#define TMINIMAP 200

//A propos de l'inventaire et du minage
#define RAYONRAM	     40
#define NBITEMS        5
#define MAXITINV       64
#define LIMITEMINA      5
#define VITESSEMINA	1
#define TAILLE_INV  40

//Utile pour l'affichage et les collisions
//Blocs
#define TAILLE_BLOCS	 16
#define VIDE  0
#define TERRE 1
#define CASQUE 2
#define ARMURE 3
#define ARBRE 4
#define ABG 5
#define ABD 6
#define BASARB 7
#define TOPARB 8
#define FONDGROTTE 9
#define TERRESH 10
#define HERBE 11
#define HERBE1 12
#define TERRE1 13
#define TERRE2 14
#define TERRE3 15
#define TERREHERBE1 16
#define TERREHERBE2 17
#define TERREHERBE3 18
#define FONDTERRE1  19
#define FONDTERRE2  20
#define FONDTERRE3  21



//Utile pour les input
//DIFFERENTES TOUCHES AVEC SCAN CODE
//CARACTERES SPECIAUX
#define ECHAP	9
#define ESPER	10
#define EACC	11
#define DOUBLEQUOTE 12
#define QUOTE 13
#define LEFTPAREN	14
#define TIRET 15
#define EACCGRA	16
#define UNDERSCORE	17
#define CCEDILLE	18
#define AACCENT	19

// LETTRES
#define Z	  25
#define Q	  38
#define S 	39
#define D 	40
#define E 	26
#define F 	41

//Utile pour les fonction des fichiers
#define VALEUR_ASCII_0 48
