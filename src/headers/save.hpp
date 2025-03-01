#include <raylib.h>
#include <stdlib.h>

#define STORAGE_DATA_FILE "save.data"

typedef enum {
    STORAGE_POSITION_SCORE = 0,
} StorageData;

static bool SaveStorageValue(unsigned int position, int value);
static int LoadStorageValue(unsigned int position);


bool SaveStorageValue(unsigned int position, int value) {
    bool success = false;
    int dataSize = 0;
    unsigned int newDataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);
    unsigned char *newFileData = NULL;

    if(fileData != NULL){
        if(dataSize <= static_cast<int>(position*sizeof(int))) {
            newDataSize = (position + 1) * sizeof(int);
            newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);

            if(newFileData != NULL) {
                int *dataPtr = (int *)newFileData;
                dataPtr[position] = value;
            } 
            else {
                TraceLog(LOG_WARNING, "Failed to reallocate memory for file data", STORAGE_DATA_FILE, dataSize, position*sizeof(int));
                newFileData = fileData;
                newDataSize = dataSize;
            }
            
        } 
        else {
            newFileData = fileData;
            newDataSize = dataSize;

            int *dataPtr = (int *)newFileData;
            dataPtr[position] = value;
        }
            success = SaveFileData(STORAGE_DATA_FILE, newFileData, newDataSize);
            RL_FREE(newFileData);

            TraceLog(LOG_INFO, "Saved data to file", STORAGE_DATA_FILE, position, value);
            TraceLog(LOG_INFO, "Saved cookie count: %d", value);
        }
        else {
            TraceLog(LOG_WARNING, "Failed to load file data", STORAGE_DATA_FILE);

            dataSize = (position + 1) * sizeof(int);
            fileData = (unsigned char *)RL_MALLOC(dataSize);
            int *dataPtr = (int *)fileData;
            dataPtr[position] = value;

            success = SaveFileData(STORAGE_DATA_FILE, fileData, dataSize);
            UnloadFileData(fileData);

            TraceLog(LOG_INFO, "Saved data to file", STORAGE_DATA_FILE, position, value);
            TraceLog(LOG_INFO, "Saved cookie count: %d", value);
        }

        return success;
}

int LoadStorageValue(unsigned int position)
{
    int value = 0;
    int dataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);

    if (fileData != NULL)
    {
        if (dataSize < ((int)(position*4))) TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
        else
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
    }

    return value;
}