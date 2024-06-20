# Servitor Journal
In this project I will be a lot about networking and how socket programming in C works. As such, I have decided to document my journey in this project with things I learnt and implemented.

### June 15, 2024
The start of the project. So far I have finished close to 3 chapters from "Beej's guide to Networking". I have learnt about different sockets, what they do, which protocols they use, what TCP and UDP are different on and IP addresses.

### June 17, 2024
Finished reading Beej's guide. It was great for understanding what the functions and structs in the C socket libraries are and do
but I still have to figure things out. So far, I have managed to create and bind a socket to a port given through standard input.

### June 19, 2024
I have now managed to make a server that creates a socket on port 8080, listens on it then returns the string that is sent to it. I have so far tested it using telnet. My next step would be to figure out how to receive and parse HTTP requests and return the proper response.
