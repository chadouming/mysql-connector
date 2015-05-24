The MySQL Connector/Arduino
---------------------------
Congratulations! You have just entered a new paradigm of Arduino project. With
this connector, you can connect your Arduino project directly to a MySQL server
without using an intermediate computer or a web-based service. Having direct
access to a database server means you can store data acquired from your project
as well as check values stored in tables on the server.

If you have used some of the other methods of storing data from an Arduino such
as writing data to flash memory (e.g. a secure digital card) or an EEPROM
device, you can eliminate the manual data extraction method altogether.

Similarly, if your project is such that you cannot or do not want to connect to
the internet to save your data, the ability to write to a local database server
solves that problem as well.

Saving your data in a database will not only preserve the data
for analysis at a later time, it also means your project can feed data to more
complex applications that make use of the data.

Better still, if you have projects that use large data values for calculations
or lookups, you can store the data on the server and retrieve only the data
you need for the calculation or operation. This opens a whole new avenue of
Arduino projects!

Perhaps the most attractive point (at least for OSS developers) is that MySQL
is open source software. Which means you can download and install it where ever
you like and use it for any of your projects. Indeed, a single instance of
MySQL will support many, many Arduino projects.

Now that I've convinced you to give it a try, let's take a high-level look at
what a typical MySQL-based Arduino project looks like.


Designing with MySQL Connector/Arduino
--------------------------------------
The first thing you should know about the Connector/Arduino is it isn't a small
library. Depending on your choice of Arduino, this could consume half of your
program memory. For most projects that isn't an issue. If it is, take a look
at the Getting Started section for a way you can save some program space by
modifying the SHA1 library.

Likewise, the Connector/Arduino can consume a lot of memory for variables. This
is primarily for its communication buffer. While it uses dynamic memory to keep
use to a minimum, how much memory is used depends on how you use the connector.
If you are issuing simple data insertion commands (INSERT INTO), an easy way to
calculate this is the Connector/Arduino uses a bit more than the maximum the
size of the longest query string. If you are querying the server for data, the
Connector/Arduino uses a bit more than the cumulative size of a row of data
returned.

As you can imagine, there are some limitations.

- Queries must fit into memory. This is because the class uses an internal
  buffer for building data packets to send to the server. It is suggested long
  strings be stored in program memory using PROGMEM (see cmd_query_P).
- Result sets are read one row-at-a-time.
- The combined length of a row in a result set must fit into memory. The
  connector reads one packet-at-a-time and since the Arduino has a limited data
  size, the combined length of all fields must be less than available memory.
- Server error responses are processed immediately with the error code and text
  written via Serial.print.

Documentation
-------------
The documentation for the connector library is a work in progress. In the
meantime, I have written a couple of blogs about the connector that explain
how to use it. Please refer to the blogs until such time there is sufficient
documentation available.

Dependencies
------------------------

include <ESP8266WiFi.h>
include <Hash.h>
include <mysql.h>
