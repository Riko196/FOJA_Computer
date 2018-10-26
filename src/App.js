import React, { Component } from "react";
import { Route } from "react-router-dom";
import { Switch } from "react-router";
import MainPage from "./Components/MainPage/MainPage";
import "./App.css";

class App extends Component {
  render() {
    return (
      <div className="application-container">
        <Route exact path="/" component={MainPage} />
        <Switch />
      </div>
    );
  }
}

export default App;
