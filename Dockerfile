FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y build-essential cmake libpqxx-dev postgresql-server-dev-14

WORKDIR /app
COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --target install

CMD ["./build/knapsack-api"]