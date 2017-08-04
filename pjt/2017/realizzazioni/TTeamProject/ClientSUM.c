#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PARAM_BUFFER_SIZE 1024
//#define PARAM_CLIENT_ADDRESS "192.168.43.106"
#define PARAM_CLIENT_ADDRESS "127.0.0.1"
#define PARAM_CLIENT_PORT 7891

#define OP_TYPE_INV -1
#define OP_TYPE_NUM +0
#define OP_TYPE_PTR +1
#define OP_TYPE_STR +2

void* sum(char *, int *);
typedef struct {
  int type;
  char str[];
} Operand;


int cntstr(char *b) {
  int i = 0;
  while(*b != '\0') {i++;b++;}
  return i;
}

void catstr(char *a, char *b, char *res) {
  int _cnt = 0;
  while(*a != '\0') {
    *(res+_cnt) = *a;
    _cnt++;
    a++;
  }
  while(*b != '\0') {
    *(res+_cnt) = *b;
    _cnt++;
    b++;
  }
  *(res+_cnt) = '\0';
}

int getType(char*, int); 
int is_int( char*, int);
int is_ptr( char*, int);
int is_str( char*, int);

Operand* getOperand(char *buffer, int size) {
  int i = 0;
  Operand *o = malloc(sizeof(char)*(size+1)+sizeof(int));
  if(o == NULL) {
    return NULL; 
  }
  for(i;i<size;i++) {
    o->str[i] = buffer[i];
  }
  o->str[i] = '\0';
  o->type = getType(buffer,size);
  //printf("get:::::::::operando: %s; type: %d\n",o->str,o->type);
  return o;
}

void deleteOperand(Operand *o) {
  if(o==NULL) return;
  free(o);
}
Operand* somma(Operand *o1, Operand *o2);

Operand* rsum(Operand **l) {

  if(l[0]==NULL) return NULL;
  if(l[1]==NULL) return l[0];

  Operand **l_i = l;
  int size = 0;
  while(l[size] != NULL) {size++;}
  l = l_i;
  Operand *o = somma(l[0],l[1]);
  size-=1;
  Operand *operandi[size];
  operandi[0] = o;
  int cnt=1;
  while(l[cnt+1] != NULL) {
    operandi[cnt] = l[cnt+1];
    cnt++;
  }
  operandi[cnt] = NULL;
  return rsum(operandi);

}

int shiftPtr(int ptr,int s) {
  return ptr+=s*sizeof(char);
}

Operand* somma(Operand *o1, Operand *o2) {
  if(o1 == NULL && o2 == NULL) return NULL;
  if(o1 == NULL) return o2;
  if(o2 == NULL) return o1;

  if(o1->type == OP_TYPE_NUM && o2->type== OP_TYPE_NUM) {

    int op1 = atoi(o1->str);
    int op2 = atoi(o2->str);
    int sum = op1+op2;
    int sum1 = sum;
    int cnt = 0;
    while(sum1>0) {
      cnt++;
      sum1/=10;
    }
    char somma[cnt];
    //printf("o1:%d   o2:%d   r:%d\n",op1,op2,sum);
    sprintf(somma, "%d", sum);
    return getOperand(somma,cnt);

  } else if(o1->type == OP_TYPE_STR || o2->type== OP_TYPE_STR) {
      int cnt = cntstr(o1->str)+cntstr(o2->str);
      char res[cnt+1];
      catstr(o1->str,o2->str,res);
      return getOperand(res,cntstr(res));
  } else if(o1->type == OP_TYPE_PTR && o2->type== OP_TYPE_NUM)  {
      int hex_ptr = (int)strtol(((o1->str)+3), NULL, 16);
      int sht = atoi(o2->str);
      hex_ptr += 8*sht;
      int cnt_i = 0;
      int tmp = hex_ptr;
      while(hex_ptr>0) {
        cnt_i++;
        hex_ptr/=10;
      }
      cnt_i+=3;
      printf("%d      %d     \n",tmp,cnt_i);
      char _nuovo[cnt_i];
      sprintf(_nuovo, "00x%x",tmp);
      return getOperand(_nuovo,cnt_i);
  } else if(o1->type == OP_TYPE_NUM && o2->type== OP_TYPE_PTR)  {
      int hex_ptr = (int)strtol(((o2->str)+3), NULL, 16);
      int sht = atoi(o1->str);
      hex_ptr += 8*sht;
      int cnt_i = 0;
      int tmp = hex_ptr;
      while(hex_ptr>0) {
        cnt_i++;
        hex_ptr/=10;
      }
      cnt_i+=3;
      printf("%d      %d     \n",tmp,cnt_i);
      char _nuovo[cnt_i];
      sprintf(_nuovo, "00x%x", tmp);
      return getOperand(_nuovo,cnt_i);
  } else printf("\nL'OPERAZIONE NON SI PUO FARE\n");

}



