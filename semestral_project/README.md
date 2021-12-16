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
Then, 2 run configurations for 2 boards should be created:
* The first one runs the CreateTasks with arguments (false, NULL) and this board will receive the desired motor position and move motor there
* The arguments of CreateTasks for the second cpnfiguration should be (true, "<first_board_ip_address>"). This board will just read the motor position and send it to the specified ip address

## Screenshot of your web-based (or text-based) user interface

![Web interface screenshot](/media/Web_interface_screenshot.png)
For doxygen: 
\image latex Web_interface_screenshot.png "Screenshot" width=10cm

## Data-Flow Diagram.

![Structure from drawio](/media/diagram.png)
For doxygen:
\image latex diagram.png "Diagram" width=10cm

## Description of global functions and variables (created by you) including the description of function parameters and return values.

The documentation generation by Doxygen and `doxy.conf` is possible. You can generate `doc/` folder
with `doxygen doxy.conf`. To receive `.pdf`, go to `/doc/latex` folder and run `make` there. To open the documentation
as a web page, go to `doc/html/` folder and open the html file using any browser
