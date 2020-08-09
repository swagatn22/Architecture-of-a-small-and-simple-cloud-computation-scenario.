#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

int main( int argc, char *argv[] ) {
   int sockfd, sockfd1, portno, clilen;
   char buffer[3];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   float a = 8.0;
   float b = 15.0;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
 
   portno = 6001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
      
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   /* Accept actual connection from the client */
   sockfd1 = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
   if (sockfd1 < 0) {
      perror("ERROR on accept");
      exit(1);
   }
   printf("Success");
   /* If connection is established then start communicating */
   while(1) {
   bzero(buffer,3);
   n = read(sockfd1,buffer,3 );
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   char data1[10]={0};
   char data2[10]={0};
   data1[0]=buffer[0];
   data2[0]=buffer[2];
   /*int i;
   for(i=0; buffer[i] != '\0'; i++)
   {	
	if(buffer[i] != '+') {
		data1[i] = buffer[i];
	}
	break;
   }
   int j = i+1;
   i = 0;
   for(; buffer[j] != '\0'; j++) 
   {
	if(buffer[j] != '+') {
		data2[i] = buffer[j];
		i++;
	}

   }*/
   if(data1[0]=='a')
	   sprintf(data1, "%2.2f", a); 
   if(data1[0]=='b')
	   sprintf(data1, "%2.2f", b); 
   if(data2[0]=='a')
	   sprintf(data2, "%2.2f", a); 
   if(data2[0]=='b')
	   sprintf(data2, "%2.2f", b); 
   //strcat(data1,"+");
   //strcat(data1,data2);
   printf("datas: %f %f %f",data1,data2);
   printf("datas: %s %s",data1,data2);
   
   write(sockfd1,data1,sizeof(data1));
   write(sockfd1,data2,sizeof(data2));
   
   //printf("datas: %s %s",data1,data2);
  // printf("Here is the message: %s\n",buffer);
   
   /* Write a response to the client */
   /*n = write(newsockfd,"I got your message",18);
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }*/
   } 
   return 0;
}
