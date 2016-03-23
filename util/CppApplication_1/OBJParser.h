#include <stdio.h>

enum eObjEntryType{
    eVertex,
    eNormal,
    eFace,
    eGroupName,
    eSmoothGroup,
    eUnknown
};


class OBJParser{
public:
    OBJParser();
    ~OBJParser();
private:
};
