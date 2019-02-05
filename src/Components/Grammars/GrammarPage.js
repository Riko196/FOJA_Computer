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
    this.props.setEquivalencyAnswer(null);
  }

  render() {
    return (
      <div className="grammar">
        <h1>Grammar Computer</h1>
        <div className="grammar-sidebar">
          <h2>Grammar 1:</h2>
          <InputGrammar
            grammar={this.props.grammar1}
            setGrammar={this.props.setGrammar1}
          />
          <GrammarWriter grammar={this.props.grammar1} />
        </div>
        <div className="grammar-sidebar2">
          <h2>Grammar 2:</h2>
          <InputGrammar
            grammar={this.props.grammar2}
            setGrammar={this.props.setGrammar2}
          />
          <GrammarWriter grammar={this.props.grammar2} />
        </div>
        <Legend />
        {this.props.grammar1 != null &&
          this.props.grammar2 != null && (
            <EquivalentButton
              grammar1={this.props.grammar1}
              grammar2={this.props.grammar2}
              setGrammar1={this.props.setGrammar1}
              setGrammar2={this.props.setGrammar2}
              setEquivalencyAnswer={this.props.setEquivalencyAnswer}
            />
          )}
        {this.props.equivalencyAnswer.equivalency === true && (
          <p className="eqP">
            Grammars are equivalent for all words with size{" "}
            {this.props.equivalencyAnswer.answer}
          </p>
        )}
        {this.props.equivalencyAnswer.equivalency === false && (
          <p className="eqP">
            Grammars are not equivalent, because of word{" "}
            {this.props.equivalencyAnswer.answer}
          </p>
        )}
      </div>
    );
  }
}

export default connect(
  state => ({
    grammar1: state.grammar1,
    grammar2: state.grammar2,
    equivalencyAnswer: state.equivalencyAnswer
  }),
  mapDispatchToProps
)(GrammarPage);
