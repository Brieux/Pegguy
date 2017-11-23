#include "../include/lvlEditor.h"

Editor *loadEditor(int map_selected)
{
  Editor *editor = malloc(sizeof(Editor));
  if (!editor)
  {
    error("Unable to alloc game.");
  }
  editor->screen = initScreen("Editor");
  editor->input = generateInput();
  editor->typeAct = EMPTY;
  editor->level = map_selected;
  editor->dep_x = 0;
  editor->dep_y = 0;
  editor->nbDynObj = 0;
  editor->background = loadTexture("../graphics/background.png", editor->screen->pRenderer);
  FILE *file = fopen("../texts/level1.txt", "r");
  if (!file)
  {
    loadEmptyMap(editor);
  }
  else
  {
    if (!searchLevelEditor(file, editor->level))
    {
      fclose(file);
      loadEmptyMap(editor);
    }
    else
    {
      jumpLine(file);
      loadMapEditor(editor, file);
    }
  }
  loadBlocsEditor(editor);
  SDL_ShowCursor(SDL_ENABLE);

  return editor;
}

DynObj *initBlocEditor(Editor *editor, int x, int y, int type)
{
  DynObj *dynObj = malloc(sizeof(DynObj));
  dynObj->type = type;
  dynObj->x = x;
  dynObj->y = y;
  dynObj->w = 32;
  dynObj->h = 32;
  if (dynObj->type > 50)
  {
    editor->nbDynObj++;
  }
  char *image;
  switch (dynObj->type)
  {
    case EMPTY:
      image = "../graphics/grid.png";
      break;
    case GROUND :                   //case sol
      image = "../graphics/Dirt.png";
      break;
    case GROUND_2 :                   //case sol
      image = "../graphics/Dirt_2.png";
      break;
    case BOX :
      image = "../graphics/box.png";
      dynObj->w = 64;
      dynObj->h = 64;
      break;
    case BOX_DESTROYABLE_EMPTY :
      image = "../graphics/box_destroyable.png";
      dynObj->w = 64;
      dynObj->h = 64;
      break;
    case BOX_DESTROYABLE_BALL :
      image = "../graphics/box_destroyable.png";
      dynObj->w = 64;
      dynObj->h = 64;
      break;
    case BOX_DESTROYABLE_DUMMY_LAUNCHER :
      image = "../graphics/box_destroyable.png";
      dynObj->w = 64;
      dynObj->h = 64;
      break;
    case TARGET :
      image = "../graphics/target.png";
      break;
    case DOOR :
      image = "../graphics/door.png";
      dynObj->h = 64;
      break;
    case NPC1 :
      image = "../graphics/npc.png";
      dynObj->h = 64;
      break;
  }
  dynObj->image = loadTexture(image, editor->screen->pRenderer);

  return dynObj;
}

void loadEmptyMap(Editor *editor)
{
  editor->wmap = 50;
  editor->hmap = 30;
  editor->map = calloc(editor->wmap, sizeof(DynObj*));
  if (!editor->map)
  {
    error("Unable to calloc map");
  }

  for (int i=0; i<editor->wmap; i++)
  {
    editor->map[i] = malloc(editor->hmap*sizeof(DynObj*));
    if (!editor->map[i])
    {
      error("Unable to calloc map");
    }
  }
  for (int x=0; x<editor->wmap; x++)
  {
    for (int y=0; y<editor->hmap; y++)
    {
      editor->map[x][y] = initBlocEditor(editor, x*32 + DEP_MAP_X, y*32 + DEP_MAP_Y, EMPTY);
    }
  }
}

bool searchLevelEditor(FILE *file, int level)
{
  //on cherche le niveau correspondant
  int lvl_actu=0;
  while (lvl_actu!=level)
  {
    fscanf(file, "Lvl:%d", &lvl_actu);
    if (lvl_actu==level) {return true;}
    //tan qu'on ne trouve pas on saute une ligne
    if (jumpLine(file)==-1)
    {
      return false;
    }
  }
  return true;
}

void loadMapEditor(Editor *editor, FILE *file)
{
  int nbDynObj = 0;
  fscanf(file, "x:%d y:%d", &editor->wmap, &editor->hmap);//on recupere la taille de la grille
  jumpLine(file);//puis on passe à la ligne suivante
  fscanf(file, "nbDynObj:%d", &nbDynObj);//on recupere le nombre d'objets dynamiques
  jumpLine(file);//puis on passe à la ligne suivante

  editor->map = calloc(editor->wmap, sizeof(DynObj*));
  if (!editor->map)
  {
    error("Unable to calloc map");
  }

  for (int i=0; i<editor->wmap; i++)
  {
    editor->map[i] = malloc(editor->hmap*sizeof(DynObj*));
    if (!editor->map[i])
    {
      error("Unable to calloc map");
    }
  }

  for (int y=0; y<editor->hmap; y++)
  {
    for (int x=0; x<editor->wmap; x++)
    {
      editor->map[x][y] = initBlocEditor(editor, x*32 + DEP_MAP_X, y*32 + DEP_MAP_Y, fgetc(file));
    }
    jumpLine(file);
  }
  editor->nbDynObj = nbDynObj;
}