int main(){
  setvbuf(stdout, NULL, _IONBF, 0);
  int sockfd;
  char buffer[PARAM_BUFFER_SIZE];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PARAM_CLIENT_PORT);
  serverAddr.sin_addr.s_addr = inet_addr(PARAM_CLIENT_ADDRESS);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
  connect(sockfd, (struct sockaddr *) &serverAddr, addr_size);
 
  usleep(100);
  write(sockfd, "SUM", 3);
  usleep(100);

  int size;

  while(1) {
    usleep(100);
    size = recv(sockfd, buffer, PARAM_BUFFER_SIZE, 0);
    usleep(100);
    if(size != -1 && size != 0) {
      if(strcmp(buffer,"CLOSE")==0) break;
      else {
        buffer[size] = '\0';
        buffer[size+1] = '\0';
        buffer[size+2] = '\0';
        buffer[size+3] = '\0';
        printf("Data size:%d received from server: %s\n",size,buffer);
        char *start_of_buffer = buffer;

        int n_operands = 0;
        while(*start_of_buffer!='\0'){
          if(*start_of_buffer=='+') n_operands++;
          start_of_buffer++;
        }
        n_operands++;
        n_operands++;
        printf("#operandi %d\n",n_operands);

        Operand *operandi[n_operands];
        int curr_operand = 0;

        start_of_buffer = buffer;
        char *itr_buffer = buffer;

        int size_o = 0;

        while(itr_buffer[size_o] != '\0') {
          while(itr_buffer[size_o] != '+' && itr_buffer[size_o] != '\0' ) {
            size_o++;
          }
          Operand *o = getOperand(start_of_buffer,size_o);
          if(o==NULL) printf("Null returned\n");
          operandi[curr_operand++] = o;
          start_of_buffer = &(itr_buffer[size_o+1]);
          itr_buffer = &(itr_buffer[size_o+1]);
          size_o = 0;
        }
        operandi[curr_operand] = NULL;
        int _i = 0;

        for(_i;_i<n_operands;_i++) {
          if(operandi[_i] == NULL) printf("operando %d è nullo\n",_i);
          else printf("operando: %s; type: %d\n",operandi[_i]->str,operandi[_i]->type);
        }
        /*while(*operandi != NULL) {
          Operand *op = *operandi;
          if(op == NULL) printf("operando  è nullo\n");
          else printf("operando: %s; type: %d\n",op->str,op->type);
        }*/
        

        Operand *r = rsum(operandi);
        printf("Risultato = {val: %s, type: %d}\nIn attesa di nuove istruzioni...",r->str,r->type);
        int acnt = 0;
        while(r->str[acnt++]!='\0');
        char toserv[3+acnt];
        catstr("RES",r->str,toserv);
        write(sockfd,toserv,3+acnt);
        
        _i = 0;
        for(_i;_i<n_operands-1;_i++) {
          free(operandi[_i]);
          operandi[_i] = NULL;
        }
      }
    } else if(size == 0) break;

  }
  printf("Arrivederci stronzi!!!\n");

  return 0;
}


int getType(char *b, int l) {
  if(is_int(b,l)) return OP_TYPE_NUM;
  if(is_ptr(b,l)) return OP_TYPE_PTR;
  if(is_str(b,l)) return OP_TYPE_STR;
  return -1;
}

int is_int(char *b, int s) {
  int i = 0;
  for(i;i<s;i++) if(b[i]<'0'||b[i]>'9') return 0;
  return 1;
}

int is_ptr(char *b, int s) {
  if(b[0] != '0') return 0;
  if(b[1]!='0') return 0;
  if(b[2]!='x' && b[2]!='X') return 0;
  int i;
  for(i=3;i<s;i++) {
    if (!((b[i]>='A' && b[i]<='F') || (b[i]>='a' && b[i]<='f') || (b[i]>='0' && b[i]<='9'))) return 0;
  }
  return 1;
}

int is_str(char *b, int s) {
  if(!is_int(b,s) && !is_ptr(b,s)) return 1;
  return 0; 
}


