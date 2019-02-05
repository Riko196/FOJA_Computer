# foja_computer

The application for computing some problems in formal languages and automata

1.  Install Node.js (https://nodejs.org/en/).
2.  Install [yarn](https://yarnpkg.com).

Starting frontend:

Frontend runs in React and uses yarn package manager.

For starting frontend go to `foja_computer/src` folder and type these commands:
`yarn` - for installing and linking dependencies.
`yarn start` - for starting frontend.

Starting server:

FOJA (formal languages and automata) algorithms run in C++, so we need to have the server
for communication betwen React and C++, it ensures nodejs server. For starting nodejs server
go to `foja_computer/Server` folder and type these commands for start server:

1. `node-gyp configure build` - for compiling C++ program (Only if you have changed the C++ source code).
   (If you dont have node-gyp, install it).
2. `node server.js` - for starting the server.
