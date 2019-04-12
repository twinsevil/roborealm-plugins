# Roborealm plugins
Plugins developed for [Roborealm](http://www.roborealm.com/) while working in Intelmet

# Queue plugin

Due to the fact that the process of detecting and recognizing an object of interest with a barcode takes considerable time, we can miss important frames of the video stream. The "Queue" plugin allows you to first save these frames to a queue, and then process each of them in "free time". By "free time" is meant the time when an object of interest does not fall into the focus of the camera. Often it takes from a few seconds to a few minutes. The process of getting an object into the focus of a video camera may take less than a second. Therefore, we must first save these moments in the queue (without any resource-intensive processing), and then process each frame and recognize the barcode.

Из-за того, что процесс детектирования и распознавания объекта интереса с баркодом занимает существенное время, мы можем упустить важные кадры видеопотока. Плагин "Очередь" позволяет сначала сохранить эти кадры в очередь, а затем обработать каждый из них в "свободное время". Под "свободным временем" понимается время, когда объект интереса не попадает в фокус камеры. Зачастую это занимает от нескольких секунд до нескольких минут. Процесс же попадания объекта в фокус видеокамеры может занимать менее секунды. Поэтому мы вынуждены сначала сохранить эти моменты в очереди (без какой-либо их ресурсозатратной обработки), а затем обработать каждый кадр и распознать баркод.

# Grid plugin

Custom grid drawing.

Отрисовка кастомизируемой сетки.
