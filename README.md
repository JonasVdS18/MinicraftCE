# MinicraftCE

IMPORTANT: this project is still under construction

A custom version of minicraft for your TI-84 plus CE calculator.
The source code of minicraft where this project is based upon: [minicraft](https://github.com/shylor/miniventure/)

To install the game on your calculator, you will need to have [TI connect CE](https://education.ti.com/en/products/computer-software/ti-connect-ce-sw) and you also need to install the [CE C 'Standard' Libraries](https://github.com/CE-Programming/libraries/releases/).

# BUILDING
If you would like to build MinicraftCE yourself, be sure you have the latest LLVM [CE C Toolchain](https://github.com/CE-Programming/toolchain/releases/latest) installed.

Simply clone or download the repository from above. 
Don't forget to copy one of the makefiles that belongs to your OS (from the makefiles folder) to the root of the project.
Finally run the following commands to build the project:

    make gfx
    make

# INFO
if you want to know more about developing games for the TI-84 plus CE calculator, I highly recommend to take a look at the [CE C Toolchain](https://github.com/CE-Programming/toolchain) they also have a [documentation](https://ce-programming.github.io/toolchain/). You can also use the [CEmu emulator](https://github.com/CE-Programming/CEmu) to experiment on a virtual calculator, so that if you do something wrong, you won't crash your actual calculator.
