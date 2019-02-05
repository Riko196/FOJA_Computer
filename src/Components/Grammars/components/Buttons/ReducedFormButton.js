import React, { Component } from "react";
import { grammarToString, stringToGrammar } from "../Utils/GrammarParser";
import { callBackendAPI } from "../Utils/Requests";

class ReducedFormButton extends Component {
  execute = () => {
    const grammarString = grammarToString(this.props.grammar);
    callBackendAPI(grammarString, "reducedNormalForm").then(res => {
      console.log(res);
      this.props.setGrammar(stringToGrammar(res));
    });
  };

  render() {
    return (
      <input
        type="button"
        onClick={this.execute}
        value={"Reduced Normal Form"}
      />
    );
  }
}

export default ReducedFormButton;
