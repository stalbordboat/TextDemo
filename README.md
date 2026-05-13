### Synopsis

Intended to be a demo of the use of the `GameEngine`'s Native API. This demo program draws a timer and FPS counter and displays it on the window.

### Basic Structure

```
----------    ---------
|Start.rb| <- |Game.so|
----------    ---------
--------
| Game |
--------
```

This projects compiles a runtime binary called `Game.so` and it's loaded using `native_load` by `Start.rb`.

### Screenshots
![ScreenshotA](https://i.imgur.com/Wwx2VFU.png)
