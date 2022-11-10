#ifndef DATADECODER_H
#define DATADECODER_H
#include <vector>
#include <datamanager.h>

class dataDecoder
{    
private:
    int size;
    int bufferIndex;
    void parseThrusterPod();
    std::string findNextItem();
    DataManager * dataManager;
    char * buffer;

public:
    dataDecoder();
    ~dataDecoder();
    void updateBuffer(char * newBuffer, int size);
    void parseData();
};

#endif // DATADECODER_H