void loadBlocsEditor(Editor *editor)
{
  editor->nbBlocs = 9;
  editor->blocs = malloc(editor->nbBlocs*sizeof(DynObj*));
  for (int i=0; i<editor->nbBlocs; i++)
  {
    if (i>1)
    {
      editor->nbDynObj--;
    }
    switch (i)
    {
      case 0 :
        editor->blocs[i] = initBlocEditor(editor, 0, 0, GROUND);
        break;
      case 1 :
        editor->blocs[i] = initBlocEditor(editor, i*32, 0, GROUND_2);
        break;
      case 2 :
        editor->blocs[i] = initBlocEditor(editor, i*32, 0, BOX);
        break;
      case 3 :
        editor->blocs[i] = initBlocEditor(editor, i*32+32, 0, BOX_DESTROYABLE_EMPTY);
        break;
      case 4 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, BOX_DESTROYABLE_BALL);
        break;
      case 5 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                0, BOX_DESTROYABLE_DUMMY_LAUNCHER);
        break;
      case 6 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                0,TARGET);
        break;
      case 7 :
      editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                0, DOOR);
        break;
      case 8 :
      editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                0, NPC1);
        break;
    }
  }
}

void print(Editor *editor)
{
  for (int i=0; i<editor->nbBlocs; i++)
  {
    printf("type:%d x:%d y:%d w:%d h:%d\n", editor->blocs[i]->type, editor->blocs[i]->x,
            editor->blocs[i]->y, editor->blocs[i]->w, editor->blocs[i]->h);
  }
}

void drawBlocCursor(Editor *editor)
{
  if (editor->typeAct != EMPTY)
    drawImage(editor->cursorImage, editor->input->xCursor, editor->input->yCursor, editor->screen->pRenderer);
}

void drawEditor(Editor *editor)
{
  clearScreen(editor->screen);
  drawImage(editor->background, 0, 0, editor->screen->pRenderer);
  drawGrid(editor);
  drawMapEditor(editor);
  drawBlocsEditor(editor);
  drawBlocCursor(editor);


  SDL_RenderPresent(editor->screen->pRenderer);
}

void drawMapEditor(Editor *editor)
{
  for (int x=0; x<editor->wmap; x++)
  {
    for (int y=0; y<editor->hmap; y++)
    {
      if (editor->map[x][y]->type != EMPTY && editor->map[x][y]->y>=editor->dep_y+DEP_MAP_Y)
      {
        drawImage(editor->map[x][y]->image, x*32 + DEP_MAP_X - editor->dep_x,
           y*32 + DEP_MAP_Y - editor->dep_y, editor->screen->pRenderer);
      }
    }
  }
}

void drawGrid(Editor *editor)
{
  for (int x=0; x<editor->wmap; x++)
  {
    for (int y=0; y<editor->hmap; y++)
    {
      if (editor->map[x][y]->type == EMPTY && editor->map[x][y]->y>=editor->dep_y+DEP_MAP_Y)
      {
        drawImage(editor->map[x][y]->image, x*32 + DEP_MAP_X - editor->dep_x,
          y*32 + DEP_MAP_Y - editor->dep_y, editor->screen->pRenderer);
      }
    }
  }
}

void drawBlocsEditor(Editor *editor)
{
  for (int i=0; i<editor->nbBlocs; i++)
  {

    drawImage(editor->blocs[i]->image, editor->blocs[i]->x,
      editor->blocs[i]->y, editor->screen->pRenderer);
  }
}

void inputsEditor(Editor *editor)
{
  //On regarde quelle touche a été appuyée
  updateEvents(editor->input);

  //on agit en conséquence
  updateInputsEditor(editor);
}


void updateInputsEditor(Editor *editor)
{
  //quit
  if (editor->input->key[SDL_SCANCODE_ESCAPE])
  {
    editor->input->quit = true;
  }

  if (editor->input->key[SDL_SCANCODE_S])
  {
    editor->input->key[SDL_SCANCODE_S] = false;
    saveMap(editor);
  }

  //scrolling grille
  if (editor->input->key[SDL_SCANCODE_LEFT])
  {
    scrollEditor(editor, LEFT);
  }
  if (editor->input->key[SDL_SCANCODE_RIGHT])
  {
    scrollEditor(editor, RIGHT);
  }
  if (editor->input->key[SDL_SCANCODE_UP])
  {
    scrollEditor(editor, UP);
  }

  if (editor->input->key[SDL_SCANCODE_DOWN])
  {
    scrollEditor(editor, DOWN);
  }

  if (editor->input->mouse[SDL_BUTTON_LEFT])
  {
    collisionBlocEditor(editor, editor->input->xCursor,
      editor->input->yCursor, 0, 0);
    placeBloc(editor);
  }

  if (editor->input->mouse[SDL_BUTTON_RIGHT])
  {
    collisionBlocEditor(editor, editor->input->xCursor,
      editor->input->yCursor, 0, 0);
    deleteBloc(editor);
  }
}

