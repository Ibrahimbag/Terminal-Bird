#ifndef DB_H
#define DB_H

typedef struct {
    char *name;
    int score;
} leaderboards;

#define CREATE 0
#define INSERT 1
#define SELECT 2

leaderboards *db_execute(int operation_type, char *name, int score);
void free_leaderboard(leaderboards *leaderboard);

#endif
