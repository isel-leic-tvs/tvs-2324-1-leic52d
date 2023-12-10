FROM alpine
LABEL purpose learning
WORKDIR src
#COPY ./config .
#COPY ./README .
COPY [ "./README", "./config",  "." ]
RUN date > build_date.txt
CMD echo $(cat build_date.txt)

