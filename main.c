#include <stdio.h>
#include <stdlib.h>
#include <include/mysql.h>

int main(int argc, char **argv) {
    MYSQL mysql_conn; /* Connection handle */
	MYSQL_RES *mysql_result = NULL;
	MYSQL_ROW mysql_row;
	int f1, f2, num_row, num_col;

    if (mysql_init(&mysql_conn) != NULL) {
        if (mysql_real_connect(&mysql_conn, "localhost", "root", "", "test", MYSQL_PORT, NULL, 0) != NULL) {  // connect to Database
            (void) printf("GOOD!\n");
			if (mysql_query(&mysql_conn, "SELECT * FROM test") == 0)  { // query data from Database
				mysql_result = mysql_store_result(&mysql_conn);  // get the result
			    num_row = mysql_num_rows(mysql_result); /* Get the no. of row */
                num_col = mysql_num_fields(mysql_result); /* Get the no. of column */
				printf("num_row: %d, num_col: %d\n", num_row, num_col);

				for (f1=0; f1<num_row; f1++) {
					mysql_row = mysql_fetch_row(mysql_result); // fetch result row by row
					for (f2=0; f2<num_col; f2++)
						printf("[Row %d, Col %d] ==> [%s]\n", f1, f2, mysql_row[f2]);  // print the results out
				}
			} else {
				(void) printf("Query fails\n");
			}
        } else {
            (void) printf("Connection fails.\n");
        }
    } else {
        (void) printf("Initialization fails.\n");
        return -1;
    }

	mysql_free_result(mysql_result); // free the result
    mysql_close(&mysql_conn);
    return 0;
}
