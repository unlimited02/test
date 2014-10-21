#ifndef __GitTutorial__SaveSQL__
#define __GitTutorial__SaveSQL__

#include "cocos2d.h"
#include "sqlite3.h"
#include <random>

class SaveSQL : public cocos2d::Node
{
public:
    virtual  bool init();

    static int sqliteOpen(sqlite3 **db);
    static const char* sqliteGetValueForKey(int textRoot, const char *name ,int random);
};

#endif /* defined(__GitTutorial__SaveSQL__) */
