#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

int main( int argc, char *argv[] ) {
   int sockfd, sockfd2, portno, clilen;
   char buffer[256];
   char buffer1[4];
   char data1[10];
   char data2[10];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
 
   portno = 7001;
   
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
   sockfd2 = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
   if (sockfd2 < 0) {
      perror("ERROR on accept");
      exit(1);
   }
   printf("Success");
   /* If connection is established then start communicating */
   while(1) {
   //bzero(buffer,256);
   bzero(buffer1,4);
   bzero(data1,10);
   bzero(data2,10);
   n = read(sockfd2,buffer1,4);
   read(sockfd2,data1,sizeof(data1));
   read(sockfd2,data2,sizeof(data2));
   printf("datas: %s %s",data1,data2);
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   //char data1[10],data2[10],data3[10];
   //bzero(data1,10);
   //bzero(data2,10);
   //bzero(data3,10);
   float f1;
   float f2;
   f1 = strtof(data1, NULL);
   f2 = strtof(data2, NULL);
   float res;
   char result[20];
   /*
   int i;
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
	break;

   }
   f1 = strtof(data2, NULL);
   j++;
   i=0;
   for(; buffer[j] != '\0'; j++) 
   {
	if(buffer[j] != '+') {
		data3[i] = buffer[j];
		i++;
	}
	break;

   }
   f2 = strtof(data3, NULL);*/
   if(!strncmp(buffer1,"add",3))
	   res = f1+f2;
   if(!strncmp(buffer1,"sub",3))
	   res = f1-f2;
   if(!strncmp(buffer1,"mul",3))
	   res = f1*f2;
   if(!strncmp(buffer1,"div",3))
	   res = f1/f2;
   printf("datas: %f %f %f",data1,data2,res);
   
   sprintf(result, "%2.2f", res);
   bzero(buffer,256);
   strcpy(buffer,result);
   write(sockfd2,buffer,sizeof(data1));

   
   //printf("Here is the message: %s\n",buffer);
   
   /* Write a response to the client */
/*   n = write(newsockfd,"I got your message",18);
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }*/
   }
   return 0;
}
