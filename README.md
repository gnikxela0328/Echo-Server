# Echo-Server
--------------------------------------
C Echo server using socket programming
--------------------------------------

<h3>Abstract<br></h3>
This program contains a server and client that can be used to communicate within a host-only 
network. With slight modification, the program can be used over the internet given the proper addressing
and port schema. The default configuration utilizes the host loopback address and port 3000 to facilitate
a tcp connection for call and response.


//Usage
Contained within the /src folder is the source code and two scripts: 

runServer & runClient

The scripts compile each program and supply the proper arguments. Included with the addressing
specifications is a username used for client authentication. The server will serve up to 8 clients 
at a time, each must supply the proper username. 

