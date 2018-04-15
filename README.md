![Whisperer logo](https://i.imgur.com/RZDdVNU.png)

# WhispererEngine - Backend for Whisperer

[![Build Status](http://74.208.200.101:8080/job/WhispererEngine/badge/icon)](http://74.208.200.101:8080/job/WhispererEngine/)

Whisperer is a digital collectible card game that focuses on deck building. We give players the freedom to create their own cards for games between friends. Are you an r/customhearthstone subscriber? Did you create custom cards for your favorite game as a kid? Whisperer is for you.
WhispererEngine is the backend server for the Whisperer game. It handles clients connecting, starting a game, and most importantly verifying valid moves. In the future this server will also support deck creation and editing.

## Important Notes
On windows make sure you have the boost env variables set (BOOST_ROOT, BOOST_LIBRARYDIR, BOOST_INCLUDEDIR) so CMake can find your boost installation

You will need to create a "dbconfig.json" file with contents similar to this, which is used to pull the connection string from
```
{
    "CONNECTION_INFO":"postgresql://74.208.200.101:5432/WhispererDev?user=reader"
}
```

## Dependencies

- [Postgres](https://www.enterprisedb.com/downloads/postgres-postgresql-downloads) (Or just apt-get the pg libs)
    - libpq, required for connecting to Postgres DB's
- [Boost](https://www.boost.org/) 1.65.1 or newer
    - asio, required for communicating with the client
    - ### Building for Windows
        - ```bootstrap.bat mingw``` or ```bootstrap.bat gcc``` (Depends on your boost version)
        - ```b2 link=static threading=multi --toolset=gcc --build-type=complete --with-system --with-thread stage``` in the download folder
- [cURL](https://curl.haxx.se/download.html)
    - libcurl, required for making API calls

## Supported compilers

- GCC 7.2.0 or newer
- MinGW/GCC 6.3.0 or newer

## About

This project was created by [Sam Privett](https://github.com/maspe36) for the University of Cincinnati's Information Technology Senior Design class of 2018. With significant contributions from [Connor Bowman](https://github.com/conbow) (User Interface) and Garry Le (Server admin on the VPS).
