import fs from "node:fs";
import path from "node:path";
import { exit } from "node:process";
import { getNextToken } from "./lexer.js";

// CLI argument handling (read code file)
if (process.argv.length !== 3) {
	console.log('Error. Usage: node main.js <calculaCodeFile>');
	exit(1);
}

// initial file processing
const filename = process.argv[2];
const filepath = path.join(import.meta.dirname, filename);

export const readable = fs.createReadStream(filepath, {
	encoding: 'utf8',
	fd: null
});
readable.on('error', () => {
	console.error(`Error reading filename: ${filename}`);
});

// main loop
while (true) {
	const token = getNextToken(readable);
	// EOF is null, we finish lexing
	if (token === null) {
		console.log("<EOF>");
		break;
	}
	console.log(token);
}

