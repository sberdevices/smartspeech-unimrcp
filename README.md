## smartspeech-unimrcp

Пример UniMRCP плагина с реализацией синтеза и распознавания с использованием SmartSpeech.
1. UniMRCP - клиент-серверная реализация протокола MRCP. https://www.unimrcp.org/
2. SmartSpeech - сервисы распознавания и синтеза речи на технологиях Сбера. https://developers.sber.ru/portal/services/smartspeech

Реализованы базовые MRCP методы. Для распознавания: `SET-PARAMS`, `DEFINE-GRAMMAR`, `RECOGNIZE`, `STOP`. Для синтеза: `SET-PARAMS`, `SPEAK`, `BARGE_IN_OCCURRED`, `STOP`.

