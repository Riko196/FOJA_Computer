const express = require("express");
const app = express();
const cecko = require("./build/Release/server");
const port = 8080;
const cors = require("cors");

/*app.use(cors());
app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header(
    "Access-Control-Allow-Headers",
    "Origin, X-Requested-With, Content-Type, Accept"
  );
  next();
});*/

// create a GET route
app.get("/express_backend", (req, res) => {
  res.send(cecko.hello());
});

// console.log that your server is up and running
app.listen(port, () => console.log(`Listening on port ${port}`));
