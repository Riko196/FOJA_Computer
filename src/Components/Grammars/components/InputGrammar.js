import React, { Component } from "react";

import "./InputGrammar.css";

class InputGrammar extends Component {
  state = {
    nonterminals: "",
    terminals: "",
    rules: "",
    start: "",
    inputMessage: ""
  };

  handleNonterminalsChange = event => {
    this.setState({ nonterminals: event.target.value });
  };

  handleTerminalsChange = event => {
    this.setState({ terminals: event.target.value });
  };

  handleRulesChange = event => {
    this.setState({ rules: event.target.value });
  };

  handleStartChange = event => {
    this.setState({ start: event.target.value });
  };

  handleInputMessageChange = value => {
    this.setState({ inputMessage: value });
  };

  badLetterProblemTerminals = word => {
    if (word.length !== 1) return true;
    return word.charCodeAt(0) < 97 || word.charCodeAt(0) > 122;
  };

  badLetterProblemNonterminals = word => {
    if (word.length !== 1) return true;
    return word.charCodeAt(0) < 65 || word.charCodeAt(0) > 90;
  };

  badRuleWord = (word, nonterminalsSet, terminalsSet) => {
    for (let letter of word) {
      if (!nonterminalsSet.has(letter) && !terminalsSet.has(letter))
        return true;
    }
    return false;
  };

  isEpsilon = word => {
    return word.length === 0;
  };

  readInput = () => {
    this.handleInputMessageChange("");

    if (
      this.state.nonterminals === "" ||
      this.state.terminals === "" ||
      this.state.rules === ""
    ) {
      this.handleInputMessageChange("There can not be empty sets!");
      return;
    }

    const nonterminals = this.state.nonterminals.split(",");
    const terminals = this.state.terminals.split(",");
    const start = this.state.start;
    const rules = this.state.rules.split(/['->', '\n']/);

    const nonterminalsSet = new Set();
    for (let letter of nonterminals) {
      if (this.badLetterProblemNonterminals(letter)) {
        this.handleInputMessageChange("Bad nonterminals!");
        return;
      }
      nonterminalsSet.add(letter);
    }

    const terminalsSet = new Set();
    for (let letter of terminals) {
      if (this.badLetterProblemTerminals(letter)) {
        this.handleInputMessageChange("Bad terminals!");
        return;
      }
      terminalsSet.add(letter);
    }

    const rulesSet = new Set();

    let nonterminal;
    for (let i = 0; i < rules.length; i += 1) {
      switch (i % 3) {
        case 0:
          if (
            this.badLetterProblemNonterminals(rules[i]) ||
            !nonterminalsSet.has(rules[i])
          ) {
            this.handleInputMessageChange("Bad left part of the rule!");
            return;
          }
          nonterminal = rules[i];
          break;
        case 1:
          if (!this.isEpsilon(rules[i])) {
            this.handleInputMessageChange("Bad format!");
            return;
          }
          break;
        case 2:
          for (let word of rules[i].split("|")) {
            if (this.badRuleWord(word, nonterminalsSet, terminalsSet)) {
              this.handleInputMessageChange("Bad right part of the rule!");
              return;
            }
            rulesSet.add([nonterminal, word]);
          }
          break;
        default:
          break;
      }
    }
    console.log(nonterminalsSet);
    console.log(terminalsSet);
    console.log(start);
    console.log(rulesSet);
  };

  render() {
    const nonterminals = this.state.nonterminals
      .split(",")
      .map(letter => <option value={letter}>{letter}</option>);
    return (
      <form onSubmit={this.readInput}>
        <h3>
          G = {"{"}
          <br /> N = {"{ "}
          <input
            type="text"
            name="nonterminals"
            onChange={this.handleNonterminalsChange}
          />
          {" }"}
          <br /> T = {"{ "}
          <input
            type="text"
            name="terminals"
            onChange={this.handleTerminalsChange}
          />
          {" }"}
          <br /> S = {"{ "}
          <select value={this.state.start} onChange={this.handleStartChange}>
            {nonterminals}
          </select>
          <br /> P = {"{ "}
          <textarea
            type="text"
            name="rules"
            onChange={this.handleRulesChange}
          />
          {" }"}
        </h3>
        <p>{"}"}</p>
        <input type="button" onClick={this.readInput} value="Enter" />
        {this.state.inputMessage !== "" && <h3>{this.state.inputMessage}</h3>}
      </form>
    );
  }
}

export default InputGrammar;
