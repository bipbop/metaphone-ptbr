const fuzzer = require('fuzzer');
const metaphone = require('..');

fuzzer.seed(Math.random());

test('fuzzy', () => {
  const string = 'Lucas Fernando Amorim';
  for (let i = 0; i < 10000; i += 1) {
    const stringTest = fuzzer.mutate.string(string);
    metaphone(stringTest);
  }
});
