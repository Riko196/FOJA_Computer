const express = require("express");
const app = express();
var cecko = require("./build/Release/server");
const port = 8080;
const cors = require("cors");

app.use(cors());
app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header(
    "Access-Control-Allow-Headers",
    "Origin, X-Requested-With, Content-Type, Accept"
  );
  next();
});

// create a GET route
app.get("/grammarRequest/:grammar/reducedNormalForm", (req, res) => {
  const { grammar } = req.params;
  res.send(cecko.execute(grammar, "reducedNormalForm"));
});

app.get("/grammarRequest/:grammar/epsilonFreeForm", (req, res) => {
  const { grammar } = req.params;
  res.send(cecko.execute(grammar, "epsilonFreeForm"));
});

app.get("/grammarRequest/:grammar1/:grammar2/equivalence", (req, res) => {
  const { grammar1 } = req.params;
  const { grammar2 } = req.params;

  res.send(cecko.execute(grammar1, grammar2, "equivalence"));
});
// console.log that your server is up and running
app.listen(port, () => console.log(`Listening on port ${port}`));
