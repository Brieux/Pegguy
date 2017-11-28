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
  loadFontEditor(editor);
  editor->linkImage = loadTexture("../graphics/link.png", editor->screen->pRenderer);
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
  dynObj->link = NULL;
  if (dynObj->type > 50 && dynObj->type != B1)
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
    case TRIANGLE :
      image = "../graphics/triangle.png";
      break;
    case CIRCLE :
      image = "../graphics/circle.png";
      break;
    case SQUARE :
      image = "../graphics/square.png";
      break;
    case TRIANGLE_BASE :
      image = "../graphics/triangle_base.png";
      break;
    case CIRCLE_BASE :
      image = "../graphics/circle_base.png";
      break;
    case SQUARE_BASE :
      image = "../graphics/square_base.png";
      break;
    case B1 :
      image = "../graphics/ghost.png";
      break;
    case MOBILE_PLATFORM :
      image = "../graphics/mobile_platform.png";
      break;
    case BALL :
      image = "../graphics/billefinale.png";
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

void loadFontEditor(Editor *editor)
{
  if(TTF_Init()==-1)
  {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
  editor->font = malloc(sizeof(TTF_Font *));
  editor->font = TTF_OpenFont("../graphics/HACKED.ttf", 20);
  if (!editor->font)
  {
    fprintf(stderr, "Unable to load font: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void loadMapEditor(Editor *editor, FILE *file)
{
  int nbDynObj = 0;
  fscanf(file, "x:%d y:%d", &editor->wmap, &editor->hmap);//on recupere la taille de la grille
  jumpLine(file);//puis on passe à la ligne suivante
  fscanf(file, "nbDynObj:%d", &nbDynObj);//on recupere le nombre d'objets dynamiques
  printf("%d\n", nbDynObj);
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

  int xLink, yLink;
  for (int y=0; y<editor->hmap; y++)
  {
    for (int x=0; x<editor->wmap; x++)
    {
      editor->map[x][y] = initBlocEditor(editor, x*32 + DEP_MAP_X, y*32 + DEP_MAP_Y, fgetc(file));
      fscanf(file, ",x:%dy:%d/", &xLink, &yLink);
      editor->map[x][y]->xLink = xLink;
      editor->map[x][y]->yLink = yLink;
    }
    jumpLine(file);
  }
  for (int y=0; y<editor->hmap; y++)
  {
    for (int x=0; x<editor->wmap; x++)
    {
      if (editor->map[x][y]->xLink != -1 && editor->map[x][y]->yLink != -1)
      {
        editor->map[x][y]->link = editor->map[editor->map[x][y]->xLink][editor->map[x][y]->yLink];
      }
    }
  }
  editor->nbDynObj = nbDynObj;
}

void loadBlocsEditor(Editor *editor)
{
  editor->nbBlocs = 18;
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
      case 9 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, TRIANGLE);
        break;
      case 10 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, CIRCLE);
        break;
      case 11 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, SQUARE);
        break;
      case 12 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, TRIANGLE_BASE);
        break;
      case 13 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, CIRCLE_BASE);
        break;
      case 14 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, SQUARE_BASE);
        break;
      case 15 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, B1);
        editor->nbDynObj++;
        break;
      case 16 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, MOBILE_PLATFORM);
        break;
      case 17 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, BALL);
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

void drawInfosEditor(Editor *editor)
{
  char text[40];
  sprintf(text, "LEVEL: %d", editor->level);
  printLineEditor(editor, WINDOW_W - 200, 20,
            text);
  sprintf(text, "x: %d y: %d", editor->wmap, editor->hmap);
  printLineEditor(editor, WINDOW_W - 100, 20,
            text);
  sprintf(text, "Curseur:    x: %d y: %d", (editor->input->xCursor + editor->dep_x - DEP_MAP_X)/32,
                                        (editor->input->yCursor + editor->dep_y - DEP_MAP_Y)/32);
  printLineEditor(editor, WINDOW_W - 195, 50,
            text);
}

