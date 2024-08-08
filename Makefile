tictactoe: tictactoe.o game.o human.o agent.o
	gcc -o tictactoe tictactoe.o game.o human.o agent.o

tictactoe.o: tictactoe.c game.h agent.h
	gcc -c tictactoe.c

game.o: game.c game.h
	gcc -c game.c

human.o: human.c game.h human.h
	gcc -c human.c

agent.o: agent.c game.h agent.h
	gcc -c agent.c

# Delete executable and object files from directory
clean:
	rm tictactoe tictactoe.o game.o human.o agent.o