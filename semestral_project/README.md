# CTU_RTSP_term_project

[assignment page link](https://wiki.control.fel.cvut.cz/psr/cviceni/semestralka/)

### Team

- Denys Datsko
- Morhunenko Mykola

## Short project description

The main goal of the semester project was to create such a program, that reads the position from one motor (moved by
hand or steer-by-wire), sends desired position via the Internet to another motor and sets it to another motor. The
set-point is transferred between two motor controllers using UDP messages. The actual state of the controller and its
history is published as live plots over http protocol.

We implemented:

- IRQ handler for reading and (maybe) updating some information
- motor driver for controlling step motors
- partially implemented PID controller for motors (P part, as we understand it, is implemented)
- UDP server for inter-controllers-communication using BSD sockets
- HTTP server for data visualisation in a browser
- SVG Plots library (we took [nanosvg](https://github.com/memononen/nanosvg) lib, modified it as we need, and wrote
  documentation + few more functions for it)

## Instructions for compiling and running your application.

Project was written and tested only on Linux-based OS, for VxWorks RTOS in WindRiver IDE. Such files as `.project`
, `.cpoject`, `.wrproject` and `.wrmakefile` files are given for building and executing.  
So to compile the project, open it using the WindRiver IDE and build it **Project -> Build project**   

## Screenshot of your web-based (or text-based) user interface

TODO

## Data-Flow Diagram.

![Structure from drawio](https://user-images.githubusercontent.com/35429810/145839149-233df933-eaf2-461b-ba59-05410f1e0474.png)

## Description of global functions and variables (created by you) including the description of function parameters and return values.

The documentation generation by Doxygen and `doxy.conf` is possible. You can generate `doc/` folder
with `doxygen doxy.conf`. To receive `.pdf`, go to `/doc/latex` folder and run `make` there. To open the documentation
as a web page, go to `doc/html/` folder and open the html file using any browser
