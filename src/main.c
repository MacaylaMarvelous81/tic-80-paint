#include "tic80.h"

WASM_EXPORT("TIC")
void TIC() {
  cls(1);
  print("Hello, world!", 0, 0, 12, false, 1, false);
}
