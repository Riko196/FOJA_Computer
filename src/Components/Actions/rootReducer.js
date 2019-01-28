import { setGrammar1, setGrammar2, setEquivalence } from "./actions";

export const reducers = (state, action) => {
  switch (action.type) {
    case "Set grammar1":
      return { ...state, grammar1: action.payload };
    case "Set grammar2":
      return { ...state, grammar2: action.payload };
    case "Set equivalence":
      return { ...state, equivalence: action.payload };
    default:
      return state;
  }
};

export const mapDispatchToProps = dispatch => ({
  setGrammar1: grammar1 => dispatch(setGrammar1(grammar1)),
  setGrammar2: grammar2 => dispatch(setGrammar2(grammar2)),
  setEquivalence: value => dispatch(setEquivalence(value))
});

export default reducers;
