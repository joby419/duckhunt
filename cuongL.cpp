//Cuong Le
//Duck Hunt Game

//I worked on some part of the background, the background transparent, and sprites with group .
//Im working on now for the menu with clickable buttons to Play and Exit  the game. 
//Next I will working for the spashscreen before the game begin.

#include "header.h"

/*
///////////////////////////////////////////////////////////////////////////////////////////////////////

Ppmimage *menuImage = NULL; //for menu splashscreen
GLuint menuTexture;//menu splashcreen
int menu = 1;// menu

void init_opengl(void)
{
menuImage = ppm6GetImage("./images/menu.ppm");// menu splashscreen
glGenTextures(1, &menuTexture);//menu

//menu splashscreen
    glBindTexture(GL_TEXTURE_2D, menuTexture);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                            menuImage->width, menuImage->height,
                            0, GL_RGB, GL_UNSIGNED_BYTE, menuImage->data);

    //-------------------------------------------------------------------

}

void render(Game *game)
{
if (menu) {

        glBindTexture(GL_TEXTURE_2D, menuTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(0, WINDOW_HEIGHT);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(WINDOW_WIDTH, 0);
        glEnd();
    }

 if (!menu){
    if(background) {
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(0, WINDOW_HEIGHT);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(WINDOW_WIDTH, 0);
        glEnd();
    }
     if(gameover) {
        glBindTexture(GL_TEXTURE_2D, gameoverbgTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(0, WINDOW_HEIGHT);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
   
     }
}
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  */

int check_keys(XEvent *e, Game *game) 
{
    Duck *d = game->duck;
    deadDuck *dd = game->deadD;
    freeDuck *fd = game->freeD;
    Dog *doge = game->dog;
    happyDog *hdoge = game->hdog;
    laughingDog *ldoge = game->ldog;

    //Was there input from the keyboard?
    if (e->type == KeyPress) {
        int key = XLookupKeysym(&e->xkey, 0);
        if (key == XK_Escape) {
            return 1;
        }
        //You may check other keys here.
        if(key == XK_1)
        {
	    fmod_stopsound();
	    fmod_playsound(2);
            game->menutest = false;
            gameover = false;
            while(d)
            {
                deleteDuck(game, d);
                d = d->next;
            }
            while(dd)
            {
                deleteDeadDuck(game, dd);
                dd = dd->next;
            }
            while(fd)
            {
                deleteFreeDuck(game, fd);
                fd = fd->next;
            }
            while(doge)
            {
                deleteDog(game, doge);
                doge = doge->next;
            }
            while(hdoge)
            {
                deleteHappyDog(game, hdoge);
                hdoge = hdoge->next;
            }
            while(ldoge)
            {
                deleteLaughingDog(game, ldoge);
                ldoge = ldoge->next;
            }
            game->n = 0;
            game->onScreen = 0;
            game->rounds = 1;
            game->duckCount = 0;
            game->duckShot = 0;
            game->bullets = 3;
            game->score = 0;
            game->duckCaptured = 0;
            game->oneDuck = true;
            game->twoDuck = false;
            game->animateDog = true;
            game->dogGone = false;
            game->afterDog = true;
            game->waitForDog = false;
        }
        if(key == XK_2)
        {
	    fmod_stopsound();
	    fmod_playsound(2);
            game->menutest = false;
            gameover = false;
            while(d)
            {
                deleteDuck(game, d);
                d = d->next;
            }
            while(dd)
            {
                deleteDeadDuck(game, dd);
                dd = dd->next;
            }
            while(fd)
            {
                deleteFreeDuck(game, fd);
                fd = fd->next;
            }
            while(doge)
            {
                deleteDog(game, doge);
                doge = doge->next;
            }
            while(hdoge)
            {
                deleteHappyDog(game, hdoge);
                hdoge = hdoge->next;
            }
            while(ldoge)
            {
                deleteLaughingDog(game, ldoge);
                ldoge = ldoge->next;
            }
            game->n = 0;
            game->onScreen = 0;
            game->rounds = 1;
            game->duckCount = 0;
            game->duckShot = 0;
            game->bullets = 3;
            game->score = 0;
            game->duckCaptured = 0;
            game->oneDuck = false;
            game->twoDuck = true;
            game->animateDog = true;
            game->dogGone = false;
            game->afterDog = true;
            game->waitForDog = false;
        }
        // press s to start the game
        if(key == XK_s)
        {
            menu ^= 1;
        }
    }
    return 0;
}

void Menu(Game *game)
{
    float w, h;

    Rect r;
    r.bot = WINDOW_HEIGHT - 550;
    r.left = WINDOW_WIDTH - 715;
    r.center = 0;

    //-------------------------------------------------------------------
    //Drawing Boxes
    Shape *s;

    if (game->menutest == true) {
        const char* text[3] = {"One Duck Hunt - Press 1", "Two Duct Hunt - Press 2", "      Exit - Press ESC"}; 
        for(int i=5; i<8; i++) {
            glColor3ub(90, 140, 90);
            s = &game->box[i];
            glPushMatrix();
            glTranslatef(s->center.x, s->center.y, s->center.z);
            w = s->width;
            h = s->height;
            r.bot = s->height - 50;
            r.left = s->width - 230;
            glBegin(GL_QUADS);
            glVertex2i(-w,-h);
            glVertex2i(-w, h);
            glVertex2i( w, h);
            glVertex2i( w,-h);
            glEnd();
            if (i == 5)
                ggprint13(&r, 35, 0x00ffffff, text[0]);
            if (i == 6)
                ggprint13(&r, 35, 0x00ffffff, text[1]);
            if (i == 7)
                ggprint13(&r, 35, 0x00ffffff, text[2]);
            r.bot = s->height - 120;
            r.left = s->width - 170;
            if (i == 5)
    		ggprint13(&r, 35, 0x00ffffff, "");
            if (i == 6)
                ggprint13(&r, 35, 0x00ffffff, "");
            if (i == 7)
                ggprint13(&r, 35, 0x00ffffff, "");
            glPopMatrix();
        }
    }
}
