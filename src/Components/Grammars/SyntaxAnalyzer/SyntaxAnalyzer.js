import React, { Component } from "react";
import Legend from "../components/Legend";
import RelationPrinter from "./RelationPrinter";
import SyntaxAnimation from "./SyntaxAnimation";
import InputSyntaxAnalyzer from "./InputSyntaxAnalyzer";
import { grammarToString } from "../components/Utils/GrammarParser";
import { connect } from "react-redux";
import { epsilon } from "../components/Utils/Constants";
import { getWordSyntaxAnalyzation } from "../../Actions/actions";

import "./SyntaxAnalyzer.css";

class SyntaxAnalyzer extends Component {
  constructor(props) {
    super(props);
    this.wordForAnalyzation = React.createRef();
  }

  nonsenseWord = word => {
    for (let i = 0; i < word.length; i += 1) {
      if (
        this.props.grammarForAnalyzation.grammar.terminalsSet.includes(
          word[i]
        ) === false
      )
        return true;
    }
    return false;
  };

  analyzeWord = () => {
    const word = this.wordForAnalyzation.current.value;
    if (this.nonsenseWord(word) === true || word === epsilon) return;

    this.props.getWordSyntaxAnalyzation(
      grammarToString(this.props.grammarForAnalyzation.grammar),
      word
    );
  };

  render() {
    return (
      <div className="syntax-analyzer">
        <h1>Syntax Analyzer</h1>
        <div className="syntax-analyzer-sidebar">
          <InputSyntaxAnalyzer />
          {this.props.precedentialRelation !== null && <RelationPrinter />}
          {this.props.grammarForAnalyzation !== null &&
            this.props.grammarForAnalyzation.isPrecedential === true && (
              <div className="analyzation-word">
                <h1>Word for analyzation:</h1>
                <input
                  type="text"
                  className="word-for-analyzation"
                  ref={this.wordForAnalyzation}
                />
                <input
                  type="button"
                  onClick={this.analyzeWord}
                  value={"Analyze word"}
                />
              </div>
            )}
          {this.props.grammarForAnalyzation !== null &&
            this.props.grammarForAnalyzation.isPrecedential !== true && (
              <p>Grammar is not simple precedential.</p>
            )}
          {this.props.analyzationOfWord !== null && <SyntaxAnimation />}
        </div>

        <Legend />
      </div>
    );
  }
}

export default connect(
  state => ({
    grammarForAnalyzation: state.grammarForAnalyzation,
    precedentialRelation: state.precedentialRelation,
    analyzationOfWord: state.analyzationOfWord,
    wordForAnalyzation: state.wordForAnalyzation
  }),
  { getWordSyntaxAnalyzation }
)(SyntaxAnalyzer);
