FROM ubuntu
RUN apt update && apt upgrade
RUN apt install build-essential -y
RUN apt install nodejs -y
RUN apt install npm -y
RUN DEBIAN_FRONTEND=noninteractive apt install libopencv-dev -y
RUN DEBIAN_FRONTEND=noninteractive apt install libtesseract-dev -y
RUN DEBIAN_FRONTEND=noninteractive apt install tesseract-ocr -y
RUN apt install cmake -y
COPY . /server
WORKDIR server
RUN npm install
WORKDIR sudokuHelper
RUN g++ -std=c++11 -o ./sudokuHelperExe sudokuHelper.cpp
RUN cp ./sudokuHelperExe ..
WORKDIR ..
WORKDIR sudokuGrabber
RUN mkdir build
WORKDIR build
RUN cmake ..
RUN make
RUN cp ./sudokuGrabberExe ../..
WORKDIR ../..
CMD ["node", "index.js"]