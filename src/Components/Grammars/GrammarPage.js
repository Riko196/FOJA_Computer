import React from "react";
import Graph from "react-graph-vis";
import InputGrammar from "./components/InputGrammar";
import Legend from "./components/Legend";

import "./GrammarPage.css";

const graph = {
  nodes: [{ id: 1, label: "adsads" }, { id: 2, label: "sdasdaddsadasdad" }],
  edges: [{ from: 1, to: 2 }]
};

const graphStyle = {
  width: "100%",
  height: "600px"
};

const GrammarPage = () => (
  <div className="grammar">
    <h1>Grammar Computer</h1>
    <div className="grammar-sidebar">
      <h3>Grammar 1:</h3>
      <InputGrammar />
      <h3>Grammar 2</h3>
      <InputGrammar />
      <Legend />
    </div>
    <div className="grammar-main">
      <Graph graph={graph} style={graphStyle} />
    </div>
  </div>
);

export default GrammarPage;
