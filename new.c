// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8540

#define clear() printf("\033[H\033[J")

char comp_id[5];
char name[30];
int num,d=5,kullanici_sayisi=6,tmp;
char mail1[30];
char kime[5];
char kimden[5];
char list[5];
int d;
struct kullanici{
    char id[5];
    char isim[30];
    int numara;
    char mail[30];
};
struct kullanici yeni;
FILE * fp;
char* extension;//="gelen.txt";
char fileSpec[32];
FILE *out;

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    int a;
    struct sockaddr_in serv_addr;
    char hello[100] ;
    char buffer[1024]={0} ;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr=INADDR_ANY;


    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }
   strcpy(yeni.id, argv[1]);
   printf("%s Kullanicisi icin giris yaptiniz\n",yeni.id);
   fp = fopen ("txt/kullanicilar.txt", "r+");
   fscanf(fp,"%s %s %d %s",comp_id,name,&num,mail1);

   while (!feof(fp)){
     //printf("%s %s %d %s\n",comp_id,name,num,mail1 );
      if (strcmp(comp_id, yeni.id) == 0){
        printf("Kullanici bulunmaktadir");
        tmp=1;
        break;
      }
      fscanf(fp,"%s %s %d %s",comp_id,name,&num,mail1);

   }
   if(tmp==0){
      printf("Boyle kullanici bulunmamaktadir\n");
      printf("Kayit olmak icin isminizi , telefon numaranizi ve mailinizi sirasiyla giriniz\n");
      scanf("%s %d %s",yeni.isim,&yeni.numara,yeni.mail );

      int i;
      char* extension;//="gelen.txt";
      char fileSpec[32];
      FILE *out;

      snprintf( fileSpec, sizeof( fileSpec ), "txt/%skonusma.txt", yeni.id );
      out = fopen( fileSpec, "w" );
      fclose(out);

      snprintf( fileSpec, sizeof( fileSpec ), "txt/%slist.txt", yeni.id );
      out = fopen( fileSpec, "w" );
      fclose(out);
      fprintf(fp, "%s %s %d %s\n",yeni.id,yeni.isim,yeni.numara,yeni.mail);
      fclose(fp);
  }
  printf("Kullanici bilgilerinize bakmak istermisiniz?" );
  printf("\n\n\n\n\n\n" );
  if (tmp==1) {
      printf("%s %s  %d  %s\n",comp_id,name,num,mail1 );
  }
  else{
      printf("%s %s  %d  %s\n",yeni.id,yeni.isim,yeni.numara,yeni.mail );
  }
    printf("Write your message\n");
    scanf(" %[^\n]%*c",hello);

    printf("kime mesaj gondermek istiyorsunuz?\n" );
    scanf("%s",kime);

    strcat(buffer,kime);
    strcat(buffer," ");
    strcat(buffer,yeni.id);
    strcat(buffer," ");
    strcat(buffer,hello);
    int flag=0;
    snprintf( fileSpec, sizeof( fileSpec ), "txt/%slist.txt", yeni.id );
    out = fopen( fileSpec, "a+" );
    while (!feof(out)) {
        fscanf(out,"%s",list );
        a=strcmp(list,kime);
        if (a==0) {
          flag=1;
          send(sock,buffer,strlen(buffer),0);
          printf("Kullanici listenizde bulunuyor,mesajiniz %s kisisine basariyla gonderildi\n",kime );
      }
    }
    if(flag!=1){
          printf("Kullanici listenizde bulunmamaktadir,kisiyi listenize eklemek istiyorsaniz 1 e basiniz\n" );
          scanf("%d",&d );
          if (d==1) {
              fprintf(out, "%s\n",kime );
              send(sock,buffer,strlen(buffer),0);
              printf("%s kullanicisi listenize eklendi\n",kime );
              printf("Mesajiniz gonderildi");
          }
    }

    fclose(out);

    return 0;
}
