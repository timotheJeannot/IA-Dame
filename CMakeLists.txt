cmake_minimum_required(VERSION 3.0)
project(TEST_GF
  VERSION 0.1.0
)
find_package(gf REQUIRED)
#find_package(gfnet0 REQUIRED)
#add_executable(test_gf
#		model/Graph.cc
#		model/Case.cc
#		model/Piece.cc
#		model/Pion.cc
#		model/Dame.cc
#		model/Plateau.cc
  # and the rest of your sources
#)



add_executable(client
		model/Graph.cc
		model/Case.cc
		model/Piece.cc
		model/Pion.cc
		model/Dame.cc
		model/Plateau.cc
		IA/heuristique.cc
		IA/MinMax.cc
		Client/client.cc
		Client/clientTools.cc Client/clientTools.h model/Graph.cc)

add_executable(clientIA
		model/Case.cc
		model/Piece.cc
		model/Pion.cc
		model/Dame.cc
		model/Plateau.cc
		IA/heuristique.cc
		IA/MinMax.cc
		Client/clientIA.cc
		Client/clientTools.cc Client/clientTools.h)
		
add_executable(clientIA_V1
		model/Case.cc
		model/Piece.cc
		model/Pion.cc
		model/Dame.cc
		model/Plateau.cc
		IA/heuristique.cc
		IA/MinMax.cc
		Client/clientIA_V1.cc
		Client/clientTools.cc Client/clientTools.h)
		



add_executable(serveur
		model/Graph.cc
		model/Case.cc
		model/Piece.cc
		model/Pion.cc
		model/Dame.cc
		model/Plateau.cc
		Serveur/serveur.cc
		Serveur/serverTools.h Serveur/serverTools.cc)


#target_link_libraries(test_gf
  #gf::gf0
#  gf0
#  gfcore0
  #gfnet::gfnet0
  #gfnet0

#)

target_link_libraries(client
	gf0
	gfnet0
	gfcore0
)

target_link_libraries(clientIA
	gf0
	gfnet0
	gfcore0
)

target_link_libraries(clientIA_V1
	gf0
	gfnet0
	gfcore0
)



target_link_libraries(serveur
	gf0
	gfnet0
	gfcore0
)




