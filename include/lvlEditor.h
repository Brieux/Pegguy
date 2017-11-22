#ifndef DEF_LVL_EDITOR
#define DEF_LVL_EDITOR

#include "defs.h"

#define DEP_MAP_X 0
#define DEP_MAP_Y 96

void print(Editor *editor);
Editor *loadEditor();
void loadEmptyMap(Editor *editor);
void drawEditor(Editor *editor);
void drawMapEditor(Editor *editor);
void drawBlocsEditor(Editor *editor);
DynObj *initBlocEditor(Editor *editor, int x, int y, int w, int h, int type);
bool collisionBlocEditor(Editor *editor);
void  placeBloc(Editor *editor);
void inputsEditor(Editor *editor);
void updateInputsEditor(Editor *editor);

#endif
