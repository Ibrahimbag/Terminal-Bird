#ifndef DB_H
#define DB_H

typedef struct {
	char *name;
	int score;
} leaderboards;

enum sql_statements { CREATE, INSERT, SELECT };

leaderboards *db_execute(int operation_type, char *name, int score);
void free_leaderboard(leaderboards *leaderboard);

#endif
