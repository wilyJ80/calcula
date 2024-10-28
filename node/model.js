import { isNonPrinting, isAlpha, isPlus, isMinus, isSlash, isMult, isEqual, isParenOpen, isParenClose, isDigit, isAlnumOrUnderscore, isNotAlnumOrUnderscore, isNotDigit } from "./controller.js";

export const transitions = {
	0: [
		{ 0: isNonPrinting, final: false },
		{ 1: isAlpha, final: false },
		{ 3: isPlus, final: true, type: 'PLUS' },
		{ 4: isMinus, final: true, type: 'MINUS' },
		{ 5: isSlash, final: true, type: 'SLASH' },
		{ 6: isMult, final: true, type: 'MULT' },
		{ 7: isEqual, final: true, type: 'EQUAL' },
		{ 8: isParenOpen, final: true, type: 'PAREN_OPEN' },
		{ 9: isParenClose, final: true, type: 'PAREN_CLOSE' },
		{ 10: isDigit, final: false }
	],
	1: [
		{ 1: isAlnumOrUnderscore, final: false },
		{ 2: isNotAlnumOrUnderscore, final: true, type: 'ID' }
	],
	2: [],
	3: [],
	4: [],
	5: [],
	6: [],
	7: [],
	8: [],
	9: [],
	10: [
		{ 10: isDigit, final: false },
		{ 11: isNotDigit, final: true, type: 'NUMBER' }
	],
	11: []
};

export const createToken = (value, type) => {
	return { value, type };
};
