# :sunny:SUNDIAL CALCULATOR:sunny:
## Summary of the project
Sundial calculator, which also indicates the season of the year, at any given location, built in a horizontal plane or on a wall with any orientation. Instructions are included in the main program tab.
## Installation
Only available for most Linux distros at the moment. To install the program you just need to download the repo into your local machine, navigate to the directory: {PARENT_FOLDER}/dist/ and execute in the bash terminal: ./gui
## Usage
To use the sundial calculator, navigate in the map to the location where the instrument will be built, specify the timezone, height of the gnomon, orientation of the wall, and click on the "Calculate" button! :metal:
A new tab will appear with the measurements of the sundial, which can be saved into your local computer.\
**_Important_ to use the program with internet connection, so that the maps can be loaded**:exclamation:\
The .csv file exports the measurements of the instrument. The season of each projection curve is indicated by the day number of the year in the "Id" column of "datos_reloj.csv"\
<img
  src="./programa_vista.png"
  title="Vista del programa"
  style="display: inline-block; margin: 0 auto; max-width: 300px">\
<img
  src="./grafica_vista.png"
  title="Vista de la gráfica"
  style="display: inline-block; margin: 0 auto; max-width: 300px">
## Code and project details
The code is well documented, and free to use for modifications and improvements. All calculations are held by c++ programs, but the gui is developed using Python3. It is recommended to use a virtual environment to encapsule the Python requirements. To download the requirements, type into your terminal (in the parent folder of the project):
```
pip install -r requirements.txt
```
## Directory structure
The source code of the project is in the src/ directory, where the c++ class and definitions of its attributes is defined, as well as the main c++ script which invoques the class. This directory also includes Python source files and some images which are needed for the gui. The binary executables of the cpp files are stored in the build/ directory, as well as the .csv files, which serve as output for the program and which store the info for building the sundial.
