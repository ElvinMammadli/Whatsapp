// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8560

void *connection_handler(void *);

FILE *out,*fp;
char fileSpec[32];

struct bilgi{
  char buffer[1024] ;
  char  hello[60];
  char kime[5];
  char kimden[5];
};
int server_fd, new_socket, valread,b;

int main(int argc, char const *argv[])
{
      struct sockaddr_in address;
      int opt = 1,c;
      int addrlen = sizeof(address);

    // Creating socket file descriptor
      if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
      {
          perror("socket failed");
          exit(EXIT_FAILURE);
      }

    // Forcefully attaching socket to the port 8080
      if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
      {
        perror("setsockopt");
        exit(EXIT_FAILURE);
      }
      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
      if (bind(server_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in))<0)
      {
        perror("bind failed");
        exit(EXIT_FAILURE);
      }
 c = sizeof(struct sockaddr_in);
      if (listen(server_fd, 3) < 0)
      {
        perror("listen");
        exit(EXIT_FAILURE);
      }
      pthread_t  thread_id;
      while( (new_socket= accept(server_fd, (struct sockaddr *)&address, &c) ))
      {
         puts("Connection accepted");

          if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &new_socket) < 0)
          {
             perror("could not create thread");
             return 1;
          }
      }
      return 0;
}
void *connection_handler(void *socket_desc)
{

  struct bilgi insan,insan1;
  //  int sock = *(int*)socket_desc;

    recv(new_socket,&insan.buffer,sizeof(insan.buffer),0);
    recv(new_socket,&insan.kime,sizeof(insan.kime),0);
    recv(new_socket,&insan.kimden,sizeof(insan.kimden),0);
    //printf("Kimden\n" );
    printf("%s\t",insan.kime );
    printf("%s\t",insan.buffer );
    printf("%s\t",insan.kimden );

    snprintf( fileSpec, sizeof( fileSpec ), "txt/%sgelen.txt", insan.kime );
    out = fopen( fileSpec, "a+" );
    fwrite(&insan,sizeof(struct bilgi),1,out);
    fclose(out);

    out = fopen( fileSpec, "r+" );
    printf("%s\n",fileSpec );
    printf("%s\n %s\n %s\n ",insan1.kimden,insan1.kime, insan1.buffer );
    fread(&insan1,sizeof(struct bilgi),1,out);
    fclose(out);

    printf("4n4n\n" );

    snprintf( fileSpec, sizeof( fileSpec ), "txt/%sgiden.txt", insan.kimden );
    fp  = fopen( fileSpec, "a+" );
    fwrite(&insan,sizeof(struct bilgi),1,out);
    fclose(fp);

    //printf("Write your message\n");
  //  scanf("%[^\n]%*c",hello);
    //int a=send(new_socket , hello , strlen(hello) , 0 );
    return 0;
}
