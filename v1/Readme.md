# Version 1 -- Erste Stabile Version

In dieser ersten stabilen Version ist es möglich sich zu registrieren (E-Mail + Passwort).
Nach dem Anmelden bekommt man eine SID die einen autorisiert die Nachrichten zu lesen.

Auf einer Seite kann man alle allgemeinen Meldungen einsehen und sich abmelden. 

Um das komplette System auf einem anderen Rechner nachzubilden sind folgende Schritte notwendig

* nginx + fcgiwrap installieren
* mysql Server installieren
* (Konfigurations-)Dateien in die entsprechenden Verzeichnisse kopieren
* Die Datei "datenbank.mysql" in die eigen mysql-Datenbank einlesen

