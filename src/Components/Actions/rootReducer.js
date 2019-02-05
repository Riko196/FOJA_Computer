import { setGrammar1, setGrammar2, setEquivalencyAnswer } from "./actions";
import { substitutedEpsilon } from "../Grammars/components/Utils/Constants";

export const reducers = (state, action) => {
  switch (action.type) {
    case "Set grammar1":
      return { ...state, grammar1: action.payload };
    case "Set grammar2":
      return { ...state, grammar2: action.payload };
    case "Set answer for equivalency":
      if (action.payload === null)
        return {
          ...state,
          equivalencyAnswer: {
            answer: null,
            equivalency: null
          }
        };
      const equivalencyAnswer = action.payload.split("|");
      const equivalency = equivalencyAnswer[1] === "0" ? false : true;
      return {
        ...state,
        equivalencyAnswer: {
          answer:
            equivalencyAnswer[0] === substitutedEpsilon
              ? "Epsilon"
              : equivalencyAnswer[0],
          equivalency: equivalency
        }
      };
    default:
      return state;
  }
};

export const mapDispatchToProps = dispatch => ({
  setGrammar1: grammar1 => dispatch(setGrammar1(grammar1)),
  setGrammar2: grammar2 => dispatch(setGrammar2(grammar2)),
  setEquivalencyAnswer: equivalencyAnswer =>
    dispatch(setEquivalencyAnswer(equivalencyAnswer))
});

export default reducers;
