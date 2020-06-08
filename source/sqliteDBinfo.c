/* SQLiteDBinfo
   expend SQLite database Info
    
   Copyright (C) 2018  Frank Sommer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
   
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define VERSION	"0.5.1"

void database_info();						/* forward declaration        */

/* print data to standard output  */
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char *argv[])
{
	int id;
	sqlite3 *db_handler;
	
	 if (argc == 1 ||!strcmp(argv[1], "--help")) { 						/* without databasefile name */
		printf(" \n");
		printf("Usage: %s:", argv[0]);
		printf(" sqlite-FILE \n");
		printf(" \n");
		printf("Information about the structure\n");
		printf("of a SQLite Database \n");
		printf("Version %s\n", VERSION);
		printf(" \n");
		printf("SQLiteDBinfo  Copyright (C) 2018  Frank Sommer\n");
		printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
		printf("This is free software, and you are welcome to redistribute it\n");
		printf("under certain conditions.\n");			
	}
	else {		
	   id = sqlite3_open_v2(argv[1], &db_handler, SQLITE_OPEN_READONLY, NULL);
	    if(id == SQLITE_OK) {
	        database_info(db_handler);
	    }
	    else {     
	        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_handler));
	        return 1;
	    }
	   sqlite3_close(db_handler);
	   return 0;
	}
}

/* expend databaseInfo */
void database_info(sqlite3 *db)
{
	char *zErrMsg = 0;
	int rc;
	
	rc = sqlite3_exec(db, "SELECT * FROM sqlite_master", callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
    }	
}
