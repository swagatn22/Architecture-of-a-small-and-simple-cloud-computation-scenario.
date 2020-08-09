#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

int main( int argc, char *argv[] ) {
   int sockfd, sockfd1, sockfd2, newsockfd, portno, portno1, portno2, clilen;
   char buffer[256];
   char buffer1[4];
   struct sockaddr_in serv_addr, data_addr, comp_addr, cli_addr;
   int  n;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
   sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0 ||sockfd1 < 0||sockfd2 < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   bzero((char *) &data_addr, sizeof(data_addr));
   bzero((char *) &comp_addr, sizeof(comp_addr));
 
   portno = 5001;
   portno1 = 6001;
   portno2 = 7001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   data_addr.sin_family = AF_INET;
   data_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   data_addr.sin_port = htons(portno1);
   
   comp_addr.sin_family = AF_INET;
   comp_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   comp_addr.sin_port = htons(portno2);

     /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding main server");
      exit(1);
   }
      
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   /* Accept actual connection from the client */
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
   if (newsockfd < 0) {
      perror("ERROR on accept");
      exit(1);
   }
   
   if (connect(sockfd1, (struct sockaddr*)&data_addr, sizeof(data_addr)) < 0) {
	   perror("Error connecting data server");
   }
printf("Success_data");
   if (connect(sockfd2, (struct sockaddr*)&comp_addr, sizeof(comp_addr)) < 0) {
	   perror("Error connecting comp server");
   }
printf("Success_comp");
char data1[10];
   char data2[10];
   /* If connection is established then start communicating */
   while(1) {
   //bzero(buffer,256);
   bzero(buffer1,4);
   //write(newsockfd,"type of computation supported(add,sub,mul,div)",256);
   n = read(newsockfd,buffer1,4);
   //strncpy(buffer1, buffer,3);
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   printf("%d",strncmp(buffer1,"add",3));

   if ((!strncmp(buffer1,"add",3)) || (!strncmp(buffer1,"sub",3)) || (!strncmp(buffer1,"mul",3)) || (!strncmp(buffer1,"div",3))) {
	write(sockfd1, "a,b", 3);
	//bzero(buffer,256);
	//read(sockfd1, buffer, 255);
	//char buffer1[256];
	bzero(data1,10);
	bzero(data2,10);
	read(sockfd1,data1,sizeof(data1));
	read(sockfd1,data2,sizeof(data2));
	//strcat(buffer1,"+");
	//strcat(buffer1,buffer);
	buffer1[3] = '\0';
	write(sockfd2, buffer1, 3);
	write(sockfd2, data1, sizeof(data1));
	write(sockfd2, data2, sizeof(data2));
	bzero(buffer,256);
	read(sockfd2, buffer, 256);
	write(newsockfd, buffer, sizeof(buffer));
   }
   else if(!strncmp(buffer1,"bye",3)) {
	ferror("BYE");
	exit(1);
   }
   else {
	   perror("Invalid Operation request");
   }
   
   //printf("Here is the message: %s\n",buffer);
   
   /* Write a response to the client */
   //n = write(newsockfd,"I got your message",18);
   
   /*if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }*/
   }
   return 0;
}
