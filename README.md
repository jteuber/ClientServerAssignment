# ClientServerAssignment

## My implementation

This implementation of the assignment below uses qmake as build-framework and the standalone ASIO library via my Linux's package manager.


## Assignment from Fizyr:

Create a command-line server and client in C++ using asynchronous communication via ASIO (either Boost ASIO or standalone ASIO). The client should send a "Hello World" text to the server. The server should print this message and send a status result back to the client. The client must then parse and print the status response.

Note that ASIO can also be used to write synchronous applications. However, we are looking for an asynchronous implementation using an event loop and callbacks.

We will be looking at a few points:
- Consistency in code style and naming.
- Code clarity (function and variable names, use of comments).
- Code structure.
