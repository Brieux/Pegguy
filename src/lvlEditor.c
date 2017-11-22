#include "../include/lvlEditor.h"

Editor *loadEditor()
{
  Editor *editor = malloc(sizeof(Editor));
  if (!editor)
  {
    error("Unable to alloc game.");
  }
  editor->screen = initScreen("Editor");
  editor->input = generateInput();
  editor->typeAct = EMPTY;
  loadEmptyMap(editor);
  SDL_ShowCursor(SDL_ENABLE);

  return editor;
}

DynObj *initBlocEditor(Editor *editor, int x, int y, int w, int h, int type)
{
  DynObj *dynObj = malloc(sizeof(DynObj));
  dynObj->type = type;
  dynObj->x = x;
  dynObj->y = y;
  dynObj->w = w;
  dynObj->h = h;
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
      break;
    case BOX_DESTROYABLE_EMPTY :
      image = "../graphics/box_destroyable.png";
      break;
    case BOX_DESTROYABLE_BALL :
      image = "../graphics/box_destroyable.png";
      break;
    case BOX_DESTROYABLE_DUMMY_LAUNCHER :
      image = "../graphics/box_destroyable.png";
      break;
    case TARGET :
      image = "../graphics/target.png";
      break;
    case DOOR :
      image = "../graphics/door.png";
      break;
    case NPC1 :
      image = "../graphics/npc.png";
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
      editor->map[x][y] = malloc(sizeof(DynObj));
      editor->map[x][y]->type = EMPTY;
      editor->map[x][y]->x = x*32 + DEP_MAP_X;
      editor->map[x][y]->y = y*32 + DEP_MAP_Y;
      editor->map[x][y]->w = 32;
      editor->map[x][y]->h = 32;
      editor->map[x][y]->image = loadTexture("../graphics/grid.png", editor->screen->pRenderer);
    }
  }

  editor->nbBlocs = 9;
  editor->blocs = malloc(editor->nbBlocs*sizeof(DynObj*));
  for (int i=0; i<editor->nbBlocs; i++)
  {
    switch (i)
    {
      case 0 :
        editor->blocs[i] = initBlocEditor(editor, 0, 0, 32, 32,
                              GROUND);
        break;
      case 1 :
        editor->blocs[i] = initBlocEditor(editor, i*32, 0, 32, 32,
                              GROUND_2);
        break;
      case 2 :
        editor->blocs[i] = initBlocEditor(editor, i*32, 0, 64, 64,
                              BOX);
        break;
      case 3 :
        editor->blocs[i] = initBlocEditor(editor, i*32+32, 0, 64, 64,
                                BOX_DESTROYABLE_EMPTY);
        break;
      case 4 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                  0, 64, 64, BOX_DESTROYABLE_BALL);
        break;
      case 5 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                0, 64, 64, BOX_DESTROYABLE_DUMMY_LAUNCHER);
        break;
      case 6 :
        editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                0, 32, 32, TARGET);
        break;
      case 7 :
      editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                0, 32, 64, DOOR);
        break;
      case 8 :
      editor->blocs[i] = initBlocEditor(editor, editor->blocs[i-1]->x + editor->blocs[i-1]->w,
                0, 32, 32, NPC1);
        break;
    }
  }
  print(editor);
}

void print(Editor *editor)
{
  for (int i=0; i<editor->nbBlocs; i++)
  {
    printf("type:%d x:%d y:%d w:%d h:%d\n", editor->blocs[i]->type, editor->blocs[i]->x,
            editor->blocs[i]->y, editor->blocs[i]->w, editor->blocs[i]->h);
  }
}

void drawEditor(Editor *editor)
{
  clearScreen(editor->screen);
  drawMapEditor(editor);
  drawBlocsEditor(editor);
  drawImage(editor->blocs[6]->image, editor->input->xCursor, editor->input->yCursor, editor->screen->pRenderer);


  SDL_RenderPresent(editor->screen->pRenderer);
}

void drawMapEditor(Editor *editor)
{
  for (int x=0; x<editor->wmap; x++)
  {
    for (int y=0; y<editor->hmap; y++)
    {
        drawImage(editor->map[x][y]->image, x*32 + DEP_MAP_X, y*32 + DEP_MAP_Y,
                    editor->screen->pRenderer);
    }
  }
}

void drawBlocsEditor(Editor *editor)
{
  for (int i=0; i<editor->nbBlocs; i++)
  {

    drawImage(editor->blocs[i]->image, editor->blocs[i]->x, editor->blocs[i]->y,
              editor->screen->pRenderer);
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

  if (editor->input->mouse[SDL_BUTTON_LEFT])
  {
    collisionBlocEditor(editor);
    placeBloc(editor);
    editor->input->mouse[SDL_BUTTON_LEFT] = false;
  }

  if (editor->input->mouse[SDL_BUTTON_RIGHT])
  {
    editor->input->mouse[SDL_BUTTON_RIGHT] = false;
  }
}

bool collisionBlocEditor(Editor *editor)
{
  for (int i=0; i<editor->nbBlocs; i++)
  {
    if (collision(editor->input->xCursor, editor->input->yCursor, 0, 0,
              editor->blocs[i]->x, editor->blocs[i]->y, editor->blocs[i]->w,
                                editor->blocs[i]->h))
    {
      editor->typeAct = editor->blocs[i]->type;
      printf("%d\n", editor->typeAct);
      return true;
    }
  }
  return false;
}

void  placeBloc(Editor *editor)
{
  for (int x=0; x<editor->wmap; x++)
  {
    for (int y=0; y<editor->hmap; y++)
    {
      if (collision(editor->input->xCursor, editor->input->yCursor, 0, 0,
                editor->map[x][y]->x, editor->map[x][y]->y, editor->map[x][y]->w,
                                  editor->map[x][y]->h))
      {
        freeDynObj(editor->map[x][y]);
        editor->map[x][y] = initBlocEditor(editor, 0, 0, 32, 32,
                              editor->typeAct);
        puts("coucou");
      }
    }
  }
}


int main(int argc, char *argv[])
{
  Editor *editor = loadEditor();

  while (!editor->input->quit)//boucle principale
  {
    inputsEditor(editor);
    drawEditor(editor);

  }

  quitSDL(editor->screen);//on supprime tous les renderers et on quitte SDL

  return EXIT_SUCCESS;
}
