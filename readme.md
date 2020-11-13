tank-v0.6
Stand 11-2020
# Tankfüllstand Sensor VL53L0X
(für einen Öltank in der Heizzentrale)  
  
DS18B20 Nr.1 - Heizung Vorlauf  
DS18B20 Nr.2 - Heizung Rücklauf   

Das Projekt soll den Bau eines Fpllstandssensors ermöglichen, der in einen Heizöltank von oben eingeschraubt wird (in einem der Blinddeckel).
Die gewonnen Daten (Füllhühe, Temperatur...) können abgelesen werden um zu vermeiden, dass der Tank komplett leerläuft.

Das aktuelle Projekt soll die Anbindung per LoRaWAN ermöglichen.
- es muss ein LoRaWAN-Gateway in Reichweite sein
- ein TTN Account ist erforderlich, eine App und die Schlüssel müssen nutzbar sein

Rückfragen dauern etwas länger, da das Projekt ausschließlich als Hobby in Freizeit entsteht.
Viel Freude beim Probieren!

Teile:
- Heltec CubeCell (HTCC-AB01) arduinokompatibel
- VL53L0X /TOF Sensor
- 2 DS18B20 Temperatursensoren
- 5v USB Netzteil /Ladegerät
- 2 Widerstände 4K7 (für DS18B20)
- Lochrasterplatte 70x50mm, passende Steckleisten, Drähte, Lötzubehör

Die Daten werden üder MQTT von TTN abgeholt und Lokal (Synology NAS DS218+ mit Docker-Containern) verarbeitet

-> MQTT (TTN) -> NodeRed (umarbeiten für INFLUX-DB) - speichern in INFLUX-DB -> Anzeige in GRAFANA DashBoards

ToDo: abholen über HTTP-Integration von TTN in Webspace (Hoster mit mySQL), Anzeige auf eigener Website z.B. mit highcharts