DynObj *collisionBlocEditor(Editor *editor, int x, int y, int w, int h)
{
  for (int i=0; i<editor->nbBlocs; i++)
  {
    if ((collision(x, y, w, h,
              editor->blocs[i]->x, editor->blocs[i]->y, editor->blocs[i]->w,
                                editor->blocs[i]->h)))
    {
      editor->typeAct = editor->blocs[i]->type;
      editor->cursorImage = editor->blocs[i]->image;
      return editor->blocs[i];
    }
  }
  return 0;
}

void deleteBlocsAround(Editor *editor, DynObj *bloc)
{
  for (int x=0; x<editor->wmap; x++)
  {
    for (int y=0; y<editor->hmap; y++)
    {
      if (editor->map[x][y] != bloc && collision(bloc->x - editor->dep_x, bloc->y - editor->dep_y, bloc->w, bloc->h,
                editor->map[x][y]->x - editor->dep_x, editor->map[x][y]->y - editor->dep_y,
                editor->map[x][y]->w, editor->map[x][y]->h))
      {
        nbDynObjDecrease(editor, editor->map[x][y]->type);
        freeDynObj(editor->map[x][y]);
        editor->map[x][y] = initBlocEditor(editor, x*32+DEP_MAP_X, y*32+DEP_MAP_Y,
                              EMPTY);
      }
    }
  }
}

void  placeBloc(Editor *editor)
{
  if (editor->input->yCursor >= DEP_MAP_Y)
  {
    for (int x=0; x<editor->wmap; x++)
    {
      for (int y=0; y<editor->hmap; y++)
      {
        if (collision(editor->input->xCursor, editor->input->yCursor, 0, 0,
                  editor->map[x][y]->x - editor->dep_x, editor->map[x][y]->y - editor->dep_y, 32, 32))
        {
          nbDynObjDecrease(editor, editor->map[x][y]->type);
          freeDynObj(editor->map[x][y]);
          editor->map[x][y] = initBlocEditor(editor, x*32+DEP_MAP_X, y*32+DEP_MAP_Y,
                                editor->typeAct);
          deleteBlocsAround(editor, editor->map[x][y]);
          y = editor->hmap;
          x = editor->wmap;
        }
      }
    }
  }
}

void nbDynObjDecrease(Editor *editor, int type)
{
  if (type > 50)
  {
    editor->nbDynObj--;
  }
}

void deleteBloc(Editor *editor)
{
  for (int x=0; x<editor->wmap; x++)
  {
    for (int y=0; y<editor->hmap; y++)
    {
      if (collision(editor->input->xCursor, editor->input->yCursor, 0, 0,
                editor->map[x][y]->x - editor->dep_x, editor->map[x][y]->y - editor->dep_y, 32, 32))
      {
        nbDynObjDecrease(editor, editor->map[x][y]->type);
        freeDynObj(editor->map[x][y]);
        editor->map[x][y] = initBlocEditor(editor, x*32+DEP_MAP_X, y*32+DEP_MAP_Y,
                              EMPTY);
        deleteBlocsAround(editor, editor->map[x][y]);
        y = editor->hmap;
        x = editor->wmap;
      }
    }
  }
}

void scrollEditor(Editor *editor, int direction)
{
  switch (direction)
  {
    case LEFT:
      for (int i=0; i<5 && editor->dep_x>0; i++)
        editor->dep_x--;
      break;
    case RIGHT:
      for (int i=0; i<5 && editor->dep_x + WINDOW_W<editor->wmap*32; i++)
        editor->dep_x++;
      break;
    case UP:
      for (int i=0; i<5 && editor->dep_y>0; i++)
        editor->dep_y--;
      break;
    case DOWN:
      for (int i=0; i<5 && editor->dep_y + WINDOW_H<editor->hmap*32; i++)
        editor->dep_y++;
      break;
  }
}

void saveMap(Editor *editor)
{
  FILE *file = fopen("../texts/level1.txt", "r+");
  if (!file)
  {
    file = fopen("../texts/level1.txt", "w");
  }
  else
  {
    if (!searchLevelEditor(file, editor->level))
    {
      fclose(file);
      file = fopen("../texts/level1.txt", "a");
    }
    else
    {
      fseek(file, -5, SEEK_CUR);
    }
  }

  fprintf(file, "Lvl:%d\n", editor->level);
  fprintf(file, "x:%d y:%d\n", editor->wmap, editor->hmap);
  fprintf(file, "nbDynObj:%d\n", editor->nbDynObj);
  for (int y=0; y<editor->hmap; y++)
  {
    for (int x=0; x<editor->wmap; x++)
    {
      fputc(editor->map[x][y]->type, file);
    }
    fputc('\n', file);
  }

  fclose(file);
}


int main(int argc, char *argv[])
{
  int map_selected = 1;//selection du niveau en argument
  if (argc == 2){
  	  map_selected = atoi(argv[1]);
  }

  Editor *editor = loadEditor(map_selected);

  while (!editor->input->quit)//boucle principale
  {
    inputsEditor(editor);
    drawEditor(editor);
  }

  quitSDL(editor->screen);//on supprime tous les renderers et on quitte SDL

  return EXIT_SUCCESS;
}
