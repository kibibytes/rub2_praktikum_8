COMMON_OPS = -Wall -std=c99 -pthread

all: server producer consumer

server: sem_server.c
	gcc $(COMMON_OPS) -o sem_server sem_server.c

producer: producer.c
	gcc $(COMMON_OPS) -o producer producer.c

consumer: consumer.c
	gcc $(COMMON_OPS) -o consumer consumer.c

clean:
	rm -f consumer
	rm -f producer
	rm -f sem_server
