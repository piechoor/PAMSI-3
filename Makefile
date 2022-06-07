APP=tiktactoe
__start__: obj ./${APP}
	rm -f core.* core; ./${APP}

obj:
	mkdir obj

./${APP}: obj/main.o obj/game.o
	g++ -o ./${APP} obj/main.o obj/game.o

obj/main.o: src/main.cpp
	g++ -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/game.o: src/game.cpp
	g++ -Iinc -W -Wall -pedantic -c -o obj/game.o src/game.cpp

clean:
	rm -f obj/* ./${APP} core.* core
