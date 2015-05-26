Copyright (c) 2012, 2015 Oracle and/or its affiliates. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA

Version 1.0.0a Created by Dr. Charles A. Bell, April 2012.
Version 1.0.0b Updated by Dr. Charles A. Bell, October 2013.
Version 1.0.1b Updated by Dr. Charles A. Bell, February 2014.
Version 1.0.2b Updated by Dr. Charles A. Bell, April 2014.
Version 1.0.3rc Updated by Dr. Charles A. Bell, March 2015.
Version 1.0.4 Updated by Chad Cormier Roussel, May 2015.

The MySQL Connector
-------------------------------
Congratulations! You have just entered a new paradigm of Arduino project. With
this connector, you can connect your Arduino project directly to a MySQL server
without using an intermediate computer or a web-based service. Having direct
access to a database server means you can store data acquired from your project
as well as check values stored in tables on the server.

This library can store data and retrieve it in a fast, efficient and secure way

Designing with MySQL Connector
--------------------------------
The first thing you should know about the Connector/Arduino is it isn't a small
library. Depending on your choice of Arduino, this could consume half of your
program memory. For most projects that isn't an issue.

Likewise, the Connector can consume a lot of memory for variables. This
is primarily for its communication buffer. While it uses dynamic memory to keep
use to a minimum, how much memory is used depends on how you use the connector.
If you are issuing simple data insertion commands (INSERT INTO), an easy way to
calculate this is the Connector/Arduino uses a bit more than the maximum the
size of the longest query string. If you are querying the server for data, the
Connector/Arduino uses a bit more than the cumulative size of a row of data
returned.

As you can imagine, there are some limitations.

- Queries must fit into memory. This is because the class uses an internal
  buffer for building data packets to send to the server.
- Result sets are read one row-at-a-time.
- The combined length of a row in a result set must fit into memory. The
  connector reads one packet-at-a-time and since the Arduino has a limited data
  size, the combined length of all fields must be less than available memory.
- Server error responses are processed immediately with the error code and text
  written via Serial.print.

Documentation
--------------------------------
The documentation for the connector library is a work in progress. In the
meantime, I have written a couple of blogs about the connector that explain
how to use it. Please refer to the blogs until such time there is sufficient
documentation available.

Dependencies
--------------------------------
<ESP8266WiFi.h>
<Hash.h>
<mysql.h>