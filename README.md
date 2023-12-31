**This project implements a simple Client-Server Model using sockets**
* When the client reads a transaction from an input file, it passes the transaction to the server by writing the transaction to the socket.
* When the server receives a transaction, it processes the transaction and sends the result back to the client using the socket.
* Multiple clients can connect to a server at the same time, though the transactions will be processed in the order they arrive by a single process.
