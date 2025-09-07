# PokoDB

This is a JavaScirpt library for PokoDB an in-memory database written in C.

It is a key-value storage and can be used as a cache to store fetched data or user state.

## Usage

```js
const Pokodb = require("@kotayama/pokodb");

try {
  // initialize instance
  const db = new Pokodb();

  // insert
  db.insert("hello", "world");

  // get
  const value = db.get("hello"); // value = "world"

  // update
  db.update("hello", "space");
  const updatedVal = db.get("hello"); // value = "space"

  // delete
  db.delete("hello");

  // close to free memory
  db.close();
} catch (e) {
  cosole.error(e);
}
```
