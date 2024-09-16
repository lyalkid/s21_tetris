# корневой image образ для сборки - чистый ubuntu
FROM ubuntu

# обновляем apt пакеты и устанавливаем по очереди нужные зависимости
RUN apt-get update && apt-get install -y gcc make valgrind check clang lcov clang-format vim libncurses5-dev libncursesw5-dev

COPY . /code

# Устанавливаем
WORKDIR /code

CMD /bin/bash

