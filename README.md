# gkit is forked from  gabrield/stk

gkit - Small Graphical toolkit based on Xlib;

gkit is a small Graphical toolkit for desktop applications.

# Build instructions
Build common object files:
- ./build.sh linux objs

Build application executable:
- ./build.sh linux exe test2.c
- or ./build.sh linux exe test.c
- or ./build.sh linux exe YourFilenameLocatedInSrcDir.c

Build app and run
- ./build.sh linux exe test-canvas.c run

Build app and run detached from terminal
- /build.sh linux exe test-canvas.c rund

Clean build directory
- ./build.sh clean


# Widget list

* Window
* Button
* Text Input/Output - still need some changes/improvements
* Plotter - under development/test
* ProgressBar

# Help
Take a look at test.c to see the basics of gkit.

