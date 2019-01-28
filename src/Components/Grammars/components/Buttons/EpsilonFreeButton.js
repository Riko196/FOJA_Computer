import React, { Component } from "react";
import { grammarToString, stringToGrammar } from "../Utils/GrammarParser";
import { callBackendAPI } from "../Utils/Requests";

class EpsilonFreeButton extends Component {
  execute = () => {
    const grammarString = grammarToString(this.props.grammar);
    callBackendAPI(grammarString, "epsilonFreeForm").then(res => {
      this.props.setGrammar(stringToGrammar(res));
    });
  };

  render() {
    return (
      <input type="button" onClick={this.execute} value={"Epsilon Free Form"} />
    );
  }
}

export default EpsilonFreeButton;
