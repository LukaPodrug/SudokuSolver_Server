FROM ubuntu
RUN apt-get update
RUN apt install nodejs -y
RUN apt install npm -y
COPY . /server
WORKDIR server
RUN npm install
CMD ["node", "index.js"]