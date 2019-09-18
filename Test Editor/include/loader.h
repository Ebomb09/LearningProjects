#ifndef LOADER_H
#define LOADER_H

    #include "classes.h"

    #include <fstream>

    namespace Map{

        bool LoadMap(const string& fname, vector<Object*>& Objects);
        bool SaveMap(string& fname, vector<Object*>& Objects);

    }

#endif