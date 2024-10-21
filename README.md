Minitalk is a set of two programs : client & server

The client transfer its message bit by bit to the server which will output it once it is fully recieved.
The server is able to handle consecutives message queries without need to be restarted. It can also recieve multiple message queries from different clients simultaneously;
Server-client synchronization is ensured throughout the entire process. 
More reliability could be implemented through a bit/packet failsafe retrieval feature that would lead the server to ask the client for any uncomplete or defective byte using a timeout on the server side.
