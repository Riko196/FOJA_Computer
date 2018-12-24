import React, { Component } from "react";
import { Route } from "react-router-dom";
import { Switch } from "react-router";
import MainPage from "./Components/MainPage/MainPage";
import GrammarPage from "./Components/Grammars/GrammarPage";
import Navigation from "./Navigation";

import "./App.css";
class App extends Component {
  render() {
    return (
      <div className="application-container">
        <Route path="/:something" component={Navigation} />
        <Route exact path="/" component={MainPage} />
        <Switch>
          <Route path="/grammarpage" component={GrammarPage} />
        </Switch>
      </div>
    );
  }
}

export default App;