void printLineEditor(Editor *editor, int x, int y, char *text)
{
    SDL_Color color_text = {0, 0, 0, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(editor->font, text, color_text);
    if (!text_surface){
        fprintf(stderr, "consol_d error: Can't create surface\n");
        return;
    }
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(editor->screen->pRenderer, text_surface);
    if (!text_texture){
        fprintf(stderr, "consol_d error: Can't create texure\n");
        return;
    }
    drawImage(text_texture, x, y, editor->screen->pRenderer);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

void drawEditor(Editor *editor)
{
  clearScreen(editor->screen);
  drawImage(editor->background, 0, 0, editor->screen->pRenderer);
  drawGrid(editor);
  drawMapEditor(editor);
  drawBlocsEditor(editor);
  drawInfosEditor(editor);
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
  for (int x=0; x<editor->wmap; x++)
  {
    for (int y=0; y<editor->hmap; y++)
    {
      if (editor->map[x][y]->type != EMPTY && editor->map[x][y]->y>=editor->dep_y+DEP_MAP_Y)
      {
        if (editor->map[x][y]->link)
        {
          drawImage(editor->linkImage, x*32 + DEP_MAP_X - editor->dep_x,
             y*32 + DEP_MAP_Y - editor->dep_y, editor->screen->pRenderer);
          if (editor->map[x][y]->link->y>=editor->dep_y+DEP_MAP_Y)
           drawImage(editor->linkImage,editor->map[x][y]->link->x - editor->dep_x,
              editor->map[x][y]->link->y - editor->dep_y, editor->screen->pRenderer);
        }
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

  if (editor->input->key[SDL_SCANCODE_Q])
  {
    editor->input->key[SDL_SCANCODE_Q] = false;
    for (int x=0; x<editor->wmap; x++)
    {
      for (int y=0; y<editor->hmap; y++)
      {
        if (editor->map[x][y]->link)
        printf("bloc[%d][%d]type:%d link:%d\n", x, y, editor->map[x][y]->type, editor->map[x][y]->link->type);
      }
    }
  }

  //scrolling grille
  if (editor->input->key[SDL_SCANCODE_RIGHT])
  {
    if (editor->input->key[SDL_SCANCODE_R])
    {
      editor->input->key[SDL_SCANCODE_RIGHT] = false;
      resizeGrid(editor, RIGHT);
    }
    else
    {
      scrollEditor(editor, RIGHT);
    }
  }
  if (editor->input->key[SDL_SCANCODE_LEFT])
  {
    if (editor->input->key[SDL_SCANCODE_R])
    {
      editor->input->key[SDL_SCANCODE_LEFT] = false;
      resizeGrid(editor, LEFT);
    }
    else
    {
      scrollEditor(editor, LEFT);
    }
  }
  if (editor->input->key[SDL_SCANCODE_UP])
  {
    if (editor->input->key[SDL_SCANCODE_R])
    {
      editor->input->key[SDL_SCANCODE_UP] = false;
      resizeGrid(editor, UP);
    }
    else
    {
      scrollEditor(editor, UP);
    }
  }

  if (editor->input->key[SDL_SCANCODE_DOWN])
  {
    if (editor->input->key[SDL_SCANCODE_R])
    {
      editor->input->key[SDL_SCANCODE_DOWN] = false;
      resizeGrid(editor, DOWN);
    }
    else
    {
      scrollEditor(editor, DOWN);
    }
  }

  if (editor->input->mouse[SDL_BUTTON_LEFT])
  {
    if (!editor->input->key[SDL_SCANCODE_L])
    {
      collisionBlocEditor(editor, editor->input->xCursor,
        editor->input->yCursor, 0, 0);
      placeBloc(editor);
    }
    else
    {
      editor->input->mouse[SDL_BUTTON_LEFT] = false;
      linker(editor);
    }
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

void resizeGrid(Editor *editor, int direction)
{
  switch (direction)
  {
    case RIGHT:
      editor->wmap++;
      editor->map = realloc(editor->map, editor->wmap*sizeof(DynObj*));
      if (!editor->map)
      {
        error("Unable to calloc map");
      }
      editor->map[editor->wmap-1] = malloc(editor->hmap*sizeof(DynObj*));
      if (!editor->map[editor->wmap-1])
      {
        error("Unable to malloc map");
      }
      for (int y=0; y<editor->hmap; y++)
      {
        editor->map[editor->wmap-1][y] = initBlocEditor(editor, (editor->wmap-1)*32 + DEP_MAP_X, y*32 + DEP_MAP_Y, EMPTY);
      }
      break;

    case DOWN:
      editor->hmap++;
      for (int x=0; x<editor->wmap; x++)
      {
        editor->map[x] = realloc(editor->map[x], editor->hmap*sizeof(DynObj*));
        if (!editor->map[x])
        {
          error("Unable to malloc map");
        }
        editor->map[x][editor->hmap-1] = initBlocEditor(editor, x*32 + DEP_MAP_X,
                                                      (editor->hmap-1)*32 + DEP_MAP_Y, EMPTY);
      }
      break;

    case LEFT:
      if (editor->wmap > 1)
      {
        for (int y=0; y<editor->hmap; y++)
        {
          freeDynObj(editor->map[editor->wmap-1][y]);
        }
        free(editor->map[editor->wmap-1]);
        editor->wmap--;
        editor->map = realloc(editor->map, editor->wmap*sizeof(DynObj*));
      }
      break;

    case UP:
      if (editor->hmap > 1)
      {
        for (int x=0; x<editor->wmap; x++)
        {
          freeDynObj(editor->map[x][editor->hmap-1]);
          editor->map[x] = realloc(editor->map[x], (editor->hmap-1)*sizeof(DynObj*));
        }
        editor->hmap--;
      }
      break;
  }
}

void nbDynObjDecrease(Editor *editor, int type)
{
  if (type > 50 && type != B1)
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

void linker(Editor *editor)
{
  for (int x=0; x<editor->wmap; x++)
  {
    for (int y=0; y<editor->hmap; y++)
    {
      if (editor->map[x][y]->type != EMPTY)
      {
        if (collision(editor->input->xCursor, editor->input->yCursor, 0, 0,
                  editor->map[x][y]->x - editor->dep_x, editor->map[x][y]->y - editor->dep_y,
                  editor->map[x][y]->w, editor->map[x][y]->h))
        {
          if (!editor->link)
          {
            if (editor->map[x][y]->link)
            {
              editor->map[x][y]->link = NULL;
            }
            else
            {
              editor->linker = editor->map[x][y];
              editor->link = true;
            }
          }
          else
          {
            editor->linker->link = editor->map[x][y];
            editor->link = false;
          }
        }
      }
    }
  }
}

void scrollEditor(Editor *editor, int direction)
{
  switch (direction)
  {
    case LEFT:
      for (int i=0; i<10 && editor->dep_x>0; i++)
        editor->dep_x--;
      break;
    case RIGHT:
      for (int i=0; i<10 && editor->dep_x + WINDOW_W - DEP_MAP_X < editor->wmap*32; i++)
        editor->dep_x++;
      break;
    case UP:
      for (int i=0; i<10 && editor->dep_y>0; i++)
        editor->dep_y--;
      break;
    case DOWN:
      for (int i=0; i<10 && editor->dep_y + WINDOW_H - DEP_MAP_Y < editor->hmap*32; i++)
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
      if (editor->map[x][y]->link)
      {
        fprintf(file, ",x:%dy:%d/", (editor->map[x][y]->link->x-DEP_MAP_X)/32,
                (editor->map[x][y]->link->y-DEP_MAP_Y)/32);
      }
      else
      {
        fprintf(file, ",x:%dy:%d/", -1, -1);
      }
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
