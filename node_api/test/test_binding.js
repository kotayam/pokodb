const Pokodb = require("../lib/binding.js");
const assert = require("assert");

assert(Pokodb, "The expected module is undefined");

function testMethodDefinition() {
  const db = new Pokodb();
  assert(db.insert, "insert is not defined");
  assert(db.get, "get is not defined");
  assert(db.delete, "delete is not defined");
  assert(db.update, "update is not defined");
  assert(db.close, "close is not defined");
  db.close();
}

function testBasic() {
  const db = new Pokodb();
  db.insert("test", "hello");
  assert.strictEqual(db.get("test"), "hello", "wrong value");
  assert.throws(() => db.get("world"), Error, "Key should not exist");
  assert.throws(() => db.insert("test"), Error, "Key already exists");

  db.insert("jack", "daniel");
  assert.strictEqual(db.get("jack"), "daniel", "wrong value");

  db.update("test", "world");
  assert.strictEqual(db.get("test"), "world", "wrong value");

  db.delete("test");
  assert.throws(() => db.get("test"), Error, "Key shoudl not exist");

  db.close();
}

testMethodDefinition();
testBasic();

console.log("Tests passed- everything looks OK!");
