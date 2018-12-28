const fuzzer = require('fuzzer');
const prettyBytes = require('pretty-bytes');
const metaphone = require('../index');

fuzzer.seed(Math.random());

test('really really dummy segfault test', () => {
  const string = 'Lucas Fernando Amorim';
  for (let i = 0; i < 100000; i += 1) {
    const stringTest = fuzzer.mutate.string(string);
    process.stderr.write(`Memory Usage: ${prettyBytes(process.memoryUsage().rss)}\r\n`);
    process.stderr.write(`Trying: (${stringTest})\r\n`);
    process.stderr.write(`Native: (${metaphone(stringTest)})\r\n`);
  }
});
