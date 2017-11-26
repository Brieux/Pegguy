#ifndef DEF_LVL_EDITOR
#define DEF_LVL_EDITOR

#include "defs.h"

#define DEP_MAP_X 0
#define DEP_MAP_Y 96

void print(Editor *editor);
Editor *loadEditor(int map_selected);
void loadEmptyMap(Editor *editor);
bool searchLevelEditor(FILE *file, int level);
void loadFontEditor(Editor *editor);
void loadMapEditor(Editor *editor, FILE *file);
void loadBlocsEditor(Editor *editor);
void drawEditor(Editor *editor);
void printLineEditor(Editor *editor, int x, int y, char *text);
void drawBlocCursor(Editor *editor);
void drawInfosEditor(Editor *editor);
void drawMapEditor(Editor *editor);
void drawGrid(Editor *editor);
void drawBlocsEditor(Editor *editor);
DynObj *initBlocEditor(Editor *editor, int x, int y, int type);
DynObj *collisionBlocEditor(Editor *editor, int x, int y, int w, int h);
void linker(Editor *editor);
void placeBloc(Editor *editor);
void resizeGrid(Editor *editor, int direction);
void inputsEditor(Editor *editor);
void deleteBlocsAround(Editor *editor, DynObj *bloc);
void deleteBloc(Editor *editor);
void updateInputsEditor(Editor *editor);
void saveMap(Editor *editor);
void scrollEditor(Editor *editor, int direction);
void nbDynObjDecrease(Editor *editor, int type);

#endif
