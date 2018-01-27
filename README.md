# Virtual artist abstractionist

This is a console C++ program that generates random abstract paintings in PNG format that I created in 2014.
Here is the [main article with lots of generated pictures](http://www.aivanf.com/eng/note/virtual-artist).

### Project files

- `mathem.h` – some helpful functions.

- `lodepng.h` / `lodepng.cpp` – PNG library created by [Lode Vandevenne](http://lodev.org/lodepng/).

- `islepng.h` –  **isle** namespace and **Picture** class for images manipulations.

- `mem.h` / `mem.cpp` – **mem** namespace, classes **Value**, **Number**, **Variable**, **Expression**, **Pool**,
and functions for deep expressions creation.

  Namespace **mem** is used for creation of random expression.
Class **Value** is an abstract parent for the **Number**, **Variable**, and **Expression** classes.
Class **Number** represents a constant number, **Variable** is a number which value may be changed from outside.
**Expression** is linked with two **Value**s and has an operation type.
Static class **Pool** is used for memory cleaning.

  The function `Value* SetDeepValueVars(int, Value*, Value*)` recursively creates random expressions
  with given values at the bottom level.

- `main.cpp` – entry point, input handling, and generation controlling.

### The algorithm of image creation

1. Initially, the program creates two expressions **P** and **Q**
with different depth and **X** and **Y** as variables.

2. Then, it creates expressions **H** and **V** using **P** and **Q** as variables.

3. Then, it iterates through image pixels and calculates values of **H** and **V**,
and uses it for translation from [HSV](https://en.wikipedia.org/wiki/HSL_and_HSV) to [RGB](https://en.wikipedia.org/wiki/RGB_color_model) color model. The obtained values are used for pixels RGB colors.

### License

Copyright AivanF. (c) 2014-2018

This code is provided 'as-is', without any express or implied
warranty. You may not hold the author liable.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this code must not be misrepresented. You must not
claim that you wrote the original software. When use the code, you must give appropriate credit,
provide a link to this license, and indicate if changes were made.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
    
