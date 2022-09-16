# Client-And-Server-Programs-for-echo

client and server side programs in C of an echo service, i.e., a service which returns back whatever it receives from clients back to them. The clients and server should communicate over the sockets mechanism. The server side should be a multi-threaded application which is capable of servicing multiple clients concurrently in parallel. In addition to the message sent back to its clients, your server should indicate to its client the order of him among all the clients he has served since startup

That is, the first client asked for the service should receive, in
addition to the echo of his message, the information that he is the first client so far, the second
client should receive the information that he is the second client so far, and so on. 
