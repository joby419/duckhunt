// ayomide johnson
// cs335
// Duck Hunt
// my github:
// added sound to jasons work from github: https://github.com/Husky3388/duckhunt

#include "header.h"

void check_mouse(XEvent *e, Game *game)
{
    int y = WINDOW_HEIGHT - e->xbutton.y;

    Duck *d = game->duck;
    Duck *saved = new Duck;
    struct timespec dt;
    clock_gettime(CLOCK_REALTIME, &dt);
    double ts;

    if (e->type == ButtonRelease) {
        return;
    }
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) {
//#ifdef USE_SOUND //////////////////////////////////////////////////
            //Left button was pressed
            while(d)
            {
		fmod_playsound(0);
                if(e->xbutton.x >= d->s.center.x - d->s.width &&
                        e->xbutton.x <= d->s.center.x + d->s.width &&
                        y <= d->s.center.y + d->s.height &&
                        y >= d->s.center.y - d->s.height)
                {
                    makeDeadDuck(game, d);
                    ts = timeDiff(&d->time, &dt);
                    if(ts < 1.5)
                    {
                        game->deadD->points = true;
                        game->score += 200;
                    }
                    else
                    {
                        game->deadD->points = false;
                        game->score += 100;
                    }
                    saved = d->next;
                    deleteDuck(game, d);
                    d = saved;
                    game->bullets--;
                    game->duckShot++;
                    game->duckCaptured++;
                    if(game->bullets < 1)
                    {
                        if(game->n == 1)
                        {
                            makeFreeDuck(game, d);
                            saved = d->next;
                            deleteDuck(game, d);
                            d = saved;
                        }
                        return;
                    }
                    return;
                }
                if(game->n == 2)
                {
                    d = d->next;
                    if(e->xbutton.x >= d->s.center.x - d->s.width &&
                            e->xbutton.x <= d->s.center.x + d->s.width &&
                            y <= d->s.center.y + d->s.height &&
                            y >= d->s.center.y - d->s.height)
                    {
                        makeDeadDuck(game, d);
                        ts = timeDiff(&d->time, &dt);
                        if(ts < 1.5)
                        {
                            game->deadD->points = true;
                            game->score += 200;
                        }
                        else
                        {
                            game->deadD->points = false;
                            game->score += 100;
                        }
                        saved = d->prev;
                        deleteDuck(game, d);
                        d = saved;
                        game->bullets--;
                        game->duckShot++;
                        game->duckCaptured++;
                        if(game->bullets < 1)
                        {
                            if(game->n == 1)
                            {
                                makeFreeDuck(game, d);
                                saved = d->next;
                                deleteDuck(game, d);
                                d = saved;
                            }
                            return;
                        }
                        return;
                    }
                }
                if(game->bullets <= 1)
                {
		    game->bullets--;
                    if(game->n == 2)
                    {
                        d = d->prev;
                    }
                    makeFreeDuck(game, d);
                    saved = d->next;
                    deleteDuck(game, d);
                    d = saved;
                    if(game->n == 1)
                    {
                        makeFreeDuck(game, d);
                        saved = d->next;
                        deleteDuck(game, d);
                        d = saved;
                    }
                    return;
                }
                game->bullets--;
                d = d->next;
            }
        }
//#endif
    }
    if (e->xbutton.button==3) {
        //Right button was pressed
        return;
    }
}

//---------------------------------------------------
void init_sounds(void)
{
#ifdef USE_SOUND
    //FMOD_RESULT result;
    if (fmod_init()) {
        std::cout << "ERROR - fmod_init()\n" << std::endl;
        return;
    }
    if (fmod_createsound((char *)"./sounds/gunshot.wav", 0)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }
    if (fmod_createsound((char *)"./sounds/startgame.mp3", 1)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }
    if (fmod_createsound((char *)"./sounds/startround.mp3", 2)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }
    if (fmod_createsound((char *)"./sounds/intro.mp3", 3)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }
    if (fmod_createsound((char *)"./sounds/doglaugh.mp3", 4)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }
    if (fmod_createsound((char *)"./sounds/drop.mp3", 5)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }
    if (fmod_createsound((char *)"./sounds/endround.mp3", 6)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }

    if (fmod_createsound((char *)"./sounds/bark.mp3",7)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }

    if (fmod_createsound((char *)"./sounds/quack.mp3",8)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }
    
    if (fmod_createsound((char *)"./sounds/land.mp3",9)) {
        std::cout << "ERROR - fmod_createsound()\n" << std::endl;
        return;
    }
    
    if (fmod_createsound((char *)"./sounds/win.mp3",10)) {
       std::cout << "ERROR - fmod_createsound()\n" << std::endl;
       return;
    }
    
    
    fmod_setmode(0,FMOD_LOOP_OFF);
    //fmod_playsound(0);
    //fmod_systemupdate();
    #endif //USE_SOUND
}
