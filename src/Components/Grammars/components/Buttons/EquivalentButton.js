import React, { Component } from "react";
import { grammarToString } from "../Utils/GrammarParser";
import { callBackendAPIEquivalence } from "../Utils/Requests";

class EquivalentButton extends Component {
  execute = () => {
    const grammarString1 = grammarToString(this.props.grammar1);
    const grammarString2 = grammarToString(this.props.grammar2);
    callBackendAPIEquivalence(
      grammarString1,
      grammarString2,
      "equivalence"
    ).then(res => {
      if (res === "true") {
        this.props.setEquivalence(true);
      } else {
        this.props.setEquivalence(false);
      }
    });
  };

  render() {
    return <input type="button" onClick={this.execute} value={"Equivalence"} />;
  }
}

export default EquivalentButton;
