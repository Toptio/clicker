#include <raylib.h>
#include <stdlib.h>
#include "cookie.hpp"
#include "upgrades.hpp"

#define STORAGE_DATA_FILE "save.data"

typedef enum {
    STORAGE_POSITION_SCORE = 0,
    STORAGE_POSITION_COOKIES_PER_CLICK = 1,
    STORAGE_POSITION_COOKIES_PER_SECOND = 2,
    STORAGE_POSITION_REQUIRED_COOKIES = 3,
    STORAGE_POSITION_WIN_COUNT = 4,
    STORAGE_POSITION_CURRENT_LEVEL = 5
} StorageData;

static bool SaveStorageValue(unsigned int position, int value);
static int LoadStorageValue(unsigned int position);

bool SaveStorageValue(unsigned int position, int value) {
    bool success = false;
    int dataSize = 0;
    unsigned int newDataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);
    unsigned char *newFileData = NULL;

    if (fileData != NULL) {
        if (dataSize <= static_cast<int>(position * sizeof(int))) {
            newDataSize = (position + 1) * sizeof(int);
            newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);

            if (newFileData != NULL) {
                int *dataPtr = (int *)newFileData;
                dataPtr[position] = value;
            } else {
                TraceLog(LOG_WARNING, "Failed to reallocate memory for file data", STORAGE_DATA_FILE, dataSize, position * sizeof(int));
                newFileData = fileData;
                newDataSize = dataSize;
            }
        } else {
            newFileData = fileData;
            newDataSize = dataSize;

            int *dataPtr = (int *)newFileData;
            dataPtr[position] = value;
        }
        success = SaveFileData(STORAGE_DATA_FILE, newFileData, newDataSize);
        RL_FREE(newFileData);

        TraceLog(LOG_INFO, "Saved data to file: %s, position: %d, value: %d", STORAGE_DATA_FILE, position, value);
    } else {
        TraceLog(LOG_WARNING, "Failed to load file data: %s", STORAGE_DATA_FILE);

        dataSize = (position + 1) * sizeof(int);
        fileData = (unsigned char *)RL_MALLOC(dataSize);
        int *dataPtr = (int *)fileData;
        dataPtr[position] = value;

        success = SaveFileData(STORAGE_DATA_FILE, fileData, dataSize);
        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "Saved data to file: %s, position: %d, value: %d", STORAGE_DATA_FILE, position, value);
    }

    return success;
}

int LoadStorageValue(unsigned int position) {
    int value = 0;
    int dataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);

    if (fileData != NULL) {
        if (dataSize < ((int)(position * 4))) TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
        else {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        UnloadFileData(fileData);

        TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
    }

    return value;
}

void saveGame(Cookie& cookie, Upgrades& upgrades) {
    if (cookie.GetCookieCount() == 0) {
        TraceLog(LOG_WARNING, "Cookie count is 0, cannot save game");
        return;
    }
   
    int winCount = upgrades.GetWinCount();
    if (winCount < 0) {
        winCount = 0;
    }

    SaveStorageValue(STORAGE_POSITION_SCORE, cookie.GetCookieCount());
    SaveStorageValue(STORAGE_POSITION_COOKIES_PER_CLICK, cookie.GetCookiePerClick());
    SaveStorageValue(STORAGE_POSITION_COOKIES_PER_SECOND, cookie.GetCookiePerSecond());
    SaveStorageValue(STORAGE_POSITION_REQUIRED_COOKIES, upgrades.GetRequiredCookies(0));
    SaveStorageValue(STORAGE_POSITION_WIN_COUNT, upgrades.GetWinCount());
    SaveStorageValue(STORAGE_POSITION_CURRENT_LEVEL, upgrades.GetCurrentLevel());

    TraceLog(LOG_INFO, "Saved cookie count: %d", cookie.GetCookieCount());
    TraceLog(LOG_INFO, "Saved cookie per click: %d", cookie.GetCookiePerClick());
    TraceLog(LOG_INFO, "Saved cookie per second: %d", cookie.GetCookiePerSecond());
    TraceLog(LOG_INFO, "Saved required cookies for upgrade");
    TraceLog(LOG_INFO, "Saved win count: %d", upgrades.GetWinCount());
    TraceLog(LOG_INFO, "Saved current level: %d", upgrades.GetCurrentLevel());
}   

void loadGame(Cookie& cookie, Upgrades& upgrades) {
    int loadedScore = LoadStorageValue(STORAGE_POSITION_SCORE);
    int loadedCookiePerClick = LoadStorageValue(STORAGE_POSITION_COOKIES_PER_CLICK);
    int loadedCookiePerSecond = LoadStorageValue(STORAGE_POSITION_COOKIES_PER_SECOND);
    int loadedRequiredCookies = LoadStorageValue(STORAGE_POSITION_REQUIRED_COOKIES);
    int loadedWinCount = LoadStorageValue(STORAGE_POSITION_WIN_COUNT);
    int loadedCurrentLevel = LoadStorageValue(STORAGE_POSITION_CURRENT_LEVEL);

    cookie.SetCookieCount(loadedScore);
    cookie.SetCookiePerClick(loadedCookiePerClick);
    cookie.SetCookiePerSecond(loadedCookiePerSecond);
    upgrades.SetRequiredCookies(0, loadedRequiredCookies);
    upgrades.SetWinCount(loadedWinCount);
    upgrades.SetCurrentLevel(loadedCurrentLevel);

    TraceLog(LOG_INFO, "Loaded cookie count: %d", loadedScore);
    TraceLog(LOG_INFO, "Loaded cookie per click: %d", loadedCookiePerClick);
    TraceLog(LOG_INFO, "Loaded cookie per second: %d", loadedCookiePerSecond);
    TraceLog(LOG_INFO, "Loaded required cookies for upgrade");
    TraceLog(LOG_INFO, "Loaded win count: %d", loadedWinCount);
    TraceLog(LOG_INFO, "Loaded current level: %d", loadedCurrentLevel);
}