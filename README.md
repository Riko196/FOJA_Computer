# foja_computer

The application for computing some problems in formal languages and automata

1.  Install Node.js (https://nodejs.org/en/).
2.  Install [yarn](https://yarnpkg.com).

Starting frontend:

Frontend runs in React and uses yarn package manager.

For starting frontend go to `foja_computer/src` folder and type these commands:

1.  `yarn` - for installing and linking dependencies.
2.  `yarn start` - for starting frontend.

Starting server:

FOJA (formal languages and automata) algorithms run in C++, so we need to have the server
for communication betwen React and C++, it ensures nodejs server. For starting nodejs server
follow these steps.

1. Go to `foja_computer/server/algorithms_c++` and type `node-gyp configure build` - for compiling C++ program (Only if you have changed the C++ source code or if you are starting it first time), if you dont have node-gyp, install it.
2. Go to `foja_computer/server` and type `node server.js` - for starting the server.
