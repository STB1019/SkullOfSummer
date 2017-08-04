#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <pthread.h>

#define PARAM_BUFFER_SIZE 1024
#define PARAM_CLIENT_ADDRESS "127.0.0.1"
//#define PARAM_CLIENT_ADDRESS "192.168.43.106"
#define PARAM_CLIENT_PORT 7891



//gcc -pthread ClientUSR.c `pkg-config --libs gtk+-2.0` ` pkg-config --cflags gtk+-2.0` -o clientUSR

int sockfd;
char buffer[PARAM_BUFFER_SIZE];
GtkWidget *label;

static void button_clicked(GtkWidget* widget, gpointer data);

static void button2_clicked(GtkWidget* widget, gpointer data);

static void check_state(GtkWidget* widget, gpointer data);


void *threadFunc(void *toggle);

char* concat(const char *s1, const char *s2);


int main(int argc, char* argv[]){

  gtk_init(&argc, &argv);
  GtkWidget *window, *btn, *btn2, *entry, *hbox1, *hbox2, *hbox3, *vbox, *image1, *image2, *image3, *toggle;
  GdkPixbuf *pixbuf;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window,"delete-event", G_CALLBACK(gtk_main_quit), NULL);
  
  
  
  //label = gtk_label_new("CLIENT UTENTE");
  //gtk_label_set_text(GTK_LABEL(label),"Connetitti");

  hbox1 = gtk_hbox_new(0,0);
  hbox2 = gtk_hbox_new(0,0);
  hbox3 = gtk_hbox_new(0,0);
  vbox = gtk_vbox_new(0,0);

  label = gtk_label_new("RISULTATI");

  pixbuf = gdk_pixbuf_new_from_file("/home/tommaso/Scrivania/SkullOfSummer/TTeamProject/Server.png", NULL);
  pixbuf = gdk_pixbuf_scale_simple(pixbuf, 50, 50, GDK_INTERP_BILINEAR);
  image1 = gtk_image_new_from_pixbuf(pixbuf);

  pixbuf = gdk_pixbuf_new_from_file("/home/tommaso/Scrivania/SkullOfSummer/TTeamProject/MAUROrasta.png", NULL);
  pixbuf = gdk_pixbuf_scale_simple(pixbuf, 50, 50, GDK_INTERP_BILINEAR);
  image2 = gtk_image_new_from_pixbuf(pixbuf);


  pixbuf = gdk_pixbuf_new_from_file("/home/tommaso/Scrivania/SkullOfSummer/TTeamProject/SERVERSEND.png", NULL);
  pixbuf = gdk_pixbuf_scale_simple(pixbuf, 50, 50, GDK_INTERP_BILINEAR);
  image3 = gtk_image_new_from_pixbuf(pixbuf);




  btn = gtk_button_new_with_label("Conosci Mauro™ ?");
  gtk_button_set_image(GTK_BUTTON(btn),image2);
  g_signal_connect(btn,"clicked", G_CALLBACK(button_clicked), NULL);


  
  entry = gtk_entry_new();
  //gtk_container_add(GTK_CONTAINER(window),label);

  btn2 = gtk_button_new_with_mnemonic("_Invia al Server");
  gtk_button_set_image(GTK_BUTTON(btn2),image3);
  

  g_signal_connect(btn2,"clicked", G_CALLBACK(button2_clicked), entry);
  g_signal_connect(entry,"activate", G_CALLBACK(button2_clicked), entry);

  toggle = gtk_toggle_button_new_with_mnemonic("_Connetti al Server");
  g_signal_connect(toggle,"toggled", G_CALLBACK(check_state), NULL);
  gtk_button_set_image(GTK_BUTTON(toggle),image1);


  



 
  gtk_box_pack_start(GTK_BOX(hbox1),toggle,1,0,0);
  gtk_box_pack_start(GTK_BOX(hbox1),btn,1,0,18);
  gtk_box_pack_start(GTK_BOX(hbox3),label,1,0,0);
  gtk_box_pack_start(GTK_BOX(hbox2),btn2,1,0,0);
  gtk_box_pack_start(GTK_BOX(hbox2),entry,1,0,0);

  gtk_box_pack_start(GTK_BOX(vbox),hbox1,1,0,3);
  gtk_box_pack_start(GTK_BOX(vbox),hbox2,1,0,40);
  gtk_box_pack_start(GTK_BOX(vbox),hbox3,1,0,40);

  



  gtk_container_set_border_width(GTK_CONTAINER(window),30);
  gtk_container_add(GTK_CONTAINER(window),vbox);
  //gtk_widget_set_size_request(window,500,500);
  gtk_window_set_title(GTK_WINDOW(window),"APPLICAZIONE UTENTE");
  gtk_widget_show_all(window);


  pthread_t pth;
	pthread_create(&pth,NULL,threadFunc,toggle);


  gtk_main();

  printf("Arrivederci stronzi!!!\n");
  
  return 0;
}



char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

static void button_clicked(GtkWidget* widget, gpointer data){
  GtkWidget *window , *image;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  image = gtk_image_new_from_file("/home/tommaso/Scrivania/SkullOfSummer/TTeamProject/MAURELLAD.png");

  gtk_container_add(GTK_CONTAINER(window),image);
  //gtk_widget_set_size_request(window,500,500);
  gtk_window_set_title(GTK_WINDOW(window),"ECCOLO, QUESTO È MAURO™");
  gtk_widget_show_all(window);
}


static void button2_clicked(GtkWidget* widget, gpointer data){
    g_print("\nIl server riceve: %s\n",gtk_entry_get_text(GTK_ENTRY(data)));
    char *msg = concat("DAT",gtk_entry_get_text(GTK_ENTRY(data)));
    send(sockfd,msg,strlen(msg),0);
    usleep(100);
    free(msg);
    gtk_entry_set_text(GTK_ENTRY(data),"");
}


static void check_state(GtkWidget* widget, gpointer data){
  if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){
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
        write(sockfd, "USE", 3);
        usleep(100);

        gtk_button_set_label(GTK_BUTTON(widget),"Disconnetti dal Server");
        
  }else{
    shutdown(sockfd ,SHUT_RDWR);
    close(sockfd);
    gtk_button_set_label(GTK_BUTTON(widget),"Connetti al Server");
  }
}



  void *threadFunc(void *toggle){
 
      int size;

      while(1) {

        size = recv(sockfd, buffer, PARAM_BUFFER_SIZE, 0);
       
        if(size != -1 && size != 0) {
          buffer[size] = '\0';
          printf("La risposta è: %s\n",buffer);
          gtk_label_set_text(GTK_LABEL(label),buffer);
          if(strcmp(buffer,"CLOSE")==0) break;
        }else if(size == 0  && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle))){
          gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle), 0);
          gtk_button_set_label(GTK_BUTTON(toggle),"Connetti al Server");
        
        }

      }

      return NULL;
    }


