FROM alpine:latest as BUILDER
RUN apk update && apk add --no-cache git make gcc musl-dev mpfr-dev gmp-dev
WORKDIR /src
ADD *.c *.h Makefile ./
RUN make

FROM alpine:latest
WORKDIR /app
RUN apk update && apk add --no-cache musl-dev mpfr-dev gmp-dev
COPY --from=BUILDER /src/pwe /app/
ENTRYPOINT ["/app/pwe"]
