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
      this.props.setEquivalencyAnswer(res);
    });
  };

  render() {
    return (
      <input
        type="button"
        id="eq"
        onClick={this.execute}
        value={"Equivalence"}
      />
    );
  }
}

export default EquivalentButton;
