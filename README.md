# snake-wasm

Snake in C+ for WebAssembly

This is a primitive snake in C++ish to test WebAssembly

## Getting Started

### Installing

You'll need [emscripten](https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html) to compile the program 

### Compiling

```
emcc web.cc snake.cc base.cc -s USE_SDL=2 -s ASSERTIONS=1 -O3 -o index.html
```

You'll then need a http server to view the result, you can use `python3 -m http.server`.


## Examples

TODO
