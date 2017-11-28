#ifndef DEF_MOVE
#define DEF_MOVE

#include "defs.h"

void updateGame(Game *game);
void updateHand(Game *game);
void updateBall(Game *game, DynObj *ball);
void updateDummyLauncher(Game *game, DynObj *dummyLauncher);
void updateForms(Game *game, DynObj *form);
void updateObj(Game *game);
void pickItems(Game *game);
void updateLinks(Game *game);
void move(Game *game, int vx, int vy);
bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
bool collisionMap(Game *game, int x1, int y1, int w1, int h1);
DynObj *collisionMapObj(Game *game, int x1, int y1, int w1, int h1,  DynObj *dynObj);
DynObj *collisionMapObjNoSolid(Game *game, int x1, int y1, int w1, int h1, DynObj *dynObj);
void gravite(Game *game, Perso *perso);
void graviteObj(Game *game);
void destroyBox(Game *game, DynObj *dynObj);
void updateProjectilesPosition(Game *game);
void jump(Perso *perso);

#endif
