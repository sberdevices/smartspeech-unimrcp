## smartspeech-unimrcp

Пример UniMRCP плагина с реализацией синтеза и распознавания с использованием SmartSpeech.
1. UniMRCP - клиент-серверная реализация протокола MRCP. https://www.unimrcp.org/
2. SmartSpeech - сервисы распознавания и синтеза речи на технологиях Сбера. https://developers.sber.ru/portal/services/smartspeech

Реализованы базовые MRCP методы. Для распознавания: `SET-PARAMS`, `DEFINE-GRAMMAR`, `RECOGNIZE`, `STOP`. Для синтеза: `SET-PARAMS`, `SPEAK`, `BARGE_IN_OCCURRED`, `STOP`.

### Подготовка к сборке:
1. Установка необходимых пакетов (сборка тестировалась на ubuntu 20.10):
   ```
   $ apt install -y build-essential gcc g++ clang cmake tar libprotobuf-dev libprotoc-dev protobuf-compiler \
   libgrpc++-dev libgrpc-dev protobuf-compiler-grpc \
   pkg-config libcurl4-openssl-dev nlohmann-json3-dev libsofia-sip-ua-dev libssl-dev
   ```
2. Скачать патченные зависимости для unimrcp:
     ```
   $ wget -O unimrcp-deps.tar.gz https://www.unimrcp.org/project/component-view/unimrcp-deps-1-6-0-tar-gz/download && tar -xf unimrcp-deps.tar.gz
     ```
    
3. Собрать зависимости:
   ```
   $ cd unimrcp-deps-1.6.0/
   $ ./build-dep-libs.sh -s -a /opt/apr -o /opt/sofia
   ```
    
4. Склонировать репрзиторий и загрузить сабмодули:
   ```
   $ git submodule update --init --recursive
   ```
   
5. Сборка плагинов:
    ```
   $ cd smartspeech-unimrcp
   $ mkdir b && cd b
   $ cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
   $ make
    ```
   
### Использование:
В результате будут собраны два плагина `smartspeech-recognition-demo.so` и `smartspeech-synthesis-demo.so`. 

#### Для базовой инсталляции unimrcp подключение плагинов выглядит так:
1. Скопировать плагины в директорию `plugins`
2. Сконфигурировать движки распознавания и/или синтеза в конфигурационном файле `unimrcpserver.xml`:
    ```
   <engine id="SmartSpeechRecognize" name="smartspeech-recognition-demo" enable="true">
        <param name="smartspeech-url" value="..."/>
        <!-- smartmarket API url -->
        <param name="smartmarket-url" value="..."/>
        <param name="smartmarket-client-id" value="..."/>
        <!-- smartmarket secret for generation access tokens -->
        <param name="smartmarket-secret" value="..."/>
      </engine>
    ```
   
После этого плагины можно использовать вместе с сервером.  

### [Инструкция для проверки работы плагинов с помощью unimrcpserver и umc](./CHECK.md)