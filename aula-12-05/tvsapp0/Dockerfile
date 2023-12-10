FROM node

# some metadata
LABEL mantainer: "Jorge Martins"

WORKDIR /tvsapp

COPY [ "tvsapp.js", "package.json", "./" ]

RUN npm install


EXPOSE 4004

CMD ["node", "tvsapp.js"]
