/* https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm */
#define _POSIX_C_SOURCE 1
#include "leaderboard_db.h"
#include <limits.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) (void)(x)

static leaderboards *leaderboard = NULL;
static int count = 0;

static int callback(void *data, int argc, char **value, char **key) 
{
    UNUSED(data);
    UNUSED(key);

    // Copy data from database to leaderboard
    for (int i = 0; i < argc; i++) 
    {
        if (i == 0)
        {
            leaderboard[count].name = strdup(value[i]);
            if (leaderboard[count].name == NULL) 
            {
                return 1;
            }
        }
        else if (i == 1)
        {
            leaderboard[count].score = atoi(value[i]);
        }
    }
    count++;

    return 0;
}

leaderboards *db_execute(int operation_type, char *name, int score)
{
    sqlite3 *db = NULL;
    char *zErrMsg = 0, *sql = NULL;
    int rc;

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/.Terminal-Bird/leaderboards.db", getenv("HOME"));
    rc = sqlite3_open(path, &db);

    if (rc) 
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    switch (operation_type)
    {
        case CREATE:
            sql = "CREATE TABLE IF NOT EXISTS leaderboards("
            	  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name TEXT NOT NULL,"
                  "score INTEGER NOT NULL);";
            leaderboard = NULL;
            break;
        case INSERT:
            sql = sqlite3_mprintf("INSERT INTO leaderboards (name, score) VALUES ('%q', %d);", name, score);
            leaderboard = NULL;
            break;
        case SELECT:
            sql = "SELECT name, score FROM leaderboards ORDER BY score DESC LIMIT 30;";

            leaderboard = malloc(sizeof(leaderboards) * 30);
            if (leaderboard == NULL) 
            {
                return NULL;
            }

            for (int i = 0; i < 30; i++) 
            {
                leaderboard[i].name = NULL;
                leaderboard[i].score = 0;
            }
            break;
        default:
            break;
    }

    rc = sqlite3_exec(db, sql, &callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return NULL;
    }

    if (operation_type == INSERT)
    {
        sqlite3_free(sql);
    }
    sqlite3_close(db);
    count = 0;

    return leaderboard;
}

void free_leaderboard(leaderboards *leaderboard)
{
    if (leaderboard != NULL) 
    {
        for (int i = 0; i < 30; i++) 
        {
            if (leaderboard[i].name != NULL) 
            {
                free(leaderboard[i].name);
                leaderboard[i].name = NULL;
            }
        }
        free(leaderboard);
        leaderboard = NULL;
    }
}
