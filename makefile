all: pizzastudy votecountersem

pizzastudy: pizzastudy.c
	gcc -pthread -o pizzastudy pizzastudy.c

votecountersem: votecountersem.c
	gcc -pthread -o votecountersem votecountersem.c
