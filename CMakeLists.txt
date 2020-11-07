cmake_minimum_required(VERSION 3.0)
project(TEST_GF
  VERSION 0.1.0
)
find_package(gf REQUIRED)
#find_package(gfnet0 REQUIRED)
add_executable(test_gf 
  test_gf.cc
  # and the rest of your sources
)



add_executable(client
	model/Case.cc
	model/Piece.cc
	model/Pion.cc
	model/Dame.cc
	model/Plateau.cc
	Client/client.cc
		Client/clientTools.cc Client/clientTools.h)

add_executable(serveur
	model/Case.cc
	model/Piece.cc
	model/Pion.cc
	model/Dame.cc
	model/Plateau.cc
	Serveur/serveur.cc
		Serveur/serverTools.h Serveur/serverTools.cc)


target_link_libraries(test_gf
  #gf::gf0
  gf0
  gfcore0
  #gfnet::gfnet0
  #gfnet0
)

target_link_libraries(client
	gf0
	gfnet0
	gfcore0
)

target_link_libraries(serveur
	gf0
	gfnet0
	gfcore0
)




