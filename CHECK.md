### Инструкция для проверки работы плагинов с помощью unimrcpserver и umc:
* Скачать и установить unimrcp версии 1.6 (для других версий потребуется пересборка плагинов с нужной версией unimrcp):
```shell
    $ wget -O unimrcp.tar.gz https://www.unimrcp.org/project/component-view/unimrcp-1-6-0-tar-gz/download tar -xf unimrcp-deps.tar.gz
    $ cd unimrcp-1.6.0/
    $ ./bootstrap
    $ ./configure --prefix /opt/unimrcp --with-apr=/opt/apr --with-apu=/opt/apr/lib/pkgconfig/apr-util-1.pc --with-sofia-sip=/usr/lib/pkgconfig/sofia-sip-ua.pc
    $ make && make install
```
* Скопировать плагины в папку `/opt/unimrcp/plugin`
* Сконфигурировать unimrcpserver для работы с плагинами в файле `/opt/unimrcp/conf/unimrcpserver.xml`  
Пример для плагина распознавания:
   ```xml
   <plugin-factory>
      <engine id="SmartSpeechRecognize" name="smartspeech-recognition-demo" enable="true">
          <param name="smartspeech-url" value="smartspeech.sber.ru"/>
          <param name="smartmarket-url" value="https://salute.online.sberbank.ru:9443"/>
          <param name="smartmarket-client-id" value=""/>
          <param name="smartmarket-secret" value=""/>
    </engine>
   </plugin-factory>
   ```
   Описание параметров:  
      `smartspeech-url` - адрес сервиса SmartSpeech  
      `smartmarket-url` - адрес SmartMarket API  
      `smartmarket-client-id` - ID клиента  
      `smartmarket-secret` - secret для получения токена для SmartSpeech  
      Опциональный параметр:  
      `smartmarket-scope` - Пространство в котором создан secret, по умолчанию: `SMART_SPEECH`
  

* Скопировать тестовые данные и прописать их в тестовые сценарии:
   ```shell
   $ cp test_sample.pcm /opt/unimrcp/data
   ```   
  `test_sample.pcm` - тестовый сырой аудиофайл pcm16 8000hz  
  Прописать тестовую запись в сценарий распознавания `/opt/unimrcp/conf/umc-scenarios/recognizer.xml`
  ```xml
  <?xml version="1.0" encoding="UTF-8"?>
    <umcscenario name="recog" class="Recognizer" profile="uni2">
    <resource-discovery enable="0"/>
    <define-grammar enable="1" content-type="application/srgs+xml" content-location="grammar.xml"/>
    <recognize enable="1" audio-source="test_sample.pcm"/>

    <termination enable="1">
      <capabilities>
        <codec name="LPCM" rates="8000 16000"/>
      </capabilities>
    </termination>
  </umcscenario>
  ```
  
* Запустить unimrcpserver и убедится в отсутствии ошибок при инициализации
    ```shell
    $ cd /opt/unimrcp/bin
    $ ./unimrcpserver
    ```
  
* Запустить umc и сценарий
   ```shell
   $ cd /opt/unimrcp/bin
   $ ./umc
   $ # для распознавания
   $ > run recog
   $ # для синтеза
   $ > run synth
   ```
  При этом в случае распознавания результат можно увидеть в выходе umc, а для синтеза будет создан файл в `/opt/unimrcp/var/<session_id>.pcm`
  (имя и путь до файла так же можно найти в выходе umc)