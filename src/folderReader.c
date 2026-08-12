#include "../include/FolderReader.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

#define GAME_WIDTH 800
#define GAME_HEIGHT 600


/*
 * Recursively search a directory for a folder named "fights".
 *
 * When found:
 *
 *     result = path containing the fights folder
 *
 * Example:
 *
 *     /media/scratchsniff314/UBUNTU 26_01
 *
 * if this exists:
 *
 *     /media/scratchsniff314/UBUNTU 26_01/fights
 */
static int findFightsFolder(const char *basePath, char *result, size_t resultSize)
{
    DIR *dir = opendir(basePath);

    if (dir == NULL)
        return 0;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char fullPath[PATH_MAX];

        int written = snprintf(
            fullPath,
            sizeof(fullPath),
            "%s/%s",
            basePath,
            entry->d_name
        );

        if (written < 0 || written >= (int)sizeof(fullPath))
            continue;

        struct stat info;

        if (stat(fullPath, &info) != 0)
            continue;

        if (!S_ISDIR(info.st_mode))
            continue;

        /*
         * We found the fights directory.
         *
         * Return the directory containing it.
         */
        if (strcmp(entry->d_name, "fights") == 0)
        {
            strncpy(result, basePath, resultSize - 1);
            result[resultSize - 1] = '\0';

            closedir(dir);
            return 1;
        }

        /*
         * Search inside this directory.
         */
        if (findFightsFolder(fullPath, result, resultSize))
        {
            closedir(dir);
            return 1;
        }
    }

    closedir(dir);
    return 0;
}


/*
 * Find the USB/game directory.
 *
 * Searches:
 *
 * /media
 * /media/user
 * /media/user/USB
 * /media/user/USB/...
 *
 * until it finds:
 *
 * /some/path/fights
 */
char *findUSB(char *path)
{
    if (path == NULL)
        return NULL;

    path[0] = '\0';

    if (findFightsFolder("/media", path, PATH_MAX))
    {
        printf("Found game directory:\n%s\n", path);
        return path;
    }

    printf("Could not find fights folder in /media\n");

    return NULL;
}


/*
 * Read all files inside:
 *
 *     path/fights
 */
struct fileList readFightFiles(char *path)
{
    struct fileList list = {0};

    /*
     * Your original code starts the list at 1,
     * so keep that behavior.
     */
    list.count = 1;

    /*
     * Find the actual USB/game directory.
     */
    if (findUSB(path) == NULL)
    {
        puts("Game directory not found");
        return list;
    }

    char fight[PATH_MAX];

    int written = snprintf(
        fight,
        sizeof(fight),
        "%s/fights",
        path
    );

    if (written < 0 || written >= (int)sizeof(fight))
    {
        puts("Fight path is too long");
        return list;
    }

    printf("Opening fights folder:\n%s\n", fight);

    DIR *folder = opendir(fight);

    if (folder == NULL)
    {
        perror("opendir fights");
        return list;
    }

    struct dirent *entry;

    while ((entry = readdir(folder)) != NULL)
    {
        /*
         * Ignore . and ..
         */
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        /*
         * Don't go past the size of fileName.
         */
        if (list.count >= MAX_FILES)
            break;

        strncpy(
            list.fileName[list.count],
            entry->d_name,
            sizeof(list.fileName[list.count]) - 1
        );

        list.fileName[list.count]
            [sizeof(list.fileName[list.count]) - 1] = '\0';

        list.count++;
    }

    closedir(folder);


    /*
     * Calculate positions.
     */
    for (int i = 1; i < list.count; i++)
    {
        if (i <= 25)
        {
            list.colPos[i] =
                GAME_HEIGHT * i / 25;

            list.rowPos[i] = 50;
        }
        else
        {
            list.rowPos[i] =
                GAME_HEIGHT * (i % 25) / 25;

            list.colPos[i] =
                320 * (i / 25);
        }
    }

    return list;
}


/*
 * Draw the file list.
 */
void drawFileList(struct fileList *list)
{
    if (list == NULL)
        return;

    for (int i = 1; i < list->count; i++)
    {
        DrawText(
            list->fileName[i],
            list->rowPos[i],
            list->colPos[i],
            25,
            WHITE
        );
    }
}


/*
 * Optional debugging function.
 *
 * IMPORTANT:
 * This function does NOT modify path anymore.
 */
char *list_directory(char *path)
{
    if (path == NULL)
        return NULL;

    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        perror("opendir");
        return NULL;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char fullPath[PATH_MAX];

        snprintf(
            fullPath,
            sizeof(fullPath),
            "%s/%s",
            path,
            entry->d_name
        );

        printf("%s\n", fullPath);
    }

    closedir(dir);

    return path;
}
