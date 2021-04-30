# Dragon Curve
A little animation of the [dragon curve fractal](https://en.wikipedia.org/wiki/Dragon_curve) written in c and using [raylib](https://raylib.com) for graphics

![](dragon_curve.gif)

## Running and stuff
**Warning:** This was developed and tested only on arch linux, so the instructions should work there, anywhere else, you are kind of on your own. You also probably don't need to build and run this yourself because of the gif on this readme, but you can if you want to.


First make sure raylib is installed, either build from source from the [github repo](https://github.com/raysan5/raylib) or (on arch linux) run `sudo pacman -S raylib`

Then you should just be able to run `make dragon` in the root of this repo (you may need to modify the Makefile if the method you used to install raylib doesn't work with `-lraylib`)

Then `./dragon` and voilà (hopefully)
