all:
	gcc udp_server.c -o server
	gcc udp_client.c -o client

clean:
	rm server client