cmake_minimum_required(VERSION 3.0)
project(TEST_GF
  VERSION 0.1.0
)
find_package(gf REQUIRED)
#find_package(gfnet0 REQUIRED)



add_executable(client
		Client/ClientModel/CBoard.cc
		Client/client.cc
		Client/ClientModel/CBoard.cc
		Client/ClientModel/CCase.cc
		Client/ClientModel/CCase.h
		Client/ClientModel/CPiece.cc
		Client/ClientModel/CPiece.h
		model/Piece.cc
		model/Case.cc
		model/Pion.cc
		model/Dame.cc
		model/Plateau.cc
		Client/clientTools.cc Client/clientTools.h
		Client/ClientNetwork.cc Client/ClientNetwork.h)

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
		model/Piece.cc
		model/Pion.cc
		model/Dame.cc
		model/Case.cc
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
	#gf0
	#gfnet0
	#gfcore0
		gf::graphics
		gf::net

)

target_link_libraries(clientIA
		gf::net
		)

target_link_libraries(clientIA_V1

		gf::net
)



target_link_libraries(serveur
	#gf0
	#gfnet0
	#gfcore0
		gf::net
		gf::net
)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)


