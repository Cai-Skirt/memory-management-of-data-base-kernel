#-------------------------------------------------------------------------
#
# Makefile--
#    Makefile
#
# IDENTIFICATION
#    ./Makefile
#
#-------------------------------------------------------------------------

BufferManager: main.c bufferManager.c lwlock.c tupleAccess.c linkedList.c simulator.c
	clang main.c bufferManager.c lwlock.c tupleAccess.c linkedList.c simulator.c -g -o BufferManager