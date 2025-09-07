# Pokodb

Pokodb is a lightweight, high-performance, in-memory key-value database written entirely in C. It is designed for speed and simplicity, offering two primary ways to interact with it: as a standalone command-line interface (CLI) or as a native Node.js addon available on the [npm registry](https://www.npmjs.com/package/@kotayama/pokodb).

## Features

- Fast In-Memory Storage: All data is stored directly in memory for rapid read and write access.
- Simple Key-Value Model: A straightforward and flexible data storage paradigm.
- Standalone CLI: A C-based command-line interface for direct database interaction and management.
- Node.js Integration: Published as an npm package, allowing you to leverage the speed of C in your JavaScript projects.

## CLI

If you want to use Pokodb as a standalone database or contribute to the core C code, you can build and run the CLI directly from the source.

### Prerequisites

- `gcc`: C compiler.
- `make`: Build tool.

### Installation and Usage

#### Clone the Repository

```
git clone [https://github.com/kotayam/pokodb.git](https://github.com/kotayam/pokodb.git)
cd pokodb
```

#### Build the Project

The included `Makefile` compiles all the necessary C source files.

```
make
```

#### Run the CLI

Use the `run` target in the `Makefile` to start the interactive CLI.

```
make run

Welcome to PokoDB!
For further instructions, please type help and press enter
>
```

This will launch the PokoDB CLI, allowing you to execute database commands directly in your terminal.

#### Operations

- `quit`: quit the program.
- `help`: show help.
- `print`: print out the stored data.
- `insert [key] [value]`: insert value in key.
- `get [key]`: get value stored in key.
- `update [key] [value]`: update the value in stored at key.
- `delete [key]`: delete key.
- `batch [num_operations] [num_threads]`: execute a batch of operations - using threads.

## NPM Package

Pokodb is released as a native addon on the [npm registry](https://www.npmjs.com/package/@kotayama/pokodb), making it easy to integrate the high-performance C database into your Node.js applications.

### Installation

Install the package using your preferred package manager:

#### Using npm

```
npm install pokodb
```

#### Using yarn

```
yarn add pokodb
```

### Usage Example

Once installed, you can require the module and use its functions in your project.

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
