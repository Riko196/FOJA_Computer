import React, { Component } from "react";
import InputGrammar from "./components/InputGrammar";
import Legend from "./components/Legend";
import GrammarWriter from "./components/GrammarWriter";
import { mapDispatchToProps } from "../Actions/rootReducer";
import { connect } from "react-redux";
import EquivalentButton from "./components/Buttons/EquivalentButton";

import "./GrammarPage.css";

class GrammarPage extends Component {
  constructor(props) {
    super(props);
    this.props.setGrammar1(null);
    this.props.setGrammar2(null);
    this.props.setEquivalence(null);
  }

  render() {
    return (
      <div className="grammar">
        <h1>Grammar Computer</h1>
        <div className="grammar-sidebar">
          <h3>Grammar 1:</h3>
          <InputGrammar
            grammar={this.props.grammar1}
            setGrammar={this.props.setGrammar1}
          />
          <GrammarWriter grammar={this.props.grammar1} />
          <h3>Grammar 2</h3>
          <InputGrammar
            grammar={this.props.grammar2}
            setGrammar={this.props.setGrammar2}
          />
          <GrammarWriter grammar={this.props.grammar2} />
          <Legend />
          {this.props.grammar1 != null &&
            this.props.grammar2 != null && (
              <EquivalentButton
                grammar1={this.props.grammar1}
                grammar2={this.props.grammar2}
                setGrammar1={this.props.setGrammar1}
                setGrammar2={this.props.setGrammar2}
                setEquivalence={this.props.setEquivalence}
              />
            )}
          {this.props.equivalence === true && (
            <p>Grammars are probably equivalent</p>
          )}
          {this.props.equivalence === false && (
            <p>Grammars are not equivalent</p>
          )}
        </div>
      </div>
    );
  }
}

export default connect(
  state => ({
    grammar1: state.grammar1,
    grammar2: state.grammar2,
    equivalence: state.equivalence
  }),
  mapDispatchToProps
)(GrammarPage);
