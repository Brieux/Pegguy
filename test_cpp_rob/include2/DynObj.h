#ifndef DYNOBJ_H
#define DYNOBJ_H

class DynObj : public Obj{
    private:
        bool gravite;
        int vSpeed;
        int hSpeed;
        DynObj *link;
        int x_Link;
        int y_Link;
        int count;
        bool linked;
        bool move;
    public:
        DynObj(int x, int y, int h, int w, int nb_Frames, float time_Frame, int deep_Image,\
            const char* img, int type, bool solid, bool active, Game *game,\
            bool gravite, int vSpeed, int hSpeed, int count, bool linked, bool move);
        ~DynObj();
        void move();
        void manageCount(int diff);
};

#endif
