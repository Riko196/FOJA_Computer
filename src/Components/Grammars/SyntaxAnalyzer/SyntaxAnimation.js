import React, { Component } from "react";
import { connect } from "react-redux";

import "./SyntaxAnimation.css";

class SyntaxAnimation extends Component {
  render() {
    return (
      <div className="syntax-animation">
        <h1>Syntax analyzation for word "{this.props.wordForAnalyzation}":</h1>
        {this.props.analyzationOfWord.map(command => (
          <p className="command-paragraph">{command}</p>
        ))}
      </div>
    );
  }
}

export default connect(state => ({
  analyzationOfWord: state.analyzationOfWord,
  wordForAnalyzation: state.wordForAnalyzation
}))(SyntaxAnimation);
