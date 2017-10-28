//
// Created by pedro on 27/10/17.
//
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>

using namespace std;
#define N 7
#define M 10

void pr(ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* asteroid, char board[N][M],ALLEGRO_BITMAP* bass,ALLEGRO_BITMAP* fondo,bool final) {
    al_draw_bitmap(fondo,0,0,0);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 10; j++) {
            switch (board[i][j]) {
                case ('#'):
                    al_draw_bitmap(image, j * 100, i * 100, 0);
                    break;
                case ('x'):
                    al_draw_bitmap(asteroid, j * 100, i * 100, 0);
                    break;
                case ('F'):
                    al_draw_bitmap(bass, j * 100, i * 100, 0);
                    break;
                case('o'):
                    if(final)
                        al_draw_filled_circle((j*100)+50,(i*100)+50,5,al_map_rgb(0,0,255));
                    break;


            }
        }

    }
    al_flip_display();
    al_rest(0.25);
    al_clear_to_color(al_map_rgb(0,0,0));

}

void printSolution(char matriz[N][M] ) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout<<matriz[i][j];
        cout<<endl;
    }
    cout<<"-----------"<<endl;
}

bool check(char matriz[N][M], int x, int y,ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* asteroid,ALLEGRO_BITMAP* bass,ALLEGRO_BITMAP* fondo){
    printSolution(matriz);


    if(x>=0 && x<N && y>=0 && y<M) {
        if (matriz[x][y] == 'F') {
            matriz[x][y] = '#';
            pr(image,asteroid,matriz,bass,fondo,false);
            return true;
        }
        if (matriz[x][y] == '0' ) {
            matriz[x][y] = '#';
            pr(image,asteroid,matriz,bass,fondo, false);
            matriz[x][y] = 'o';




            if (check(matriz, x, y+1,image,asteroid, bass,fondo)) {
                return true;
            } else if (check(matriz, x-1, y,image,asteroid, bass,fondo)) {
                return true;
            } else if (check(matriz, x+1, y,image,asteroid, bass,fondo)) {
                return true;
            } else if (check(matriz, x, y-1,image,asteroid, bass, fondo)) {
                return true;
            } else {
                matriz[x][y] = '#';
                pr(image,asteroid,matriz,bass,fondo, false);
                matriz[x][y] = 'a';
                return false;
            }
        }
    }
    return false;
}

void makeMatriz(char matriz[N][M]){
    for(int i=0;i<N;i++){
        for(int j=0; j<M;j++){
            matriz[i][j]= '0';
        }

        for(int k=0;k<2;k++) {
            int y = rand() % 10 + 1;
            matriz[i][y] = 'x';
        }
    }

    int x = rand()%7;
    matriz[x][M-1]='F';
}

int main() {
    srand(time(NULL));// Para el random
    char matriz[N][M];//makeMatriz
    int W = 1000;
    int h = 700;
    bool done = false;
    char title1[] = "Bien hecho";
    char msj1[] = "Encontrado!!!";
    char pregunta1[] = "¿Desea volverlo hacer?";
    char title2[] = "Fallo!";
    char msj2[] = "No existe Ruta";

    //allegro variable
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_BITMAP* image = NULL;
    ALLEGRO_BITMAP* asteroid = NULL;
    ALLEGRO_BITMAP* bass = NULL;
    ALLEGRO_BITMAP* fondo = NULL;

    //program init
    if(!al_init())
        return -1;

    display = al_create_display(W,h);

    if(!display)
        return -1;

    //addon init
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();


    // cargar las imágenes
    image = al_load_bitmap("/home/pedro/Escritorio/MillenniumFalcon.png");
    asteroid = al_load_bitmap("/home/pedro/Escritorio/asteroids.png");
    bass = al_load_bitmap("/home/pedro/Escritorio/Base.png");
    fondo = al_load_bitmap("/home/pedro/Escritorio/Space.png");

    //Cola de eventos
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());


    // Ciclo infinito
    while (!done){

        makeMatriz(matriz);


        if ( check(matriz,2,0,image,asteroid,bass,fondo) == false ){
            if(al_show_native_message_box(display,title2,msj2,pregunta1,NULL,ALLEGRO_MESSAGEBOX_OK_CANCEL)== 2){
                return 0;
            }
            cout<<"Solution does not exist"<<endl;

        }else{
            pr(image,asteroid,matriz,bass,fondo, true);
            if(al_show_native_message_box(display,title1,msj1,pregunta1,NULL,ALLEGRO_MESSAGEBOX_OK_CANCEL)== 2){
                return 0;
            }
            cout<<"encontrado"<<endl;
        }





    }

    al_destroy_bitmap(image);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}

