// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8540

void *connection_handler(void *);

FILE *out,*fp;
char fileSpec[32];
struct bilgi{
  char buffer[1024] ;
  char kime[5];
  char kimden[5];
};
int server_fd, new_socket, valread,b;
char hello[60];
char apple[1024];
int main(int argc, char const *argv[])
{
  struct sockaddr_in address;
  int opt = 1,c=0;
  int addrlen = sizeof(address);

    // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
          perror("socket failed");
          exit(EXIT_FAILURE);
  }

    // Forcefully attaching socket to the port 8080
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
  }
      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_port = htons( PORT );

    // Forcefully attaching sock%set to the port 8080
   if (bind(server_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
   }

   if (listen(server_fd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
   }
  pthread_t  thread_id;
  while( (new_socket= accept(server_fd, (struct sockaddr *)&address, &c) )){
         puts("Connection accepted");

          if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &new_socket) < 0){
             perror("could not create thread");
             return 1;
          }
  }
  return 0;
}



void *connection_handler(void *socket_desc)
{

  struct bilgi insan;
  memset(insan.buffer, 0, sizeof(insan.buffer));
  //  int sock = *(int*)socket_desc;

  recv(new_socket,&apple,sizeof(apple),0);

    int i=0,c=0;
    while(apple[c]!=' '){
        insan.kime[c]=apple[c];
        c++;
    }
    insan.kime[c]='\0';
    c++;
    while (apple[c]!=' ') {
      insan.kimden[i]=apple[c];
      i++;
      c++;
    }
    insan.kimden[i]='\0';
    i=0;
    while (apple[c]!='\0') {
      insan.buffer[i]=apple[c];
      i++;
      c++;
    }
    insan.buffer[i]='\0';
    printf("%s\n",insan.kime );
    printf("%s\n",insan.kimden );
    printf("%s\n",insan.buffer );

    char apple='\0';
    snprintf( fileSpec, sizeof( fileSpec ), "txt/%skonusma.txt", insan.kime );
    out = fopen( fileSpec, "a+" );
    fprintf(out, "+ %s %s\n",insan.kimden,insan.buffer );
    fclose(out);

    snprintf( fileSpec, sizeof( fileSpec ), "txt/%skonusma.txt", insan.kimden );
    fp  = fopen( fileSpec, "a+" );
    fprintf(fp, "- %s %s\n",insan.kime,insan.buffer );
    fclose(fp);

    //printf("Write your message\n");
  //  scanf("%[^\n]%*c",hello);
    //int a=send(new_socket , hello , strlen(hello) , 0 );
    return 0;
}
