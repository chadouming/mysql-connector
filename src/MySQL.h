/* MySQL connector Library
 * Library for fast, secure and efficient query
 * to a MySQL server.
 *
 * Copyright (c) 2012, 2015 Oracle and/or its affiliates. All rights reserved.
 */
#ifndef mysql_h
#define mysql_h

#include "Arduino.h"
#include <ESP8266WiFi.h>

//#define WITH_SELECT  // Comment this for use without SELECT capability

//#define DEBUG   // Uncomment this for enabling debugging of messages

#define OK_PACKET     0x00
#define EOF_PACKET    0xfe
#define ERROR_PACKET  0xff
#define MAX_FIELDS    0x20   // Maximum number of fields. Reduce to save memory. Default=32
#define VERSION_STR   "1.0.4"

#ifdef WITH_SELECT

// Structure for retrieving a field (minimal implementation).
typedef struct {
  char *db;
  char *table;
  char *name;
} field_struct;

// Structure for storing result set metadata.
typedef struct {
  int num_fields;     // actual number of fields
  field_struct *fields[MAX_FIELDS];
} column_names;

// Structure for storing row data.
typedef struct {
  char *values[MAX_FIELDS];
} row_values;

#endif

/**
 * Connector class
 *
 * The connector class permits users to connect to and issue queries
 * against a MySQL database. It is a lightweight connector with the
 * following features.
 *
 *  - Connect and authenticate with a MySQL server (using 'new' 4.1+
 *    protocol).
 *  - Issue simple commands like INSERT, UPDATE, DELETE, SHOW, etc.
 *  - Run queries that return result sets.
 *
 *  There are some strict limitations:
 *
 *  - Queries must fit into memory. This is because the class uses an
 *    internal buffer for building data packets to send to the server.
 *    It is suggested long strings be stored in program memory using
 *    PROGMEM (see cmd_query_P).
 *  - Result sets are read one row-at-a-time.
 *  - The combined length of a row in a result set must fit into
 *    memory. The connector reads one packet-at-a-time and since the
 *    Arduino has a limited data size, the combined length of all fields
 *    must be less than available memory.
 *  - Server error responses are processed immediately with the error
 *    code and text written via Serial.print.
 */
class Connector
{
  public:
    Connector();
    bool mysql_connect(const char *server, uint16_t port, char *user, char *password);
	bool mysql_connect(IPAddress server, uint16_t port, char *user, char *password);
    void disconnect();
    bool cmd_query(const char *query);
	bool cmd_query_P(const char *query);
    int is_connected () { return client.connected(); }
    const char *version() { return VERSION_STR; }
#ifdef WITH_SELECT
    column_names *get_columns();
    row_values *get_next_row();
    void free_columns_buffer();
    void free_row_buffer();
    void show_results();
    bool clear_ok_packet();
#endif
  private:
    byte *buffer;
    char *server_version;
    byte seed[20];
    int packet_len;
#ifdef WITH_SELECT
    column_names columns;
    bool columns_read;
    int num_cols;
    row_values row;
#endif

    WiFiClient client;

    // Methods for handling packets
    int wait_for_client();
    void send_authentication_packet(char *user, char *password);
    void read_packet();
    void parse_handshake_packet();
    int check_ok_packet();
    void parse_error_packet();
    bool run_query(int query_len);

    // Utility methods
    bool scramble_password(char *password, byte *pwd_hash);
    int get_lcb_len(int offset);
    int read_int(int offset, int size=0);
    void store_int(byte *buff, long value, int size);
#ifdef WITH_SELECT
    char *read_string(int *offset);
    int get_field(field_struct *fs);
    int get_row();
    bool get_fields();
    bool get_row_values();
    column_names *query_result();
#endif

    // diagnostic methods
#ifdef WITH_DEBUG
    void print_packet();
#endif

    void print_message(const char *msg, bool EOL = false) {
      Serial.print(msg);
      if (EOL)
        Serial.println();
    }
};

#endif
