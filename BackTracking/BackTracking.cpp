//
// Created by pedro on 27/10/17.
//
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;
#define N 7
#define M 10

void pr(ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* asteroid, char board[N][M],ALLEGRO_BITMAP* bass,ALLEGRO_BITMAP* fondo) {
    al_draw_bitmap(fondo,0,0,0);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 10; j++) {
            switch (board[i][j]) {
                case ('#'):
                    al_draw_bitmap(image, j * 100, i * 100, 0);
                    break;
                case ('l'):
                    al_draw_bitmap(asteroid, j * 100, i * 100, 0);
                    break;
                case ('F'):
                    al_draw_bitmap(bass, j * 100, i * 100, 0);
                    break;

            }
        }

    }
    al_flip_display();
    al_rest(0.25);
    al_clear_to_color(al_map_rgb(0,0,0));

}


void printSolution(char board[N][M] )
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            cout<<board[i][j];
        cout<<endl;
    }
    cout<<"-----------"<<endl;
}

bool check(char board[N][M], int x, int y,ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* asteroid,ALLEGRO_BITMAP* bass,ALLEGRO_BITMAP* fondo){
    printSolution(board);


    if(x>=0 && x<N && y>=0 && y<M) {
        if (board[x][y] == 'F') {
            return true;
        }
        if (board[x][y] == '0' ) {
            board[x][y] = '#';
            pr(image,asteroid,board,bass,fondo);
            board[x][y] = 'a';




            if (check(board, x, y + 1,image,asteroid, bass,fondo)) {
                return true;
            } else if (check(board, x - 1, y,image,asteroid, bass,fondo)) {
                return true;
            } else if (check(board, x, y - 1,image,asteroid, bass,fondo)) {
                return true;
            } else if (check(board, x + 1, y,image,asteroid, bass, fondo)) {
                return true;
            } else {
                board[x][y] = '#';
                pr(image,asteroid,board,bass,fondo);
                board[x][y] = '0';
                return false;
            }
        }
    }
    return false;
}

int main() {
    char board[N][M] = {{'l','0','l','0','0','0','l','0','l','0'},
                        {'l','0','l','0','0','0','0','0','l','0'},
                        {'0','0','l','0','0','l','0','0','0','F'},
                        {'0','l','l','0','0','l','0','l','0','0'},
                        {'0','0','0','0','l','0','0','0','0','0'},
                        {'0','0','l','0','0','l','0','0','l','0'},
                        {'0','0','0','0','0','0','0','0','0','0'}
    };

    int W = 1000;
    int h = 700;
    bool done = false;

    int imageW = 0;
    int imageH = 0;

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

    image = al_load_bitmap("/home/pedro/Escritorio/MillenniumFalcon.png");
    asteroid = al_load_bitmap("/home/pedro/Escritorio/asteroids.png");
    bass = al_load_bitmap("/home/pedro/Escritorio/Base.png");
    fondo = al_load_bitmap("/home/pedro/Escritorio/Space.png");
    imageW = al_get_bitmap_width(image);
    imageH = al_get_bitmap_height(image);


    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());


    /////////////
    while (!done){
        ALLEGRO_EVENT ev;

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_1:
                    done = true;
                    break;
            }
        }
        if ( check(board,2,0,image,asteroid,bass,fondo) == false )
        {
            cout<<"Solution does not exist"<<endl;
            return false;
        }else{
            cout<<"encontrado"<<endl;
        }




        al_wait_for_event(event_queue, &ev);
    }

    al_destroy_bitmap(image);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}

