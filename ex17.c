#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

// addresses have set length for name and email to make them uniform in the db
struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

// database has a certain amount of rows allocated for same reason
struct Database {
	struct Address rows[MAX_ROWS];
};

// We are going to write and read from a file for each database
struct Connection {
	FILE *file;
	struct Database *db;		
};

void die(const char *message)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

// We take an address, and we use our -> to get fields out of our struct and print
void address_print(struct Address *addr)
{
	printf("%d, %s, %s\n", addr->id, addr->name, addr->email);
}

void database_load(struct Connection *conn)
{
	/* fread: we are loading ONE item of size: size of database struct, from our
       connection's file name, and we are storing it in our connection's db
       field. */
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);

	// If our pointer is NULL, we failed to load the database
	if(rc != 1) die("Failed to load database."); 
}

/* const char *f: this means that we have a changable pointer to a constant
   string. I believe this means that the filename cannot change, although we could
   decide to change the address of the filename variable to something else. */
struct Connection *database_open(const char *filename, char mode) 
{
	/* We allocate enough space for a new HEAP, since it is a pointer and not 
	   called without malloc, so that we can update its fields with the arguments 
    */
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn) die("Memory error"); // die if our pointer to new conn failed 

	if(mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");

		if(conn->file) {
			database_load(conn);
		}
	}

	if(!conn->file) die("Failed to open the file");
	
	return conn;
}


void database_close(struct Connection *conn)
{
	// if the connection exists
	if(conn) {
		// if the connection has a pointer to a file, then close that file
		if(conn->file) fclose(conn->file);

		// if the connection has a db in memory, remove that capture of the db
		if(conn->db) free(conn->db);

		// and then remove the db from the heap entirely
		free(conn);
	}
}

void database_write(struct Connection *conn)
{
	// make sure the file is at its beginning
	rewind(conn->file);
	
	/* similar to read above, if there is any awaiting changes in the db, i.e.
	   the conn->db, then we want to open the file to write one database-sized
       thingy, and place the changes in the conn file stream to be flushed */
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1) die("Failed to write database.");

	/* Flush pushes all the of the elements in the output buffer of the stream,
       here connection's file, to be written to the file. If the resulting int
       is negative one, then the flush has failed */
	rc = fflush(conn->file);
	if(rc == -1) die("Cannot flush database.");
}

void database_create(struct Connection *conn)
{
	int i = 0;

	for(i = 0; i < MAX_ROWS; i++) {
		// make a prototype to initialize the database
		struct Address addr = {.id = i, .set = 0};
		// then assign it to conn
		conn->db->rows[i] = addr;
	}
	printf("got to bottom of database create");
}

void database_set(struct Connection *conn, int id, const char *name,
                  const char *email)
{
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("Already set, delete it first");

	addr->set = 1;
	// WARNING FIX THIS
	char *res = strncpy(addr->name, name, MAX_DATA);
	// demonstrate that strncpy bug
	if(!res) die("Name copy failed");

	res = strncpy(addr->email, email, MAX_DATA);
	if(!res) die("Email copy failed");
}

void database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];
	
	if(addr->set) {
		address_print(addr);
	} else {
		die("ID is not set");
	}
}

void database_delete(struct Connection *conn, int id)
{
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;

	for(i = 0; i < MAX_ROWS; i++) {
		struct Address *cur = &db->rows[i];

		if(cur->set) {
			address_print(cur);
		}
	}
}


int main(int argc, char *argv[])
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if(argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("There's not that many records.");

    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}

